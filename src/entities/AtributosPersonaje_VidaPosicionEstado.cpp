#include "entities/AtributosPersonaje_VidaPosicionEstado.h"
#include "core/LecturaDeTeclado_P1_P2.h"
#include "graphics/DibujoDePersonaje1_CuerpoYArticulaciones.h"
#include "graphics/DibujoDePersonaje2_CuerpoYArticulaciones.h"
#include "graphics/FuncionesParaDibujarFigurasBasicas.h"
#include <algorithm>
#include <cmath>

// Constantes de fisica del juego
const float GRAVEDAD = 0.0012f;
const float FUERZA_SALTO = 0.024f;
const float VELOCIDAD_CAMINAR = 0.0085f;
const float FRICCION_SUELO = 0.82f;

PersonajeFighter::PersonajeFighter() {
    idJugador = 1;
    tipo = PERSONAJE_LEONARDOX;
    nombre = "Leonardox";

    posicion = Vector2D(0.0f, -0.45f);
    velocidad = Vector2D(0.0f, 0.0f);
    direccion = 1;
    enSuelo = true;

    saludMax = 100.0f;
    salud = saludMax;
    saludRetardada = saludMax;

    escudoMax = 100.0f;
    escudo = escudoMax;
    recargaEscudoPorSeg = 14.0f;
    guardiaRota = false;

    roundsGanados = 0;
    estadoActual = ESTADO_IDLE;
    temporizadorEstado = 0.0f;
    temporizadorAturdimiento = 0.0f;
    enfriamientoParry = 0.0f;
    tiempoAnimacion = 0.0f;

    tiempoMensajeCombate = 0.0f;
}

void PersonajeFighter::setTipo(TipoPersonaje nuevoTipo) {
    tipo = nuevoTipo;
    nombre = (tipo == PERSONAJE_LEONARDOX) ? "Leonardox" : "Guadalupe";
}

void PersonajeFighter::inicializar(int _idJugador, TipoPersonaje _tipo, float posXInicial, float nivelSuelo, int dirInicial) {
    idJugador = _idJugador;
    setTipo(_tipo);

    posicion = Vector2D(posXInicial, nivelSuelo);
    velocidad = Vector2D(0.0f, 0.0f);
    direccion = dirInicial;
    enSuelo = true;

    salud = saludMax;
    saludRetardada = saludMax;
    escudo = escudoMax;
    guardiaRota = false;
    roundsGanados = 0;

    estadoActual = ESTADO_IDLE;
    temporizadorEstado = 0.0f;
    temporizadorAturdimiento = 0.0f;
    enfriamientoParry = 0.0f;
    tiempoAnimacion = 0.0f;
    tiempoMensajeCombate = 0.0f;

    actualizarHitboxYHurtbox();
}

void PersonajeFighter::reiniciarRonda(float posXInicial, float nivelSuelo, int dirInicial) {
    posicion = Vector2D(posXInicial, nivelSuelo);
    velocidad = Vector2D(0.0f, 0.0f);
    direccion = dirInicial;
    enSuelo = true;

    salud = saludMax;
    saludRetardada = saludMax;
    escudo = escudoMax;
    guardiaRota = false;

    estadoActual = ESTADO_IDLE;
    temporizadorEstado = 0.0f;
    temporizadorAturdimiento = 0.0f;
    enfriamientoParry = 0.0f;
    tiempoAnimacion = 0.0f;
    tiempoMensajeCombate = 0.0f;

    actualizarHitboxYHurtbox();
}

void PersonajeFighter::setMensajeCombate(const std::string& msj, float duracion) {
    mensajeCombate = msj;
    tiempoMensajeCombate = duracion;
}

void PersonajeFighter::dispararAtaque(EstadoFighter estadoAtaque, float duracion, float danio, float danioEsc, float empujeX, float empujeY, bool esFuerte) {
    estadoActual = estadoAtaque;
    temporizadorEstado = duracion;

    hitboxAtaque.activa = true;
    hitboxAtaque.datosGolpe.danioSalud = danio;
    hitboxAtaque.datosGolpe.danioEscudo = danioEsc;
    hitboxAtaque.datosGolpe.empujeX = empujeX;
    hitboxAtaque.datosGolpe.empujeY = empujeY;
    hitboxAtaque.datosGolpe.esFuerte = esFuerte;
    hitboxAtaque.datosGolpe.causaAturdimiento = false;

    actualizarHitboxYHurtbox();
}

