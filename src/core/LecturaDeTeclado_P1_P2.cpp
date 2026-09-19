#include "core/LecturaDeTeclado_P1_P2.h"
#include "states/Pantalla_MenuPrincipal.h"
#include <GL/freeglut.h>
#include <cstdlib> // Para exit(0)

// Referencia global al menú para controlar la navegación
extern Pantalla_MenuPrincipal menuPrincipal;
extern int estadoActualJuego; // 0 = Menú, 1 = Pelea

void teclaEspecialPresionada(int tecla, int x, int y) {
    if (estadoActualJuego == 0) { // Si estamos en el Menú
        switch (tecla) {
            case GLUT_KEY_UP:
                menuPrincipal.moverSeleccion(-1);
                break;
            case GLUT_KEY_DOWN:
                menuPrincipal.moverSeleccion(1);
                break;
        }
    }
}

void teclaNormalPresionada(unsigned char tecla, int x, int y) {
    if (estadoActualJuego == 0) { // Si estamos en el Menú
        if (tecla == 13) { // Tecla ENTER
            int opcion = menuPrincipal.getOpcionSeleccionada();
            if (opcion == 0) {
                // Entrar a la pelea
                estadoActualJuego = 1;
            } else if (opcion == 1) {
                // Salir del juego
                exit(0);
            }
        }
    } else if (estadoActualJuego == 1) { // Si estamos en Pelea
        if (tecla == 27) { // Tecla ESCAPE
            // Volver al menú
            estadoActualJuego = 0;
        }
    }
}
