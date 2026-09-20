#include "states/Pantalla_MenuPrincipal.h"
#include "graphics/FuncionesParaDibujarFigurasBasicas.h"
#include <GL/freeglut.h>
#include <cmath>

Pantalla_MenuPrincipal::Pantalla_MenuPrincipal() {
    opcionSeleccionada = 0;
    tiempoAnim = 0.0f;
}

void Pantalla_MenuPrincipal::inicializar() {
    opcionSeleccionada = 0;
    tiempoAnim = 0.0f;
}

void Pantalla_MenuPrincipal::actualizar(float dt) {
    tiempoAnim += dt;
}

void Pantalla_MenuPrincipal::moverSeleccion(int direccion) {
    opcionSeleccionada += direccion;
    if (opcionSeleccionada < 0) {
        opcionSeleccionada = TOTAL_OPCIONES - 1;
    } else if (opcionSeleccionada >= TOTAL_OPCIONES) {
        opcionSeleccionada = 0;
    }
}

void Pantalla_MenuPrincipal::renderizar() {
    // 1. Fondo degradado noche/neon con atmosfera
    dibujarRectanguloDegradado(-1.0f, -1.0f, 2.0f, 2.0f,
                              0.03f, 0.05f, 0.12f,
                              0.10f, 0.08f, 0.22f,
                              true);

    // Rejilla de lineas retro en la mitad inferior
    for (float lx = -1.0f; lx <= 1.0f; lx += 0.15f) {
        dibujarLinea(lx, -1.0f, lx * 0.4f, -0.2f, 1.2f, 0.15f, 0.25f, 0.45f);
    }
    for (float ly = -1.0f; ly <= -0.2f; ly += 0.12f) {
        dibujarLinea(-1.0f, ly, 1.0f, ly, 1.2f, 0.15f, 0.25f, 0.45f);
    }

    // 2. Titulo estilizado con efecto de brillo
    float oscTitulo = std::sin(tiempoAnim * 3.0f) * 0.015f;
    dibujarRectangulo(-0.60f, 0.45f + oscTitulo, 1.20f, 0.28f, 0.05f, 0.05f, 0.10f, true);
    dibujarRectangulo(-0.60f, 0.45f + oscTitulo, 1.20f, 0.28f, 0.95f, 0.75f, 0.20f, false);

    dibujarTextoConSombra("FIGHTING GAME 2D", -0.42f, 0.60f + oscTitulo,
                          GLUT_BITMAP_TIMES_ROMAN_24, 1.0f, 0.85f, 0.20f);
    dibujarTextoConSombra("COMPUTACION GRAFICA - MOTOR VECTORIAL", -0.46f, 0.50f + oscTitulo,
                          GLUT_BITMAP_HELVETICA_12, 0.4f, 0.85f, 1.0f);

    // 3. Opciones del Menu Principal
    const char* textosOpciones[4] = {
        "1 vs 1 COMBATE DIRECTO",
        "SELECCION DE LUCHADOR Y MAPA",
        "CONFIGURACION Y TECLAS",
        "SALIR DEL JUEGO"
    };

    float posYBase = 0.20f;
    float separacion = 0.13f;

    for (int i = 0; i < TOTAL_OPCIONES; i++) {
        float y = posYBase - (float)i * separacion;
        bool seleccionada = (opcionSeleccionada == i);

        // Caja de fondo para la opcion
        if (seleccionada) {
            float pulso = 0.008f * std::sin(tiempoAnim * 8.0f);
            dibujarRectangulo(-0.48f - pulso, y - 0.035f, 0.96f + pulso * 2.0f, 0.085f, 0.15f, 0.35f, 0.55f, true);
            dibujarRectangulo(-0.48f - pulso, y - 0.035f, 0.96f + pulso * 2.0f, 0.085f, 0.2f, 1.0f, 0.6f, false);

            // Indicador de flecha '>'
            dibujarTextoConSombra(">", -0.44f, y, GLUT_BITMAP_HELVETICA_18, 0.2f, 1.0f, 0.6f);
            dibujarTextoConSombra(textosOpciones[i], -0.38f, y, GLUT_BITMAP_HELVETICA_18, 0.2f, 1.0f, 0.6f);
        } else {
            dibujarRectangulo(-0.45f, y - 0.035f, 0.90f, 0.085f, 0.08f, 0.10f, 0.16f, true);
            dibujarRectangulo(-0.45f, y - 0.035f, 0.90f, 0.085f, 0.30f, 0.30f, 0.35f, false);

            dibujarTexto(textosOpciones[i], -0.38f, y, GLUT_BITMAP_HELVETICA_18, 0.70f, 0.75f, 0.80f);
        }
    }

    // 4. Guia inferior de navegacion
    dibujarRectangulo(-1.0f, -0.98f, 2.0f, 0.06f, 0.05f, 0.05f, 0.08f, true);
    dibujarTextoConSombra("Usa FLECHAS ARRIBA/ABAJO para navegar  |  ENTER para seleccionar",
                          -0.52f, -0.955f, GLUT_BITMAP_HELVETICA_12, 0.6f, 0.7f, 0.8f);
}
