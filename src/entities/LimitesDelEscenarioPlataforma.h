#ifndef LIMITES_ESCENARIO_PLATAFORMA_H
#define LIMITES_ESCENARIO_PLATAFORMA_H

/**
 * ============================================================================
 * MODULO: LimitesDelEscenarioPlataforma
 * ============================================================================
 * Gestiona los limites espaciales de la arena (suelo y paredes izquierda/derecha)
 * y la mecanica de rotura de escenario / transicion cuando un luchador recibe un
 * impacto fuerte contra el borde del mapa.
 */

enum TipoEscenario {
    ESCENARIO_PARQUE = 0,
    ESCENARIO_UNIVERSIDAD,
    TOTAL_ESCENARIOS
};

class LimitesEscenario {
private:
    float limiteIzquierdo;
    float limiteDerecho;
    float nivelSuelo;

    TipoEscenario escenarioActual;
    bool enTransicion;
    float temporizadorTransicion;
    float tiempoAlertaTransicion;

    // Efecto de vibracion/sacudida de camara (Screen Shake) tras golpes contundentes
    float temblorX;
    float temblorY;
    float duracionTemblor;

    // Semilla para variaciones procedurales de los objetos del mapa
    int variacionObjetos;

public:
    LimitesEscenario();

    void inicializar(TipoEscenario escenarioInicial = ESCENARIO_PARQUE);
    void actualizar(float dt);

    // Verificacion y correccion de posicion de personajes
    void mantenerDentroDeLimites(float& posX, float anchoPersonaje);
    bool estaEnSuelo(float posY) const;
    float getSueloY() const { return nivelSuelo; }
    float getLimiteIzquierdo() const { return limiteIzquierdo; }
    float getLimiteDerecho() const { return limiteDerecho; }

    // Mecanica de impacto contra el borde:
    // Si un jugador recibe un golpe fuerte cerca del borde, activa la rotura del escenario
    bool verificarImpactoBorde(float posX, bool fueGolpeFuerte);

    // Control de escenarios y transicion
    void cambiarEscenario(TipoEscenario nuevoEscenario);
    void transicionarSiguienteEscenario();
    TipoEscenario getTipoEscenario() const { return escenarioActual; }
    int getVariacionObjetos() const { return variacionObjetos; }

    bool hayAlertaTransicion() const { return tiempoAlertaTransicion > 0.0f; }

    // Screen Shake
    void aplicarTemblor(float intensidad, float duracion);
    float getTemblorX() const { return temblorX; }
    float getTemblorY() const { return temblorY; }
};

#endif // LIMITES_ESCENARIO_PLATAFORMA_H
