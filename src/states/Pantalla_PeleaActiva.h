#ifndef PANTALLA_PELEA_ACTIVA_H
#define PANTALLA_PELEA_ACTIVA_H

#include "entities/AtributosPersonaje_VidaPosicionEstado.h"
#include "entities/LimitesDelEscenarioPlataforma.h"
#include "graphics/DibujoFondoEscenario_MontaniasEdificios.h"
#include "graphics/Interfaz_BarrasDeVidaYReloj.h"
#include <string>

/**
 * ============================================================================
 * MODULO: Pantalla_PeleaActiva
 * ============================================================================
 * Administra el estado central de combate:
 * - Ciclo de rondas (Round 1, Round 2, Round Final) al mejor de 3.
 * - Temporizador regresivo de 99 segundos.
 * - Comprobación de colisiones entre Hitbox ofensiva y Hurtbox defensiva.
 * - Mecánica de rotura y cambio de escenario al recibir golpes fuertes en el borde.
 * - Menú de pausa interactivo con overlay traslúcido.
 */

enum FaseRonda {
    FASE_INTRO_ROUND = 0,
    FASE_FIGHT,
    FASE_COMBATE_ACTIVO,
    FASE_KO,
    FASE_FIN_COMBATE
};

class Pantalla_PeleaActiva {
private:
    PersonajeFighter jugador1;
    PersonajeFighter jugador2;
    LimitesEscenario limites;
    RenderizadorEscenario renderizadorEscenario;
    InterfazCombate hud;

    int tiempoRestante;
    float acumuladorSegundo;
    int roundActual;
    FaseRonda faseActual;
    float temporizadorFase;
    std::string mensajeCentral;

    bool enPausa;
    int opcionPausa; // 0 = Reanudar, 1 = Opciones, 2 = Menu Principal

    TipoPersonaje tipoP1;
    TipoPersonaje tipoP2;
    TipoEscenario mapaActual;

public:
    Pantalla_PeleaActiva();

    void inicializarCombate(TipoPersonaje p1, TipoPersonaje p2, TipoEscenario mapa);
    void actualizar(float dt);
    void renderizar();
    void manejarTeclas(unsigned char tecla, bool esEspecial);

    void alternarPausa() { enPausa = !enPausa; opcionPausa = 0; }
    bool estaEnPausa() const { return enPausa; }
    void moverSeleccionPausa(int dir);
    int getOpcionPausa() const { return opcionPausa; }

    bool combateTerminado() const { return faseActual == FASE_FIN_COMBATE; }
    TipoPersonaje getGanadorCombate() const;
    int getIdGanadorCombate() const;

private:
    void iniciarNuevaRonda();
    void verificarColisionesCombate();
    void renderizarMenuPausa();
};

#endif // PANTALLA_PELEA_ACTIVA_H
