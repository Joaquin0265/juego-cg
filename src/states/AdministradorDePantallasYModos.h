#ifndef ADMINISTRADOR_DE_PANTALLAS_Y_MODOS_H
#define ADMINISTRADOR_DE_PANTALLAS_Y_MODOS_H

#include "states/Pantalla_MenuPrincipal.h"
#include "states/Pantalla_SeleccionDePersonajeYMapa.h"
#include "states/Pantalla_PeleaActiva.h"
#include "states/Pantalla_Opciones.h"
#include "states/Pantalla_VictoriaYFinDeJuego.h"

/**
 * ============================================================================
 * MODULO: AdministradorDePantallasYModos
 * ============================================================================
 * Gestor central de la maquina de estados del juego (State Machine).
 * Controla el flujo entre Menu Principal, Seleccion, Combate, Opciones y Victoria.
 */

enum PantallaJuego {
    PANTALLA_MENU_PRINCIPAL = 0,
    PANTALLA_SELECCION,
    PANTALLA_PELEA,
    PANTALLA_OPCIONES,
    PANTALLA_VICTORIA
};

class AdministradorDePantallasYModos {
private:
    PantallaJuego pantallaActual;
    PantallaJuego pantallaAnterior;

    Pantalla_MenuPrincipal menuPrincipal;
    PantallaSeleccionDePersonajeYMapa seleccion;
    Pantalla_PeleaActiva peleaActiva;
    PantallaOpciones opciones;
    PantallaVictoriaYFinDeJuego pantallaVictoria;

public:
    AdministradorDePantallasYModos();

    void inicializar();
    void actualizar(float dt);
    void renderizarActual();
    void manejarTeclas(int tecla, bool esEspecial);

    void cambiarPantalla(PantallaJuego nuevaPantalla);
    PantallaJuego getPantallaActual() const { return pantallaActual; }
};

#endif // ADMINISTRADOR_DE_PANTALLAS_Y_MODOS_H
