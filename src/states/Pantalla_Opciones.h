#ifndef PANTALLA_OPCIONES_H
#define PANTALLA_OPCIONES_H

#include "core/Config_ResolucionYTeclas.h"

/**
 * ============================================================================
 * MODULO: Pantalla_Opciones
 * ============================================================================
 * Menú de configuración interactivo:
 * - Selección de Resolución y Pantalla Completa.
 * - Ajuste de volumen de música y efectos de sonido.
 * - Reasignación (bindeo) en tiempo real de cada tecla para Jugador 1 y Jugador 2.
 * - Guardado y carga automática en config.txt.
 * - Restauración de controles por defecto.
 */

class PantallaOpciones {
private:
    int menuActual;         // 0 = Menu Principal de Opciones, 1 = Editar Teclas P1, 2 = Editar Teclas P2
    int opcionSeleccionada;
    bool modoReasignando;   // True cuando espera que el usuario presione una tecla
    int accionAEditar;      // Indice de la accion que se esta reasignando
    float tiempoAnim;
    std::string mensajeEstado;
    float tiempoMensaje;

public:
    PantallaOpciones();

    void inicializar();
    void actualizar(float dt);
    void renderizar();
    void manejarTeclas(int codigoTecla, bool esEspecial);

private:
    void alternarPantallaCompleta();
    void cambiarResolucion(int delta);
    void cambiarVolumen(bool esMusica, int delta);
};

#endif // PANTALLA_OPCIONES_H
