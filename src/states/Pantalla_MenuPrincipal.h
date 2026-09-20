#ifndef PANTALLA_MENU_PRINCIPAL_H
#define PANTALLA_MENU_PRINCIPAL_H

/**
 * ============================================================================
 * MODULO: Pantalla_MenuPrincipal
 * ============================================================================
 * Menú principal del juego con fondo degradado dinámico, logotipo vectorial
 * y opciones de navegación.
 */

class Pantalla_MenuPrincipal {
private:
    int opcionSeleccionada;
    const int TOTAL_OPCIONES = 4;
    float tiempoAnim;

public:
    Pantalla_MenuPrincipal();

    void inicializar();
    void actualizar(float dt);
    void renderizar();
    void moverSeleccion(int direccion);

    int getOpcionSeleccionada() const { return opcionSeleccionada; }
};

#endif // PANTALLA_MENU_PRINCIPAL_H
