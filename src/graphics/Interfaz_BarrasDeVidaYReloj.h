#ifndef INTERFAZ_BARRAS_VIDA_RELOJ_H
#define INTERFAZ_BARRAS_VIDA_RELOJ_H

#include "entities/AtributosPersonaje_VidaPosicionEstado.h"

/**
 * ============================================================================
 * MODULO: Interfaz_BarrasDeVidaYReloj (HUD)
 * ============================================================================
 * Renderiza la interfaz grafica durante el combate:
 * - Barras de vida de P1 y P2 con indicador de daño retardado (barra amarilla).
 * - Barras de escudo/bloqueo debajo de la vida (cambia de color cuando se agota).
 * - Reloj central de 99 segundos.
 * - Marcadores de rounds ganados.
 * - Letreros centrales para "FIGHT!", "K.O.", "STAGE BREAK!", etc.
 * - Guia rapida de controles en la parte inferior.
 */

class InterfazCombate {
private:
    float tiempoTotal;

public:
    InterfazCombate();

    void renderizar(const PersonajeFighter& p1, const PersonajeFighter& p2,
                    int tiempoRestante, int roundActual,
                    const char* mensajeCentral, bool alertaTransicionEscenario);

private:
    void dibujarBarraJugador(float x, float y, float ancho, float alto,
                             const PersonajeFighter& p, bool invertida);
    void dibujarMarcadorRounds(float x, float y, int roundsGanados, bool invertida);
};

#endif // INTERFAZ_BARRAS_VIDA_RELOJ_H
