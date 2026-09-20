#ifndef PANTALLA_SELECCION_DE_PERSONAJE_Y_MAPA_H
#define PANTALLA_SELECCION_DE_PERSONAJE_Y_MAPA_H

class PantallaSeleccionDePersonajeYMapa {
private:
    int personajeP1 = 0;
    int personajeP2 = 0;
    int mapaSeleccionado = 0;
    bool seleccionConfirmada = false;

public:
    PantallaSeleccionDePersonajeYMapa();

    void renderizar();
    void manejarTeclas(unsigned char tecla, bool esEspecial);
    void moverSeleccionP1(int dir);
    void moverSeleccionP2(int dir);

    bool estaListo() const { return seleccionConfirmada; }
};

#endif // PANTALLA_SELECCION_DE_PERSONAJE_Y_MAPA_H
