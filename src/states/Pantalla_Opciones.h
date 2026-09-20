#ifndef PANTALLA_OPCIONES_H
#define PANTALLA_OPCIONES_H

#include "core/Config_ResolucionYTeclas.h"

class PantallaOpciones {
private:
    int opcionSeleccionada = 0;
    bool reasignandoTecla = false;
    int jugadorAEdit = 1; // 1 = P1, 2 = P2
    int accionAEdit = 0;

public:
    void alternarPantallaCompleta();
    void manejarTeclas(unsigned char tecla, bool esEspecial);
};

#endif // PANTALLA_OPCIONES_H
