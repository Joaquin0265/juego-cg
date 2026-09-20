#ifndef INTERFAZ_ESTADO_BASE_H
#define INTERFAZ_ESTADO_BASE_H

/**
 * ============================================================================
 * INTERFAZ: InterfazEstadoBase
 * ============================================================================
 * Clase base abstracta para aplicar el Patron State (Maquina de Estados).
 * Cada pantalla del juego (Menu, Opciones, Pelea, Victoria, Seleccion) implementa
 * estos metodos para un ciclo de vida limpio e independiente.
 */
class InterfazEstadoBase {
public:
    virtual ~InterfazEstadoBase() {}

    virtual void inicializar() = 0;
    virtual void actualizar(float dt) = 0;
    virtual void renderizar() = 0;
    virtual void manejarEntrada(int tecla, bool esEspecial, bool presionado) = 0;
};

#endif // INTERFAZ_ESTADO_BASE_H
