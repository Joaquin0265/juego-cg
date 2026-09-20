#include "states/Pantalla_SeleccionDePersonajeYMapa.h"
#include "graphics/FuncionesParaDibujarFigurasBasicas.h"
#include "graphics/DibujoDePersonaje1_CuerpoYArticulaciones.h"
#include "graphics/DibujoDePersonaje2_CuerpoYArticulaciones.h"
#include <GL/freeglut.h>
#include <cmath>

PantallaSeleccionDePersonajeYMapa::PantallaSeleccionDePersonajeYMapa() {
    personajeP1 = PERSONAJE_LEONARDOX;
    personajeP2 = PERSONAJE_GUADALUPE;
    mapaSeleccionado = ESCENARIO_PARQUE;
    tiempoAnim = 0.0f;
    seleccionConfirmada = false;
}

void PantallaSeleccionDePersonajeYMapa::inicializar() {
    tiempoAnim = 0.0f;
    seleccionConfirmada = false;
}

void PantallaSeleccionDePersonajeYMapa::actualizar(float dt) {
    tiempoAnim += dt;
}

void PantallaSeleccionDePersonajeYMapa::alternarP1() {
    personajeP1 = (personajeP1 == PERSONAJE_LEONARDOX) ? PERSONAJE_GUADALUPE : PERSONAJE_LEONARDOX;
}

void PantallaSeleccionDePersonajeYMapa::alternarP2() {
    personajeP2 = (personajeP2 == PERSONAJE_LEONARDOX) ? PERSONAJE_GUADALUPE : PERSONAJE_LEONARDOX;
}

void PantallaSeleccionDePersonajeYMapa::alternarMapa() {
    mapaSeleccionado = (mapaSeleccionado == ESCENARIO_PARQUE) ? ESCENARIO_UNIVERSIDAD : ESCENARIO_PARQUE;
}

void PantallaSeleccionDePersonajeYMapa::manejarTeclas(unsigned char tecla, bool esEspecial) {
    if (esEspecial) {
        if (tecla == GLUT_KEY_LEFT || tecla == GLUT_KEY_RIGHT) {
            alternarP2();
        } else if (tecla == GLUT_KEY_UP || tecla == GLUT_KEY_DOWN) {
            alternarMapa();
        }
    } else {
        if (tecla == 'a' || tecla == 'A' || tecla == 'd' || tecla == 'D') {
            alternarP1();
        } else if (tecla == 'w' || tecla == 'W' || tecla == 's' || tecla == 'S') {
            alternarMapa();
        } else if (tecla == 13) { // ENTER
            seleccionConfirmada = true;
        }
    }
}

void PantallaSeleccionDePersonajeYMapa::renderizar() {
    // 1. Fondo degradado de seleccion
    dibujarRectanguloDegradado(-1.0f, -1.0f, 2.0f, 2.0f,
                              0.08f, 0.06f, 0.16f,
                              0.16f, 0.12f, 0.28f,
                              true);

    // Titulo superior
    dibujarTextoConSombra("SELECCION DE LUCHADORES Y ESCENARIO", -0.45f, 0.85f,
                          GLUT_BITMAP_TIMES_ROMAN_24, 1.0f, 0.85f, 0.20f);

    // 2. Panel Jugador 1 (Izquierda)
    dibujarRectangulo(-0.85f, -0.40f, 0.70f, 1.15f, 0.12f, 0.14f, 0.22f, true);
    dibujarRectangulo(-0.85f, -0.40f, 0.70f, 1.15f, 0.20f, 0.60f, 1.00f, false);
    dibujarTextoConSombra("JUGADOR 1 (A/D)", -0.72f, 0.68f, GLUT_BITMAP_HELVETICA_18, 0.3f, 0.8f, 1.0f);

    const char* nomP1 = (personajeP1 == PERSONAJE_LEONARDOX) ? "LEONARDOX" : "GUADALUPE";
    dibujarTextoConSombra(nomP1, -0.68f, 0.58f, GLUT_BITMAP_TIMES_ROMAN_24, 1.0f, 0.9f, 0.3f);

    // Previsualizacion animada P1
    if (personajeP1 == PERSONAJE_LEONARDOX) {
        renderizarLeonardox(-0.50f, -0.15f, 1, 0, tiempoAnim, 100.0f, 100.0f, false);
    } else {
        renderizarGuadalupe(-0.50f, -0.15f, 1, 0, tiempoAnim, 100.0f, 100.0f, false);
    }

    // 3. Panel Jugador 2 (Derecha)
    dibujarRectangulo(0.15f, -0.40f, 0.70f, 1.15f, 0.12f, 0.14f, 0.22f, true);
    dibujarRectangulo(0.15f, -0.40f, 0.70f, 1.15f, 1.00f, 0.40f, 0.40f, false);
    dibujarTextoConSombra("JUGADOR 2 (FLECHAS)", 0.25f, 0.68f, GLUT_BITMAP_HELVETICA_18, 1.0f, 0.4f, 0.4f);

    const char* nomP2 = (personajeP2 == PERSONAJE_LEONARDOX) ? "LEONARDOX" : "GUADALUPE";
    dibujarTextoConSombra(nomP2, 0.32f, 0.58f, GLUT_BITMAP_TIMES_ROMAN_24, 1.0f, 0.9f, 0.3f);

    // Previsualizacion animada P2
    if (personajeP2 == PERSONAJE_LEONARDOX) {
        renderizarLeonardox(0.50f, -0.15f, -1, 0, tiempoAnim, 100.0f, 100.0f, false);
    } else {
        renderizarGuadalupe(0.50f, -0.15f, -1, 0, tiempoAnim, 100.0f, 100.0f, false);
    }

    // 4. Panel Central de Escenario
    dibujarRectangulo(-0.45f, -0.75f, 0.90f, 0.28f, 0.10f, 0.12f, 0.18f, true);
    dibujarRectangulo(-0.45f, -0.75f, 0.90f, 0.28f, 0.95f, 0.85f, 0.20f, false);

    dibujarTextoConSombra("ESCENARIO (W/S o FLECHAS ARRIBA/ABAJO):", -0.40f, -0.54f,
                          GLUT_BITMAP_HELVETICA_12, 0.8f, 0.8f, 0.9f);

    const char* nomMapa = (mapaSeleccionado == ESCENARIO_PARQUE) ?
                          "< ESCENARIO 1: EL PARQUE CENTRAL >" :
                          "< ESCENARIO 2: ENTRADA UNIVERSIDAD >";
    dibujarTextoConSombra(nomMapa, -0.41f, -0.66f, GLUT_BITMAP_HELVETICA_18, 0.2f, 1.0f, 0.6f);

    // 5. Barra inferior con instruccion
    dibujarRectangulo(-1.0f, -0.98f, 2.0f, 0.06f, 0.05f, 0.05f, 0.08f, true);
    dibujarTextoConSombra("Presiona ENTER para INICIAR EL COMBATE  |  ESC para volver al Menu",
                          -0.54f, -0.955f, GLUT_BITMAP_HELVETICA_12, 0.7f, 0.8f, 0.9f);
}
