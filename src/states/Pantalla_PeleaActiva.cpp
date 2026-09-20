#include "states/Pantalla_PeleaActiva.h"
#include "graphics/FuncionesParaDibujarFigurasBasicas.h"
#include <GL/freeglut.h>
#include <cstdio>
#include <cmath>

Pantalla_PeleaActiva::Pantalla_PeleaActiva() {
    tiempoRestante = 99;
    acumuladorSegundo = 0.0f;
    roundActual = 1;
    faseActual = FASE_INTRO_ROUND;
    temporizadorFase = 1.6f;
    enPausa = false;
    opcionPausa = 0;
    tipoP1 = PERSONAJE_LEONARDOX;
    tipoP2 = PERSONAJE_GUADALUPE;
    mapaActual = ESCENARIO_PARQUE;
}

void Pantalla_PeleaActiva::inicializarCombate(TipoPersonaje p1, TipoPersonaje p2, TipoEscenario mapa) {
    tipoP1 = p1;
    tipoP2 = p2;
    mapaActual = mapa;

    limites.inicializar(mapaActual);

    jugador1.inicializar(1, tipoP1, -0.45f, limites.getSueloY(), 1);
    jugador2.inicializar(2, tipoP2, 0.45f, limites.getSueloY(), -1);

    roundActual = 1;
    iniciarNuevaRonda();
    enPausa = false;
    opcionPausa = 0;
}

void Pantalla_PeleaActiva::iniciarNuevaRonda() {
    tiempoRestante = 99;
    acumuladorSegundo = 0.0f;
    faseActual = FASE_INTRO_ROUND;
    temporizadorFase = 1.4f;

    char buf[32];
    std::snprintf(buf, sizeof(buf), "ROUND %d", roundActual);
    mensajeCentral = buf;

    jugador1.reiniciarRonda(-0.45f, limites.getSueloY(), 1);
    jugador2.reiniciarRonda(0.45f, limites.getSueloY(), -1);
}

void Pantalla_PeleaActiva::verificarColisionesCombate() {
    // 1. Verificar si el ataque de P1 impacta la hurtbox de P2
    if (jugador1.getHitbox().activa) {
        if (jugador1.getHitbox().caja.intersecta(jugador2.getHurtbox().caja)) {
            float dirEmpuje = (jugador1.getPosicion().x <= jugador2.getPosicion().x) ? 1.0f : -1.0f;
            const PropiedadesGolpe& datos = jugador1.getHitbox().datosGolpe;

            bool impactoLimpio = jugador2.recibirGolpe(datos, dirEmpuje);
            jugador1.desactivarHitbox(); // Desactivar hitbox para no dañar en frames consecutivos

            // REQUISITO: Rotura/cambio de escenario al recibir golpe fuerte en el borde
            if (impactoLimpio && datos.esFuerte) {
                limites.verificarImpactoBorde(jugador2.getPosicion().x, true);
            }
        }
    }

    // 2. Verificar si el ataque de P2 impacta la hurtbox de P1
    if (jugador2.getHitbox().activa) {
        if (jugador2.getHitbox().caja.intersecta(jugador1.getHurtbox().caja)) {
            float dirEmpuje = (jugador2.getPosicion().x <= jugador1.getPosicion().x) ? 1.0f : -1.0f;
            const PropiedadesGolpe& datos = jugador2.getHitbox().datosGolpe;

            bool impactoLimpio = jugador1.recibirGolpe(datos, dirEmpuje);
            jugador2.desactivarHitbox();

            // REQUISITO: Rotura/cambio de escenario al recibir golpe fuerte en el borde
            if (impactoLimpio && datos.esFuerte) {
                limites.verificarImpactoBorde(jugador1.getPosicion().x, true);
            }
        }
    }
}

