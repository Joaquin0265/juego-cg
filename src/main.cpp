#include <GL/freeglut.h>
#include "core/Config_ResolucionYTeclas.h"
#include "core/LecturaDeTeclado_P1_P2.h"
#include "states/Pantalla_MenuPrincipal.h"

// Variables Globales de Estado
Pantalla_MenuPrincipal menuPrincipal;
int estadoActualJuego = 0; // 0 = Menú, 1 = Pelea Activa

void renderizarPantalla() {
    glClear(GL_COLOR_BUFFER_BIT);

    if (estadoActualJuego == 0) {
        // Dibuja el Menú Principal
        menuPrincipal.renderizar();
    } else if (estadoActualJuego == 1) {
        // --- VISTA TEMPORAL DE PELEA ---
        glClearColor(0.2f, 0.05f, 0.05f, 1.0f); // Fondo Rojo de Pelea

        // Dibujamos un "Suelo" de prueba
        glColor3f(0.3f, 0.3f, 0.3f);
        glBegin(GL_QUADS);
            glVertex2f(-1.0f, -0.6f);
            glVertex2f( 1.0f, -0.6f);
            glVertex2f( 1.0f, -1.0f);
            glVertex2f(-1.0f, -1.0f);
        glEnd();

        // Texto informativo
        glColor3f(1.0f, 1.0f, 1.0f);
        glRasterPos2f(-0.35f, 0.8f);
        const char* msg = "MODO DE PELEA (Presiona ESC para volver)";
        for (const char* c = msg; *c != '\0'; c++) {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, *c);
        }
    }

    glutSwapBuffers();
}

void buclePrincipal(int valor) {
    if (estadoActualJuego == 0) {
        menuPrincipal.actualizar();
    }

    glutPostRedisplay();
    glutTimerFunc(1000 / FPS, buclePrincipal, 0);
}

void redimensionarVentana(int ancho, int alto) {
    if (alto == 0) alto = 1;
    glViewport(0, 0, ancho, alto);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowSize(ANCHO_PANTALLA, ALTO_PANTALLA);
    glutInitWindowPosition(100, 100);

    glutCreateWindow("Juego de Peleas 2D - Menu Principal");

    // Registramos los callbacks de dibujado y bucle
    glutDisplayFunc(renderizarPantalla);
    glutReshapeFunc(redimensionarVentana);
    glutTimerFunc(1000 / FPS, buclePrincipal, 0);

    // Registramos los callbacks del teclado (NUEVO)
    glutSpecialFunc(teclaEspecialPresionada); // Flechas Arriba/Abajo
    glutKeyboardFunc(teclaNormalPresionada);  // Enter / ESC

    glutMainLoop();
    return 0;
}
