#include "states/Pantalla_SeleccionDePersonajeYMapa.h"
#include <GL/freeglut.h>

PantallaSeleccionDePersonajeYMapa::PantallaSeleccionDePersonajeYMapa() {
    personajeP1 = 0;
    personajeP2 = 1;
    mapaSeleccionado = 0;
    seleccionConfirmada = false;
}

void PantallaSeleccionDePersonajeYMapa::moverSeleccionP1(int dir) {
    personajeP1 = (personajeP1 + dir + 2) % 2; // Ejemplo para 2 personajes
}

void PantallaSeleccionDePersonajeYMapa::moverSeleccionP2(int dir) {
    personajeP2 = (personajeP2 + dir + 2) % 2;
}

void PantallaSeleccionDePersonajeYMapa::renderizar() {
    // Dibujado básico provisional de la pantalla de selección
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    // Fondo o texto informativo
    // (Aquí puedes llamar a tus funciones de gráficos)
}

void PantallaSeleccionDePersonajeYMapa::manejarTeclas(unsigned char tecla, bool esEspecial) {
    if (tecla == 13) { // ENTER para confirmar
        seleccionConfirmada = true;
    }
}
