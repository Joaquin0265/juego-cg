#ifndef MOTOR_PRINCIPAL_BUCLE_JUEGO_H
#define MOTOR_PRINCIPAL_BUCLE_JUEGO_H

#include "states/AdministradorDePantallasYModos.h"

/**
 * ============================================================================
 * MODULO: MotorPrincipal_BucleJuego
 * ============================================================================
 * Orquesta el ciclo de vida del juego con GLUT:
 * - Inicializacion de ventana grafica y contexto OpenGL.
 * - Registro de callbacks de renderizado, teclado (pulsacion y liberacion).
 * - Temporizador a 60 FPS estables con calculo de Delta Time.
 * - Control de proyeccion ortografica 2D adaptada a la resolucion seleccionada.
 */

class MotorJuego {
private:
    static MotorJuego* instancia;
    AdministradorDePantallasYModos administradorPantallas;
    int milisegundosPrevios;

public:
    MotorJuego();

    static MotorJuego& obtenerInstancia();

    void inicializar(int argc, char** argv);
    void ejecutar();

    // Callbacks estaticos para GLUT
    static void callbackRenderizar();
    static void callbackRedimensionar(int ancho, int alto);
    static void callbackTemporizador(int valor);
    static void callbackTeclaNormal(unsigned char tecla, int x, int y);
    static void callbackTeclaNormalUp(unsigned char tecla, int x, int y);
    static void callbackTeclaEspecial(int tecla, int x, int y);
    static void callbackTeclaEspecialUp(int tecla, int x, int y);

    AdministradorDePantallasYModos& getAdminPantallas() { return administradorPantallas; }
};

#endif // MOTOR_PRINCIPAL_BUCLE_JUEGO_H
