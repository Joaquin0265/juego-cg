#include "states/AdministradorDePantallasYModos.h"
#include <GL/freeglut.h>
#include <cstdlib>

AdministradorDePantallasYModos::AdministradorDePantallasYModos() {
    pantallaActual = PANTALLA_MENU_PRINCIPAL;
    pantallaAnterior = PANTALLA_MENU_PRINCIPAL;
}

void AdministradorDePantallasYModos::inicializar() {
    pantallaActual = PANTALLA_MENU_PRINCIPAL;
    pantallaAnterior = PANTALLA_MENU_PRINCIPAL;
    menuPrincipal.inicializar();
    seleccion.inicializar();
    opciones.inicializar();
}

void AdministradorDePantallasYModos::cambiarPantalla(PantallaJuego nuevaPantalla) {
    pantallaAnterior = pantallaActual;
    pantallaActual = nuevaPantalla;

    if (pantallaActual == PANTALLA_MENU_PRINCIPAL) {
        menuPrincipal.inicializar();
    } else if (pantallaActual == PANTALLA_SELECCION) {
        seleccion.inicializar();
    } else if (pantallaActual == PANTALLA_OPCIONES) {
        opciones.inicializar();
    }
}

void AdministradorDePantallasYModos::actualizar(float dt) {
    switch (pantallaActual) {
        case PANTALLA_MENU_PRINCIPAL:
            menuPrincipal.actualizar(dt);
            break;

        case PANTALLA_SELECCION:
            seleccion.actualizar(dt);
            if (seleccion.estaListoParaPelear()) {
                seleccion.resetearEstadoListo();
                peleaActiva.inicializarCombate(seleccion.getPersonajeP1(),
                                              seleccion.getPersonajeP2(),
                                              seleccion.getMapa());
                cambiarPantalla(PANTALLA_PELEA);
            }
            break;

        case PANTALLA_PELEA:
            peleaActiva.actualizar(dt);
            if (peleaActiva.combateTerminado()) {
                pantallaVictoria.configurarGanador(peleaActiva.getGanadorCombate(),
                                                  peleaActiva.getIdGanadorCombate());
                cambiarPantalla(PANTALLA_VICTORIA);
            }
            break;

        case PANTALLA_OPCIONES:
            opciones.actualizar(dt);
            break;

        case PANTALLA_VICTORIA:
            pantallaVictoria.actualizar(dt);
            break;
    }
}

void AdministradorDePantallasYModos::renderizarActual() {
    switch (pantallaActual) {
        case PANTALLA_MENU_PRINCIPAL:
            menuPrincipal.renderizar();
            break;

        case PANTALLA_SELECCION:
            seleccion.renderizar();
            break;

        case PANTALLA_PELEA:
            peleaActiva.renderizar();
            break;

        case PANTALLA_OPCIONES:
            opciones.renderizar();
            break;

        case PANTALLA_VICTORIA:
            pantallaVictoria.renderizar();
            break;
    }
}

void AdministradorDePantallasYModos::manejarTeclas(int tecla, bool esEspecial) {
    // 1. MENU PRINCIPAL
    if (pantallaActual == PANTALLA_MENU_PRINCIPAL) {
        if (esEspecial) {
            if (tecla == GLUT_KEY_UP) menuPrincipal.moverSeleccion(-1);
            if (tecla == GLUT_KEY_DOWN) menuPrincipal.moverSeleccion(1);
        } else if (tecla == 13) { // ENTER
            int op = menuPrincipal.getOpcionSeleccionada();
            if (op == 0) { // 1 vs 1 Directo
                peleaActiva.inicializarCombate(PERSONAJE_LEONARDOX, PERSONAJE_GUADALUPE, ESCENARIO_PARQUE);
                cambiarPantalla(PANTALLA_PELEA);
            } else if (op == 1) { // Seleccion
                cambiarPantalla(PANTALLA_SELECCION);
            } else if (op == 2) { // Opciones
                cambiarPantalla(PANTALLA_OPCIONES);
            } else if (op == 3) { // Salir
                std::exit(0);
            }
        }
    }
    // 2. SELECCION DE LUCHADORES Y MAPA
    else if (pantallaActual == PANTALLA_SELECCION) {
        if (!esEspecial && tecla == 27) { // ESC para volver al menu
            cambiarPantalla(PANTALLA_MENU_PRINCIPAL);
        } else {
            seleccion.manejarTeclas((unsigned char)tecla, esEspecial);
        }
    }
    // 3. COMBATE ACTIVO
    else if (pantallaActual == PANTALLA_PELEA) {
        if (!esEspecial && tecla == 27) { // ESC para alternar pausa
            peleaActiva.alternarPausa();
            return;
        }

        if (peleaActiva.estaEnPausa()) {
            if (esEspecial) {
                if (tecla == GLUT_KEY_UP) peleaActiva.moverSeleccionPausa(-1);
                if (tecla == GLUT_KEY_DOWN) peleaActiva.moverSeleccionPausa(1);
            } else if (tecla == 13) { // ENTER dentro de la pausa
                int op = peleaActiva.getOpcionPausa();
                if (op == 0) {
                    peleaActiva.alternarPausa(); // Reanudar
                } else if (op == 1) {
                    cambiarPantalla(PANTALLA_OPCIONES); // Ir a Opciones
                } else if (op == 2) {
                    peleaActiva.alternarPausa();
                    cambiarPantalla(PANTALLA_MENU_PRINCIPAL); // Volver al menu principal
                }
            }
        } else {
            peleaActiva.manejarTeclas((unsigned char)tecla, esEspecial);
        }
    }
    // 4. CONFIGURACION Y OPCIONES
    else if (pantallaActual == PANTALLA_OPCIONES) {
        if (!esEspecial && tecla == 27) { // ESC para salir de opciones
            cambiarPantalla(pantallaAnterior);
        } else {
            opciones.manejarTeclas(tecla, esEspecial);
        }
    }
    // 5. PANTALLA DE VICTORIA
    else if (pantallaActual == PANTALLA_VICTORIA) {
        if (esEspecial) {
            pantallaVictoria.manejarTeclas((unsigned char)tecla, esEspecial);
        } else if (tecla == 13) { // ENTER
            int op = pantallaVictoria.getOpcionSeleccionada();
            if (op == 0) { // Revancha
                peleaActiva.inicializarCombate(seleccion.getPersonajeP1(),
                                              seleccion.getPersonajeP2(),
                                              seleccion.getMapa());
                cambiarPantalla(PANTALLA_PELEA);
            } else if (op == 1) { // Seleccion
                cambiarPantalla(PANTALLA_SELECCION);
            } else if (op == 2) { // Menu Principal
                cambiarPantalla(PANTALLA_MENU_PRINCIPAL);
            }
        }
    }
}