void PersonajeFighter::procesarEntrada(float dt) {
    // Si esta derrotado, aturdido, herido o en castigo de parry, no puede procesar comandos
    if (estadoActual == ESTADO_DERROTADO ||
        estadoActual == ESTADO_ATURDIDO ||
        estadoActual == ESTADO_HERIDO ||
        estadoActual == ESTADO_CASTIGO_PARRY) {
        return;
    }

    // 1. Mecanica de ESQUIVE / PARRY
    // Solo si no esta en cooldown y se presiona la tecla de esquivar
    if (fueAccionPresionada(idJugador, ESQUIVAR) && enfriamientoParry <= 0.0f && enSuelo) {
        if (estadoActual == ESTADO_IDLE || estadoActual == ESTADO_CAMINANDO || estadoActual == ESTADO_BLOQUEO) {
            estadoActual = ESTADO_POSTURA_PARRY;
            temporizadorEstado = 0.35f; // Ventana de parry de 0.35 segundos
            enfriamientoParry = 1.10f;  // Cooldown para castigar si se intenta spamear
            velocidad.x = 0.0f;
            hitboxAtaque.activa = false;
            return;
        }
    }

    // Si ya esta en postura de parry o atacando, no interrumpir con caminar/bloquear
    if (estadoActual == ESTADO_POSTURA_PARRY ||
        estadoActual == ESTADO_GOLPE_SUAVE ||
        estadoActual == ESTADO_GOLPE_FUERTE ||
        estadoActual == ESTADO_CONTRAATAQUE) {
        return;
    }

    // 2. BLOQUEO (Guardia con barra de escudo)
    if (estaAccionActiva(idJugador, BLOQUEAR) && enSuelo && escudo > 0.0f) {
        estadoActual = ESTADO_BLOQUEO;
        velocidad.x = 0.0f;
        hitboxAtaque.activa = false;
        return;
    } else if (estadoActual == ESTADO_BLOQUEO && !estaAccionActiva(idJugador, BLOQUEAR)) {
        estadoActual = ESTADO_IDLE;
    }

    // 3. AGACHARSE
    if (estaAccionActiva(idJugador, AGCHARSE) && enSuelo) {
        estadoActual = ESTADO_AGACHADO;
        velocidad.x = 0.0f;
    } else if (estadoActual == ESTADO_AGACHADO && !estaAccionActiva(idJugador, AGCHARSE)) {
        estadoActual = ESTADO_IDLE;
    }

    // 4. SALTAR (Recordatorio del usuario: no olvidar el salto!)
    if (fueAccionPresionada(idJugador, SALTAR) && enSuelo && estadoActual != ESTADO_AGACHADO) {
        velocidad.y = FUERZA_SALTO;
        enSuelo = false;
        estadoActual = ESTADO_SALTANDO;
    }

    // 5. ATAQUES: Golpe Suave y Golpe Fuerte
    if (fueAccionPresionada(idJugador, GOLPE_SUAVE)) {
        dispararAtaque(ESTADO_GOLPE_SUAVE, 0.22f, 8.0f, 15.0f, 0.035f, 0.0f, false);
        return;
    }

    if (fueAccionPresionada(idJugador, GOLPE_FUERTE)) {
        // Golpe fuerte: mayor duracion, alto daño y empuje potente capaz de romper bordes
        dispararAtaque(ESTADO_GOLPE_FUERTE, 0.38f, 18.0f, 32.0f, 0.095f, 0.010f, true);
        return;
    }

    // 6. MOVIMIENTO LATERAL (Caminar)
    bool mueveIzq = estaAccionActiva(idJugador, MOVER_IZQ);
    bool mueveDer = estaAccionActiva(idJugador, MOVER_DER);

    if (estadoActual == ESTADO_IDLE || estadoActual == ESTADO_CAMINANDO || estadoActual == ESTADO_SALTANDO) {
        if (mueveIzq && !mueveDer) {
            velocidad.x = -VELOCIDAD_CAMINAR;
            if (enSuelo) estadoActual = ESTADO_CAMINANDO;
        } else if (mueveDer && !mueveIzq) {
            velocidad.x = VELOCIDAD_CAMINAR;
            if (enSuelo) estadoActual = ESTADO_CAMINANDO;
        } else {
            velocidad.x *= FRICCION_SUELO;
            if (enSuelo && estadoActual == ESTADO_CAMINANDO) {
                estadoActual = ESTADO_IDLE;
            }
        }
    }
}

