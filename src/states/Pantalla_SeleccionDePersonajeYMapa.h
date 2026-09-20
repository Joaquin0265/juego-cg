#ifndef PANTALLA_SELECCION_DE_PERSONAJE_Y_MAPA_H
#define PANTALLA_SELECCION_DE_PERSONAJE_Y_MAPA_H

#include "entities/LimitesDelEscenarioPlataforma.h"
#include "entities/AtributosPersonaje_VidaPosicionEstado.h"

/**
 * ============================================================================
 * MODULO: Pantalla_SeleccionDePersonajeYMapa
 * ============================================================================
 * Permite a los jugadores elegir sus luchadores (Leonardox o Guadalupe) y el
 * escenario de combate (El Parque o Entrada de la Universidad) con
 * previsualizaciones vectoriales en tiempo real.
 */

class PantallaSeleccionDePersonajeYMapa {
private:
    TipoPersonaje personajeP1;
    TipoPersonaje personajeP2;
    TipoEscenario mapaSeleccionado;

    float tiempoAnim;
    bool seleccionConfirmada;

public:
    PantallaSeleccionDePersonajeYMapa();

    void inicializar();
    void actualizar(float dt);
    void renderizar();
    void manejarTeclas(unsigned char tecla, bool esEspecial);

    void alternarP1();
    void alternarP2();
    void alternarMapa();

    TipoPersonaje getPersonajeP1() const { return personajeP1; }
    TipoPersonaje getPersonajeP2() const { return personajeP2; }
    TipoEscenario getMapa() const { return mapaSeleccionado; }
    bool estaListoParaPelear() const { return seleccionConfirmada; }
    void resetearEstadoListo() { seleccionConfirmada = false; }
};

#endif // PANTALLA_SELECCION_DE_PERSONAJE_Y_MAPA_H
