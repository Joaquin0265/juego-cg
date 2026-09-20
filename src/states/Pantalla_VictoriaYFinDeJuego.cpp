#include "states/Pantalla_VictoriaYFinDeJuego.h"
#include "graphics/FuncionesParaDibujarFigurasBasicas.h"
#include "graphics/DibujoDePersonaje1_CuerpoYArticulaciones.h"
#include "graphics/DibujoDePersonaje2_CuerpoYArticulaciones.h"
#include <GL/freeglut.h>
#include <cstdio>
#include <cmath>

PantallaVictoriaYFinDeJuego::PantallaVictoriaYFinDeJuego() {
    ganador = PERSONAJE_LEONARDOX;
    idGanador = 1;
    opcionSeleccionada = 0;
    tiempoAnim = 0.0f;
}

void PantallaVictoriaYFinDeJuego::configurarGanador(TipoPersonaje _ganador, int _idGanador) {
    ganador = _ganador;
    idGanador = _idGanador;
    opcionSeleccionada = 0;
    tiempoAnim = 0.0f;
}

void PantallaVictoriaYFinDeJuego::actualizar(float dt) {
    tiempoAnim += dt;
}

void PantallaVictoriaYFinDeJuego::manejarTeclas(unsigned char tecla, bool esEspecial) {
    if (esEspecial) {
        if (tecla == GLUT_KEY_UP) {
            opcionSeleccionada = (opcionSeleccionada - 1 + 3) % 3;
        } else if (tecla == GLUT_KEY_DOWN) {
            opcionSeleccionada = (opcionSeleccionada + 1) % 3;
        }
    }
}

void PantallaVictoriaYFinDeJuego::renderizar() {
    // 1. Fondo degradado de victoria
    dibujarRectanguloDegradado(-1.0f, -1.0f, 2.0f, 2.0f,
                              0.04f, 0.06f, 0.14f,
                              0.12f, 0.18f, 0.32f,
                              true);

    // Rayos de triunfo de fondo
    for (int i = 0; i < 12; i++) {
        float ang = tiempoAnim * 0.4f + (float)i * (2.0f * PI_CONST / 12.0f);
        float x2 = std::cos(ang) * 1.5f;
        float y2 = std::sin(ang) * 1.5f;
        dibujarLinea(0.0f, 0.1f, x2, y2, 2.5f, 0.15f, 0.22f, 0.38f);
    }

    // 2. Banner de Victoria
    float osc = std::sin(tiempoAnim * 4.0f) * 0.015f;
    dibujarRectangulo(-0.55f, 0.60f + osc, 1.10f, 0.22f, 0.10f, 0.12f, 0.20f, true);
    dibujarRectangulo(-0.55f, 0.60f + osc, 1.10f, 0.22f, 1.00f, 0.85f, 0.20f, false);

    dibujarTextoConSombra("¡VICTORIA TOTAL!", -0.28f, 0.72f + osc,
                          GLUT_BITMAP_TIMES_ROMAN_24, 1.0f, 0.85f, 0.2f);

    char bufGanador[64];
    std::snprintf(bufGanador, sizeof(bufGanador), "¡%s (JUGADOR %d) ES EL CAMPEON!",
                  (ganador == PERSONAJE_LEONARDOX) ? "LEONARDOX" : "GUADALUPE", idGanador);
    dibujarTextoConSombra(bufGanador, -0.42f, 0.64f + osc,
                          GLUT_BITMAP_HELVETICA_18, 0.3f, 1.0f, 0.6f);

    // 3. Renderizado del Ganador en pose de victoria en el centro
    if (ganador == PERSONAJE_LEONARDOX) {
        renderizarLeonardox(0.0f, -0.20f, 1, 7, tiempoAnim, 100.0f, 100.0f, false);
    } else {
        renderizarGuadalupe(0.0f, -0.20f, 1, 7, tiempoAnim, 100.0f, 100.0f, false);
    }

    // 4. Opciones posteriores al combate
    const char* textosOpciones[3] = {
        "REVANCHA (VOLVER A COMBATIR)",
        "SELECCION DE LUCHADORES Y MAPA",
        "MENU PRINCIPAL"
    };

    float yBase = -0.40f;
    float sep = 0.11f;

    for (int i = 0; i < 3; i++) {
        float y = yBase - (float)i * sep;
        bool sel = (opcionSeleccionada == i);

        if (sel) {
            float pulso = 0.005f * std::sin(tiempoAnim * 8.0f);
            dibujarRectangulo(-0.46f - pulso, y - 0.028f, 0.92f + pulso * 2.0f, 0.075f, 0.15f, 0.35f, 0.55f, true);
            dibujarRectangulo(-0.46f - pulso, y - 0.028f, 0.92f + pulso * 2.0f, 0.075f, 0.2f, 1.0f, 0.6f, false);
            dibujarTextoConSombra(">", -0.42f, y, GLUT_BITMAP_HELVETICA_18, 0.2f, 1.0f, 0.6f);
            dibujarTextoConSombra(textosOpciones[i], -0.36f, y, GLUT_BITMAP_HELVETICA_18, 0.2f, 1.0f, 0.6f);
        } else {
            dibujarRectangulo(-0.45f, y - 0.028f, 0.90f, 0.075f, 0.08f, 0.10f, 0.16f, true);
            dibujarRectangulo(-0.45f, y - 0.028f, 0.90f, 0.075f, 0.30f, 0.30f, 0.35f, false);
            dibujarTexto(textosOpciones[i], -0.36f, y, GLUT_BITMAP_HELVETICA_18, 0.70f, 0.75f, 0.80f);
        }
    }

    // 5. Guia inferior
    dibujarRectangulo(-1.0f, -0.98f, 2.0f, 0.06f, 0.05f, 0.05f, 0.08f, true);
    dibujarTextoConSombra("Usa FLECHAS ARRIBA/ABAJO  |  ENTER para confirmar opcion",
                          -0.45f, -0.955f, GLUT_BITMAP_HELVETICA_12, 0.6f, 0.7f, 0.8f);
}
