#ifndef CONFIG_RESOLUCION_Y_TECLAS_H
#define CONFIG_RESOLUCION_Y_TECLAS_H

#include <GL/freeglut.h>

#define FPS 60
#define ANCHO_PANTALLA 800
#define ALTO_PANTALLA 600

enum AccionJuego {
    MOVER_IZQ,
    MOVER_DER,
    SALTAR,
    AGCHARSE,
    GOLPE_SUAVE,
    GOLPE_FUERTE,
    BLOQUEAR,
    ESQUIVAR,
    MODO_ULTI,
    TOTAL_ACCIONES
};

struct ControlesJugador {
    int teclas[TOTAL_ACCIONES];
};

struct ConfiguracionJuego {
    int anchoPantalla = ANCHO_PANTALLA;
    int altoPantalla = ALTO_PANTALLA;
    bool pantallaCompleta = false;
    int volumenMusica = 80;
    int volumenEfectos = 100;

    ControlesJugador p1;
    ControlesJugador p2;
};

extern ConfiguracionJuego configGlobal;

void cargarControlesPorDefecto();

#endif // CONFIG_RESOLUCION_Y_TECLAS_H
