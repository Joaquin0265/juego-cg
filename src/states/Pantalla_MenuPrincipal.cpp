#include "states/Pantalla_MenuPrincipal.h"
#include <GL/freeglut.h>

Pantalla_MenuPrincipal::Pantalla_MenuPrincipal() {
    opcionSeleccionada = 0; // Inicia en 1v1 Local
}

void Pantalla_MenuPrincipal::moverSeleccion(int direccion) {
    opcionSeleccionada += direccion;

    if (opcionSeleccionada < 0) {
        opcionSeleccionada = TOTAL_OPCIONES - 1;
    } else if (opcionSeleccionada >= TOTAL_OPCIONES) {
        opcionSeleccionada = 0;
    }
}

void Pantalla_MenuPrincipal::dibujarTexto(const char* texto, float x, float y, void* fuente, float r, float g, float b) {
    glColor3f(r, g, b);
    glRasterPos2f(x, y);
    for (const char* c = texto; *c != '\0'; c++) {
        glutBitmapCharacter(fuente, *c);
    }
}

void Pantalla_MenuPrincipal::actualizar() {
    // Animaciones futuras
}

void Pantalla_MenuPrincipal::renderizar() {
    // 1. Fondo Degradado Noche/Neón
    glBegin(GL_QUADS);
        glColor3f(0.08f, 0.05f, 0.15f);
        glVertex2f(-1.0f, 1.0f);
        glVertex2f( 1.0f, 1.0f);
        glColor3f(0.02f, 0.08f, 0.2f);
        glVertex2f( 1.0f, -1.0f);
        glVertex2f(-1.0f, -1.0f);
    glEnd();

    // 2. Título del juego
    dibujarTexto("JUEGO DE PELEAS 2D", -0.42f, 0.5f, GLUT_BITMAP_TIMES_ROMAN_24, 1.0f, 0.8f, 0.2f);
    dibujarTexto("--- PROCEDURAL ENGINE ---", -0.32f, 0.38f, GLUT_BITMAP_HELVETICA_12, 0.6f, 0.6f, 0.8f);

    // 3. Opciones del Menú

    // Opción 0: 1v1 Local
    if (opcionSeleccionada == 0) {
        dibujarTexto("> 1 vs 1 LOCAL <", -0.22f, 0.10f, GLUT_BITMAP_HELVETICA_18, 0.0f, 1.0f, 0.5f);
    } else {
        dibujarTexto("  1 vs 1 LOCAL  ", -0.22f, 0.10f, GLUT_BITMAP_HELVETICA_18, 0.7f, 0.7f, 0.7f);
    }

    // Opción 1: Configuración / Opciones (NUEVA)
    if (opcionSeleccionada == 1) {
        dibujarTexto("> CONFIGURACION <", -0.24f, -0.08f, GLUT_BITMAP_HELVETICA_18, 0.0f, 0.8f, 1.0f); // Azul cian
    } else {
        dibujarTexto("  CONFIGURACION  ", -0.24f, -0.08f, GLUT_BITMAP_HELVETICA_18, 0.7f, 0.7f, 0.7f);
    }

    // Opción 2: Salir
    if (opcionSeleccionada == 2) {
        dibujarTexto("> SALIR <", -0.12f, -0.26f, GLUT_BITMAP_HELVETICA_18, 1.0f, 0.2f, 0.2f);
    } else {
        dibujarTexto("  SALIR  ", -0.12f, -0.26f, GLUT_BITMAP_HELVETICA_18, 0.7f, 0.7f, 0.7f);
    }

    // Instrucciones
    dibujarTexto("Usa FLECHAS para moverte | ENTER para seleccionar", -0.48f, -0.85f, GLUT_BITMAP_HELVETICA_12, 0.5f, 0.5f, 0.5f);
}