void PersonajeFighter::actualizar(float dt, float nivelSuelo, float posXEnemigo) {
    tiempoAnimacion += dt;

    // Actualizar duracion de mensajes flotantes
    if (tiempoMensajeCombate > 0.0f) {
        tiempoMensajeCombate -= dt;
        if (tiempoMensajeCombate < 0.0f) tiempoMensajeCombate = 0.0f;
    }

    // Reducir suavemente la barra de daño retardado
    if (saludRetardada > salud) {
        saludRetardada -= 25.0f * dt;
        if (saludRetardada < salud) saludRetardada = salud;
    }

    // Cooldown de esquive / parry
    if (enfriamientoParry > 0.0f) {
        enfriamientoParry -= dt;
        if (enfriamientoParry < 0.0f) enfriamientoParry = 0.0f;
    }

    // Regeneracion pasiva del escudo de bloqueo si no esta bloqueando ni aturdido
    if (estadoActual != ESTADO_BLOQUEO && estadoActual != ESTADO_ATURDIDO && estadoActual != ESTADO_DERROTADO) {
        if (escudo < escudoMax) {
            escudo += recargaEscudoPorSeg * dt;
            if (escudo > escudoMax) escudo = escudoMax;
        }
    }

    // Fisicas de gravedad y salto
    if (!enSuelo) {
        velocidad.y -= GRAVEDAD;
        posicion.y += velocidad.y;

        if (posicion.y <= nivelSuelo) {
            posicion.y = nivelSuelo;
            velocidad.y = 0.0f;
            enSuelo = true;
            if (estadoActual == ESTADO_SALTANDO) {
                estadoActual = ESTADO_IDLE;
            }
        }
    }

    // Aplicar velocidad horizontal y friccion
    posicion.x += velocidad.x;
    if (enSuelo) {
        velocidad.x *= FRICCION_SUELO;
        if (std::abs(velocidad.x) < 0.0005f) velocidad.x = 0.0f;
    }

    // Orientar siempre hacia el rival si esta de pie
    if (estadoActual == ESTADO_IDLE || estadoActual == ESTADO_CAMINANDO || estadoActual == ESTADO_SALTANDO) {
        if (posicion.x < posXEnemigo) {
            direccion = 1;
        } else {
            direccion = -1;
        }
    }

    // Maquina de estados por tiempo
    if (temporizadorEstado > 0.0f) {
        temporizadorEstado -= dt;
        if (temporizadorEstado <= 0.0f) {
            temporizadorEstado = 0.0f;

            if (estadoActual == ESTADO_POSTURA_PARRY) {
                // REQUISITO: Si no le pegan en la ventana de esquive, se queda parado como castigo
                estadoActual = ESTADO_CASTIGO_PARRY;
                temporizadorEstado = 0.65f; // Duracion del castigo
                setMensajeCombate("FALLO PARRY!", 0.65f);
            } else if (estadoActual == ESTADO_CASTIGO_PARRY) {
                estadoActual = ESTADO_IDLE;
            } else if (estadoActual == ESTADO_GOLPE_SUAVE ||
                       estadoActual == ESTADO_GOLPE_FUERTE ||
                       estadoActual == ESTADO_CONTRAATAQUE ||
                       estadoActual == ESTADO_HERIDO) {
                hitboxAtaque.activa = false;
                estadoActual = enSuelo ? ESTADO_IDLE : ESTADO_SALTANDO;
            }
        }
    }

    // Estado Aturdido (Stun por rompimiento de guardia o impacto)
    if (estadoActual == ESTADO_ATURDIDO) {
        temporizadorAturdimiento -= dt;
        velocidad.x = 0.0f;
        hitboxAtaque.activa = false;
        if (temporizadorAturdimiento <= 0.0f) {
            temporizadorAturdimiento = 0.0f;
            estadoActual = ESTADO_IDLE;
            escudo = 30.0f; // Recupera un poco de escudo tras salir del aturdimiento
        }
    }

    actualizarHitboxYHurtbox();
}

void PersonajeFighter::actualizarHitboxYHurtbox() {
    float altoPersonaje = (estadoActual == ESTADO_AGACHADO) ? 0.20f : 0.38f;
    float anchoPersonaje = 0.14f;

    // Configurar Hurtbox (area vulnerable del cuerpo)
    hurtboxCuerpo.configurar(posicion.x - anchoPersonaje * 0.5f,
                            posicion.y,
                            anchoPersonaje,
                            altoPersonaje,
                            estadoActual != ESTADO_DERROTADO);

    // Configurar Hitbox (area de impacto ofensivo en frente del personaje)
    if (hitboxAtaque.activa) {
        float anchoGolpe = (hitboxAtaque.datosGolpe.esFuerte) ? 0.16f : 0.12f;
        float altoGolpe  = (hitboxAtaque.datosGolpe.esFuerte) ? 0.14f : 0.10f;
        float golpeX = (direccion >= 0) ? (posicion.x + 0.04f) : (posicion.x - 0.04f - anchoGolpe);
        float golpeY = posicion.y + 0.14f;

        hitboxAtaque.configurar(golpeX, golpeY, anchoGolpe, altoGolpe, true);
    }
}

