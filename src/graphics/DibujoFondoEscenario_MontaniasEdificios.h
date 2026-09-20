#ifndef DIBUJO_FONDO_ESCENARIO_H
#define DIBUJO_FONDO_ESCENARIO_H

#include "entities/LimitesDelEscenarioPlataforma.h"

/**
 * ============================================================================
 * MODULO: DibujoFondoEscenario_MontaniasEdificios
 * ============================================================================
 * Renderiza los 2 escenarios vectoriales solicitados para Computacion Grafica:
 * 1. Parque: Arboles, copas poligonales, bancos de madera, farolas y cielo abierto.
 * 2. Entrada de Universidad: Fachada monumental, columnas clasicas, escalinata
 *    y portico de ingreso universitario.
 * Los objetos se componen como piezas modulares para permitir variaciones
 * visuales al cambiar o romper el escenario tras un impacto de borde.
 */

class RenderizadorEscenario {
public:
    RenderizadorEscenario();

    // Dibuja el escenario correspondiente segun el estado actual y variacion
    void renderizar(TipoEscenario tipo, int variacion, float nivelSuelo);

private:
    // Dibujo del Escenario 1: Parque
    void renderizarParque(int variacion, float nivelSuelo);
    void dibujarArbol(float x, float y, float escala);
    void dibujarBancoParque(float x, float y);
    void dibujarFarola(float x, float y);
    void dibujarNube(float x, float y, float escala);

    // Dibujo del Escenario 2: Entrada Universidad
    void renderizarUniversidad(int variacion, float nivelSuelo);
    void dibujarColumna(float x, float y, float ancho, float alto);
    void dibujarEscalinata(float nivelSuelo);
    void dibujarPorticoUniversidad(float centroX, float nivelSuelo);
    void dibujarEstatuaOEmblema(float x, float y);
};

#endif // DIBUJO_FONDO_ESCENARIO_H
