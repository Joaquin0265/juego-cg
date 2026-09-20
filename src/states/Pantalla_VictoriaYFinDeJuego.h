#ifndef PANTALLA_VICTORIA_FIN_JUEGO_H
#define PANTALLA_VICTORIA_FIN_JUEGO_H

#include "entities/AtributosPersonaje_VidaPosicionEstado.h"

/**
 * ============================================================================
 * MODULO: Pantalla_VictoriaYFinDeJuego
 * ============================================================================
 * Pantalla que se muestra al finalizar el combate cuando un jugador gana
 * 2 rondas. Presenta al ganador con animacion de celebracion y opciones
 * de revancha o volver al menu.
 */

class PantallaVictoriaYFinDeJuego {
private:
    TipoPersonaje ganador;
    int idGanador;
    int opcionSeleccionada; // 0 = Revancha, 1 = Seleccion, 2 = Menu Principal
    float tiempoAnim;

public:
    PantallaVictoriaYFinDeJuego();

    void configurarGanador(TipoPersonaje _ganador, int _idGanador);
    void actualizar(float dt);
    void renderizar();
    void manejarTeclas(unsigned char tecla, bool esEspecial);

    int getOpcionSeleccionada() const { return opcionSeleccionada; }
};

#endif // PANTALLA_VICTORIA_FIN_JUEGO_H