void Pantalla_PeleaActiva::actualizar(float dt) {
    if (enPausa) return;

    limites.actualizar(dt);

    // Maquina de fases de la ronda
    if (faseActual == FASE_INTRO_ROUND) {
        temporizadorFase -= dt;
        if (temporizadorFase <= 0.0f) {
            faseActual = FASE_FIGHT;
            temporizadorFase = 0.8f;
            mensajeCentral = "¡FIGHT!";
        }
    } else if (faseActual == FASE_FIGHT) {
        temporizadorFase -= dt;
        if (temporizadorFase <= 0.0f) {
            faseActual = FASE_COMBATE_ACTIVO;
            mensajeCentral = "";
        }
    } else if (faseActual == FASE_COMBATE_ACTIVO) {
        // Reloj regresivo
        acumuladorSegundo += dt;
        if (acumuladorSegundo >= 1.0f) {
            acumuladorSegundo -= 1.0f;
            if (tiempoRestante > 0) {
                tiempoRestante--;
            }
        }

        // Procesar controles de combate de ambos jugadores
        jugador1.procesarEntrada(dt);
        jugador2.procesarEntrada(dt);

        // Actualizar fisicas y posiciones
        jugador1.actualizar(dt, limites.getSueloY(), jugador2.getPosicion().x);
        jugador2.actualizar(dt, limites.getSueloY(), jugador1.getPosicion().x);

        // Mantener a los jugadores dentro de los limites del escenario
        float p1X = jugador1.getPosicion().x;
        limites.mantenerDentroDeLimites(p1X, 0.14f);
        jugador1.setPosicionX(p1X);

        float p2X = jugador2.getPosicion().x;
        limites.mantenerDentroDeLimites(p2X, 0.14f);
        jugador2.setPosicionX(p2X);

        // Comprobacion de colisiones ofensivas y defensivas
        verificarColisionesCombate();

        // Comprobar fin de la ronda por KO o tiempo
        if (jugador1.estaDerrotado() || jugador2.estaDerrotado() || tiempoRestante <= 0) {
            faseActual = FASE_KO;
            temporizadorFase = 2.4f;

            if (jugador1.estaDerrotado() && !jugador2.estaDerrotado()) {
                mensajeCentral = "¡K.O. - GANA P2!";
                jugador2.sumarRoundGanado();
            } else if (jugador2.estaDerrotado() && !jugador1.estaDerrotado()) {
                mensajeCentral = "¡K.O. - GANA P1!";
                jugador1.sumarRoundGanado();
            } else if (tiempoRestante <= 0) {
                // Decision por mayor salud restante
                if (jugador1.getSalud() > jugador2.getSalud()) {
                    mensajeCentral = "¡TIME OVER - GANA P1!";
                    jugador1.sumarRoundGanado();
                } else if (jugador2.getSalud() > jugador1.getSalud()) {
                    mensajeCentral = "¡TIME OVER - GANA P2!";
                    jugador2.sumarRoundGanado();
                } else {
                    mensajeCentral = "¡EMPATE!";
                }
            }
        }
    } else if (faseActual == FASE_KO) {
        temporizadorFase -= dt;

        // Actualizar fisicas para que caigan y se asiente el impacto
        jugador1.actualizar(dt, limites.getSueloY(), jugador2.getPosicion().x);
        jugador2.actualizar(dt, limites.getSueloY(), jugador1.getPosicion().x);

        if (temporizadorFase <= 0.0f) {
            // Verificar si alguien alcanzo 2 rounds ganados
            if (jugador1.getRoundsGanados() >= 2 || jugador2.getRoundsGanados() >= 2) {
                faseActual = FASE_FIN_COMBATE;
            } else {
                roundActual++;
                iniciarNuevaRonda();
            }
        }
    }
}

TipoPersonaje Pantalla_PeleaActiva::getGanadorCombate() const {
    if (jugador1.getRoundsGanados() >= jugador2.getRoundsGanados()) {
        return jugador1.getTipo();
    }
    return jugador2.getTipo();
}

int Pantalla_PeleaActiva::getIdGanadorCombate() const {
    if (jugador1.getRoundsGanados() >= jugador2.getRoundsGanados()) {
        return 1;
    }
    return 2;
}

void Pantalla_PeleaActiva::moverSeleccionPausa(int dir) {
    opcionPausa += dir;
    if (opcionPausa < 0) opcionPausa = 2;
    if (opcionPausa > 2) opcionPausa = 0;
}

