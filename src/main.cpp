#if defined(_WIN32)
#include <windows.h>
#endif

#include <GL/freeglut.h>
#include "core/Config_ResolucionYTeclas.h"
#include "core/LecturaDeTeclado_P1_P2.h"
#include "states/Pantalla_MenuPrincipal.h"

// Variables globales del estado del juego
Pantalla_MenuPrincipal menuPrincipal;
int estadoActualJuego = 0; // 0 = Menú, 1 = Pelea

void buclePrincipal(int valor) {
    glutPostRedisplay();
    glutTimerFunc(1000 / FPS, buclePrincipal, 0);
}

void renderizar() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    if (estadoActualJuego == 0) {
        menuPrincipal.renderizar();
    } else if (estadoActualJuego == 1) {
        // Renderizar pantalla de pelea
    }

    glutSwapBuffers();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(ANCHO_PANTALLA, ALTO_PANTALLA);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Proyecto Final - Juego de Pelea");

    // Configuración inicial de controles
    cargarControlesPorDefecto();

    // Registro de callbacks
    glutDisplayFunc(renderizar);
    glutKeyboardFunc(teclaNormalPresionada);
    glutSpecialFunc(teclaEspecialPresionada);
    glutTimerFunc(1000 / FPS, buclePrincipal, 0);

    glutMainLoop();
    return 0;
}