bool PersonajeFighter::recibirGolpe(const PropiedadesGolpe& golpe, float direccionEmpuje) {
    if (estadoActual == ESTADO_DERROTADO) return false;

    // 1. REQUISITO: Si esta en POSTURA_PARRY -> ¡Contraataque exitoso!
    if (estadoActual == ESTADO_POSTURA_PARRY) {
        setMensajeCombate("COUNTER!", 1.0f);
        // Desatar contraataque inmediato y cancelar el golpe rival
        dispararAtaque(ESTADO_CONTRAATAQUE, 0.40f, 22.0f, 35.0f, 0.11f, 0.015f, true);
        velocidad.x = direccion * 0.02f; // Se abalanza hacia adelante en contraataque
        return false; // El golpe del rival fue bloqueado y anulado
    }

    // 2. BLOQUEO: Se absorbe con el medidor de escudo
    if (estadoActual == ESTADO_BLOQUEO && escudo > 0.0f) {
        escudo -= golpe.danioEscudo;
        setMensajeCombate("BLOQUEADO", 0.6f);
        velocidad.x = direccionEmpuje * (golpe.empujeX * 0.4f); // Empuje reducido

        // Si el escudo se rompe -> GUARD BREAK y ATURDIMIENTO
        if (escudo <= 0.0f) {
            escudo = 0.0f;
            estadoActual = ESTADO_ATURDIDO;
            temporizadorAturdimiento = 1.8f;
            setMensajeCombate("GUARD BREAK!", 1.5f);
        }
        return false;
    }

    // 3. IMPACTO DIRECTO A LA SALUD
    salud -= golpe.danioSalud;
    if (salud < 0.0f) salud = 0.0f;

    velocidad.x = direccionEmpuje * golpe.empujeX;
    velocidad.y = golpe.empujeY;
    if (golpe.empujeY > 0.001f) enSuelo = false;

    if (salud <= 0.0f) {
        estadoActual = ESTADO_DERROTADO;
        temporizadorEstado = 999.0f;
        hitboxAtaque.activa = false;
        setMensajeCombate("K.O.!", 2.0f);
    } else {
        // Si el golpe causa aturdimiento directo
        if (golpe.causaAturdimiento) {
            estadoActual = ESTADO_ATURDIDO;
            temporizadorAturdimiento = 1.5f;
            setMensajeCombate("ATURDIDO!", 1.5f);
        } else {
            estadoActual = ESTADO_HERIDO;
            temporizadorEstado = 0.25f;
        }
    }

    hitboxAtaque.activa = false;
    return true;
}

void PersonajeFighter::renderizar() {
    int codEstado = 0;
    switch (estadoActual) {
        case ESTADO_IDLE:          codEstado = 0; break;
        case ESTADO_CAMINANDO:     codEstado = 1; break;
        case ESTADO_SALTANDO:      codEstado = 2; break;
        case ESTADO_AGACHADO:      codEstado = 3; break;
        case ESTADO_GOLPE_SUAVE:   codEstado = 4; break;
        case ESTADO_GOLPE_FUERTE:  codEstado = 5; break;
        case ESTADO_BLOQUEO:       codEstado = 6; break;
        case ESTADO_POSTURA_PARRY: codEstado = 7; break; // Pose esquive Leonardox/Guadalupe
        case ESTADO_CONTRAATAQUE:  codEstado = 8; break;
        case ESTADO_CASTIGO_PARRY: codEstado = 9; break; // Castigo indefenso
        case ESTADO_DERROTADO:     codEstado = 10; break;
        case ESTADO_HERIDO:        codEstado = 1; break;
        case ESTADO_ATURDIDO:      codEstado = 0; break;
        case ESTADO_VICTORIA:      codEstado = 7; break;
        default:                   codEstado = 0; break;
    }

    bool aturd = (estadoActual == ESTADO_ATURDIDO);

    if (tipo == PERSONAJE_LEONARDOX) {
        renderizarLeonardox(posicion.x, posicion.y, direccion, codEstado,
                            tiempoAnimacion, salud, escudo, aturd);
    } else {
        renderizarGuadalupe(posicion.x, posicion.y, direccion, codEstado,
                            tiempoAnimacion, salud, escudo, aturd);
    }

    // Renderizado de texto flotante de combate ("COUNTER!", "GUARD BREAK!", etc.)
    if (tiempoMensajeCombate > 0.0f) {
        float flotanteY = posicion.y + 0.42f + (1.0f - (tiempoMensajeCombate / 1.0f)) * 0.05f;
        float r = 1.0f, g = 0.9f, b = 0.1f;
        if (mensajeCombate == "COUNTER!") { r = 1.0f; g = 0.2f; b = 0.2f; }
        else if (mensajeCombate == "GUARD BREAK!") { r = 0.9f; g = 0.4f; b = 1.0f; }
        else if (mensajeCombate == "BLOQUEADO") { r = 0.3f; g = 0.8f; b = 1.0f; }

        dibujarTextoConSombra(mensajeCombate.c_str(), posicion.x - 0.08f, flotanteY,
                              GLUT_BITMAP_HELVETICA_18, r, g, b);
    }
}
