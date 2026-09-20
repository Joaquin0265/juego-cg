#ifndef ATRIBUTOS_PERSONAJE_VIDA_POSICION_ESTADO_H
#define ATRIBUTOS_PERSONAJE_VIDA_POSICION_ESTADO_H

#include "core/VectoresYMatematicas2D.h"
#include "entities/CajasDeGolpeYDanio_Hitbox.h"
#include <string>

/**
 * ============================================================================
 * PLANTILLA DE JUGADOR: AtributosPersonaje_VidaPosicionEstado
 * ============================================================================
 * Clase base completa y reutilizable que modela a cualquier luchador 2D:
 * - Movimiento lateral, salto con gravedad y agacharse.
 * - Barra de vida (100 HP) con degradado y reduccion retardada en UI.
 * - Barra de escudo/bloqueo (100 SP): se desgasta al absorber ataques. Si llega
 *   a 0, sufre un "Guard Break" y entra en Aturdimiento (Stun).
 * - Mecanica de Parry / Esquive y Contraataque:
 *   Tiene una ventana activa (~0.35s); si el rival ataca en ese instante, el
 *   golpe es anulado y ejecuta un contraataque demoledor. Si nadie golpea,
 *   entra en estado de castigo vulnerable e indefenso (~0.65s).
 * - Animaciones unicas: Leonardox levanta un brazo; Guadalupe se toca la cara.
 * - Sistema modular de Hurtbox y Hitbox AABB.
 */

enum EstadoFighter {
    ESTADO_IDLE = 0,
    ESTADO_CAMINANDO = 1,
    ESTADO_SALTANDO = 2,
    ESTADO_AGACHADO = 3,
    ESTADO_GOLPE_SUAVE = 4,
    ESTADO_GOLPE_FUERTE = 5,
    ESTADO_BLOQUEO = 6,
    ESTADO_POSTURA_PARRY = 7,  // Esperando el golpe rival
    ESTADO_CONTRAATAQUE = 8,   // Golpe veloz tras parry exitoso
    ESTADO_CASTIGO_PARRY = 9,  // Castigo por fallar el parry (congelado)
    ESTADO_DERROTADO = 10,     // KO en el suelo
    ESTADO_HERIDO = 11,        // Impacto recibido
    ESTADO_ATURDIDO = 12,      // Mareado con estrellas en la cabeza
    ESTADO_VICTORIA = 13       // Pose de triunfo
};

enum TipoPersonaje {
    PERSONAJE_LEONARDOX = 0,
    PERSONAJE_GUADALUPE = 1
};

class PersonajeFighter {
private:
    int idJugador;              // 1 para P1, 2 para P2
    TipoPersonaje tipo;         // LEONARDOX o GUADALUPE
    std::string nombre;

    // Transformaciones y fisicas
    Vector2D posicion;
    Vector2D velocidad;
    int direccion;              // +1: mira a la derecha, -1: mira a la izquierda
    bool enSuelo;

    // Estadisticas de combate
    float saludMax;
    float salud;
    float saludRetardada;       // Para transicion suave en la barra de vida

    float escudoMax;            // Medidor de bloqueo
    float escudo;               // Vida del bloqueo
    float recargaEscudoPorSeg;  // Regeneracion pasiva si no bloquea
    bool guardiaRota;           // True si el escudo llego a 0

    int roundsGanados;

    // Maquina de estados y temporizadores
    EstadoFighter estadoActual;
    float temporizadorEstado;
    float temporizadorAturdimiento;
    float enfriamientoParry;    // Cooldown para evitar spam de esquive
    float tiempoAnimacion;

    // Cajas de colision
    CajaColision hurtboxCuerpo;
    CajaColision hitboxAtaque;

    // Mensajes flotantes de combate
    std::string mensajeCombate;
    float tiempoMensajeCombate;

public:
    PersonajeFighter();

    // Inicializacion y reinicio
    void inicializar(int _idJugador, TipoPersonaje _tipo, float posXInicial, float nivelSuelo, int dirInicial);
    void reiniciarRonda(float posXInicial, float nivelSuelo, int dirInicial);

    // Bucle de juego
    void procesarEntrada(float dt);
    void actualizar(float dt, float nivelSuelo, float posXEnemigo);
    void renderizar();

    // Sistema de combate
    // Retorna true si el golpe fue asestado con exito, false si fue bloqueado o repelido por parry
    bool recibirGolpe(const PropiedadesGolpe& golpe, float direccionEmpuje);

    // Getters y utilidades
    int getId() const { return idJugador; }
    TipoPersonaje getTipo() const { return tipo; }
    const std::string& getNombre() const { return nombre; }
    void setTipo(TipoPersonaje nuevoTipo);

    Vector2D getPosicion() const { return posicion; }
    void setPosicionX(float px) { posicion.x = px; }
    float getSalud() const { return salud; }
    float getSaludMax() const { return saludMax; }
    float getSaludRetardada() const { return saludRetardada; }
    float getEscudo() const { return escudo; }
    float getEscudoMax() const { return escudoMax; }
    int getDireccion() const { return direccion; }
    EstadoFighter getEstado() const { return estadoActual; }
    bool estaAturdido() const { return estadoActual == ESTADO_ATURDIDO; }
    bool estaDerrotado() const { return salud <= 0.0f; }
    bool estaEnSuelo() const { return enSuelo; }

    int getRoundsGanados() const { return roundsGanados; }
    void sumarRoundGanado() { roundsGanados++; }
    void resetearRounds() { roundsGanados = 0; }

    const CajaColision& getHurtbox() const { return hurtboxCuerpo; }
    const CajaColision& getHitbox() const { return hitboxAtaque; }
    void desactivarHitbox() { hitboxAtaque.activa = false; }

    const std::string& getMensajeCombate() const { return mensajeCombate; }
    bool tieneMensajeCombate() const { return tiempoMensajeCombate > 0.0f; }
    void setMensajeCombate(const std::string& msj, float duracion = 1.0f);

private:
    void actualizarHitboxYHurtbox();
    void dispararAtaque(EstadoFighter estadoAtaque, float duracion, float danio, float danioEsc, float empujeX, float empujeY, bool esFuerte);
};

#endif // ATRIBUTOS_PERSONAJE_VIDA_POSICION_ESTADO_H
