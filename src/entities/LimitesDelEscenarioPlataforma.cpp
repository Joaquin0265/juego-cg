#include "entities/LimitesDelEscenarioPlataforma.h"
#include <cstdlib>
#include <cmath>

LimitesEscenario::LimitesEscenario() {
    limiteIzquierdo = -0.92f;
    limiteDerecho = 0.92f;
    nivelSuelo = -0.45f;
    escenarioActual = ESCENARIO_PARQUE;
    enTransicion = false;
    temporizadorTransicion = 0.0f;
    tiempoAlertaTransicion = 0.0f;
    temblorX = 0.0f;
    temblorY = 0.0f;
    duracionTemblor = 0.0f;
    variacionObjetos = 0;
}

void LimitesEscenario::inicializar(TipoEscenario escenarioInicial) {
    escenarioActual = escenarioInicial;
    enTransicion = false;
    temporizadorTransicion = 0.0f;
    tiempoAlertaTransicion = 0.0f;
    temblorX = 0.0f;
    temblorY = 0.0f;
    duracionTemblor = 0.0f;
    variacionObjetos = std::rand() % 3;
}

void LimitesEscenario::actualizar(float dt) {
    // Actualizar duracion de la alerta visual de cambio de escenario
    if (tiempoAlertaTransicion > 0.0f) {
        tiempoAlertaTransicion -= dt;
        if (tiempoAlertaTransicion < 0.0f) {
            tiempoAlertaTransicion = 0.0f;
        }
    }

    // Actualizar efecto de temblor de pantalla
    if (duracionTemblor > 0.0f) {
        duracionTemblor -= dt;
        // Pequeño desplazamiento aleatorio proporcional al tiempo restante
        float factor = duracionTemblor * 0.05f;
        temblorX = ((float)(std::rand() % 100) / 50.0f - 1.0f) * factor;
        temblorY = ((float)(std::rand() % 100) / 50.0f - 1.0f) * factor;
        if (duracionTemblor <= 0.0f) {
            temblorX = 0.0f;
            temblorY = 0.0f;
        }
    }
}

void LimitesEscenario::mantenerDentroDeLimites(float& posX, float anchoPersonaje) {
    float mitadAncho = anchoPersonaje * 0.5f;
    if (posX - mitadAncho < limiteIzquierdo) {
        posX = limiteIzquierdo + mitadAncho;
    }
    if (posX + mitadAncho > limiteDerecho) {
        posX = limiteDerecho - mitadAncho;
    }
}

bool LimitesEscenario::estaEnSuelo(float posY) const {
    return posY <= nivelSuelo + 0.001f;
}

bool LimitesEscenario::verificarImpactoBorde(float posX, bool fueGolpeFuerte) {
    if (!fueGolpeFuerte) return false;

    // Si el jugador esta cerca de la pared izquierda o derecha al recibir golpe fuerte
    bool cercaIzquierda = (posX <= limiteIzquierdo + 0.15f);
    bool cercaDerecha   = (posX >= limiteDerecho - 0.15f);

    if (cercaIzquierda || cercaDerecha) {
        // Disparar temblor y transicion
        aplicarTemblor(0.04f, 0.45f);
        transicionarSiguienteEscenario();
        return true;
    }
    return false;
}

void LimitesEscenario::cambiarEscenario(TipoEscenario nuevoEscenario) {
    escenarioActual = nuevoEscenario;
    variacionObjetos = (variacionObjetos + 1) % 3;
}

void LimitesEscenario::transicionarSiguienteEscenario() {
    int siguiente = (int)escenarioActual + 1;
    if (siguiente >= TOTAL_ESCENARIOS) {
        siguiente = 0;
    }
    escenarioActual = (TipoEscenario)siguiente;
    variacionObjetos = (variacionObjetos + 1) % 3;
    tiempoAlertaTransicion = 2.0f; // Mostrar alerta 2 segundos
}

void LimitesEscenario::aplicarTemblor(float intensidad, float duracion) {
    duracionTemblor = duracion;
}
