#include "states/Pantalla_Opciones.h"
#include <GL/freeglut.h>

void PantallaOpciones::alternarPantallaCompleta() {
    configGlobal.pantallaCompleta = !configGlobal.pantallaCompleta;
    if (configGlobal.pantallaCompleta) {
        glutFullScreen();
    } else {
        glutReshapeWindow(configGlobal.anchoPantalla, configGlobal.altoPantalla);
        glutPositionWindow(100, 100);
    }
}

void PantallaOpciones::manejarTeclas(unsigned char tecla, bool esEspecial) {
    if (reasignandoTecla) {
        // Asignar la tecla presionada al jugador correspondiente
        if (jugadorAEdit == 1) {
            configGlobal.p1.teclas[accionAEdit] = tecla;
        } else {
            configGlobal.p2.teclas[accionAEdit] = tecla;
        }
        reasignandoTecla = false; // Salir del modo reasignar
        return;
    }

    // Navegación normal con Enter
    if (tecla == 13) { // ENTER
        if (opcionSeleccionada == 0) {
            alternarPantallaCompleta();
        } else if (opcionSeleccionada == 1) {
            // Entrar en modo reasignar tecla
            reasignandoTecla = true;
        }
    }
}