void Pantalla_PeleaActiva::renderizarMenuPausa() {
    // 1. Capa oscura traslucida
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glColor4f(0.0f, 0.0f, 0.0f, 0.70f);
    glBegin(GL_QUADS);
        glVertex2f(-1.0f, -1.0f);
        glVertex2f( 1.0f, -1.0f);
        glVertex2f( 1.0f,  1.0f);
        glVertex2f(-1.0f,  1.0f);
    glEnd();
    glDisable(GL_BLEND);

    // 2. Ventana de Pausa
    dibujarRectangulo(-0.40f, -0.35f, 0.80f, 0.70f, 0.08f, 0.10f, 0.18f, true);
    dibujarRectangulo(-0.40f, -0.35f, 0.80f, 0.70f, 0.95f, 0.80f, 0.20f, false);

    dibujarTextoConSombra("JUEGO EN PAUSA", -0.22f, 0.22f, GLUT_BITMAP_TIMES_ROMAN_24, 1.0f, 0.85f, 0.20f);

    const char* opcionesPausa[3] = {
        "REANUDAR COMBATE",
        "CONFIGURACION Y TECLAS",
        "VOLVER AL MENU PRINCIPAL"
    };

    float yBase = 0.06f;
    float sep = 0.13f;

    for (int i = 0; i < 3; i++) {
        float y = yBase - (float)i * sep;
        bool sel = (opcionPausa == i);

        if (sel) {
            dibujarRectangulo(-0.35f, y - 0.03f, 0.70f, 0.08f, 0.15f, 0.35f, 0.55f, true);
            dibujarRectangulo(-0.35f, y - 0.03f, 0.70f, 0.08f, 0.2f, 1.0f, 0.6f, false);
            dibujarTextoConSombra(">", -0.32f, y, GLUT_BITMAP_HELVETICA_18, 0.2f, 1.0f, 0.6f);
            dibujarTextoConSombra(opcionesPausa[i], -0.26f, y, GLUT_BITMAP_HELVETICA_18, 0.2f, 1.0f, 0.6f);
        } else {
            dibujarRectangulo(-0.35f, y - 0.03f, 0.70f, 0.08f, 0.10f, 0.12f, 0.18f, true);
            dibujarRectangulo(-0.35f, y - 0.03f, 0.70f, 0.08f, 0.30f, 0.30f, 0.35f, false);
            dibujarTexto(opcionesPausa[i], -0.26f, y, GLUT_BITMAP_HELVETICA_18, 0.8f, 0.8f, 0.8f);
        }
    }
}

void Pantalla_PeleaActiva::renderizar() {
    glPushMatrix();

    // Aplicar temblor de camara (Screen Shake) si hubo impacto fuerte contra la pared
    glTranslatef(limites.getTemblorX(), limites.getTemblorY(), 0.0f);

    // 1. Escenario Procedural 100% Vectorial (Parque o Universidad)
    renderizadorEscenario.renderizar(limites.getTipoEscenario(),
                                    limites.getVariacionObjetos(),
                                    limites.getSueloY());

    // 2. Renderizado de los luchadores
    jugador1.renderizar();
    jugador2.renderizar();

    glPopMatrix();

    // 3. HUD (Barras de Vida, Escudo, Reloj, avisos de combate)
    hud.renderizar(jugador1, jugador2, tiempoRestante, roundActual,
                   mensajeCentral.c_str(), limites.hayAlertaTransicion());

    // 4. Overlay de Pausa si esta pausado
    if (enPausa) {
        renderizarMenuPausa();
    }
}

void Pantalla_PeleaActiva::manejarTeclas(unsigned char tecla, bool esEspecial) {
    if (!esEspecial && tecla == 27) { // ESC para alternar pausa
        alternarPausa();
        return;
    }

    if (enPausa) {
        if (esEspecial) {
            if (tecla == GLUT_KEY_UP) moverSeleccionPausa(-1);
            if (tecla == GLUT_KEY_DOWN) moverSeleccionPausa(1);
        }
    }
}
