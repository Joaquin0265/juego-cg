#ifndef PANTALLA_MENU_PRINCIPAL_H
#define PANTALLA_MENU_PRINCIPAL_H

class Pantalla_MenuPrincipal {
private:
    int opcionSeleccionada; // 0 = 1v1 Local, 1 = Salir
    const int TOTAL_OPCIONES = 2;

    void dibujarTexto(const char* texto, float x, float y, void* fuente, float r, float g, float b);

public:
    Pantalla_MenuPrincipal();

    void actualizar();
    void renderizar();
    void moverSeleccion(int direccion); // -1 arriba, 1 abajo
    int getOpcionSeleccionada() const { return opcionSeleccionada; }
};

#endif // PANTALLA_MENU_PRINCIPAL_H
