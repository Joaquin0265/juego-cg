#ifndef CONFIG_RESOLUCION_Y_TECLAS_H
#define CONFIG_RESOLUCION_Y_TECLAS_H

#include <GL/freeglut.h>
#include <string>

// Constantes de pantalla y tasa de refresco
#define FPS 60
#define ANCHO_PANTALLA_BASE 800
#define ALTO_PANTALLA_BASE 600

/**
 * ============================================================================
 * ENUM: AccionJuego
 * ============================================================================
 * Identifica cada una de las acciones que puede realizar un jugador en combate.
 */
enum AccionJuego {
    MOVER_IZQ = 0,
    MOVER_DER,
    SALTAR,
    AGCHARSE,
    GOLPE_SUAVE,
    GOLPE_FUERTE,
    BLOQUEAR,
    ESQUIVAR,   // Parry / Esquive y Contraataque
    TOTAL_ACCIONES
};

/**
 * Contenedor de teclas para un jugador específico
 */
struct ControlesJugador {
    int teclas[TOTAL_ACCIONES];
    bool esTeclaEspecial[TOTAL_ACCIONES]; // true si es tecla especial GLUT (flechas, F1, etc.)
};

/**
 * Configuración global del juego persistente en disco
 */
struct ConfiguracionJuego {
    int anchoPantalla = ANCHO_PANTALLA_BASE;
    int altoPantalla = ALTO_PANTALLA_BASE;
    bool pantallaCompleta = false;
    int volumenMusica = 80;
    int volumenEfectos = 100;
    int indiceResolucion = 0; // 0: 800x600, 1: 1024x768, 2: 1280x720

    ControlesJugador p1;
    ControlesJugador p2;
};

// Instancia global compartida en todo el proyecto
extern ConfiguracionJuego configGlobal;

// Funciones de configuración
void cargarControlesPorDefecto();
void guardarConfiguracionEnArchivo();
void cargarConfiguracionDesdeArchivo();
void aplicarResolucion(int indice);

// Funciones utilitarias para menús
std::string obtenerNombreAccion(int accion);
std::string obtenerNombreTecla(int codigoTecla, bool esEspecial);

#endif // CONFIG_RESOLUCION_Y_TECLAS_H
