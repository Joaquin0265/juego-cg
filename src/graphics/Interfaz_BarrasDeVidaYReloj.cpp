#include "graphics/Interfaz_BarrasDeVidaYReloj.h"
#include "graphics/FuncionesParaDibujarFigurasBasicas.h"
#include <cstdio>
#include <cmath>

InterfazCombate::InterfazCombate() {
    tiempoTotal = 0.0f;
}

void InterfazCombate::dibujarMarcadorRounds(float x, float y, int roundsGanados, bool invertida) {
    for (int i = 0; i < 2; i++) {
        float ox = invertida ? (x - (float)i * 0.04f) : (x + (float)i * 0.04f);
        bool ganado = (i < roundsGanados);
        if (ganado) {
            dibujarEstrella(ox, y, 0.016f, 0.007f, 5, 0.0f, 1.0f, 0.85f, 0.1f);
        } else {
            dibujarCirculo(ox, y, 0.012f, 10, 0.3f, 0.3f, 0.35f, true);
            dibujarCirculo(ox, y, 0.012f, 10, 0.6f, 0.6f, 0.7f, false);
        }
    }
}

void InterfazCombate::dibujarBarraJugador(float x, float y, float ancho, float alto,
                                          const PersonajeFighter& p, bool invertida) {
    // 1. Marco exterior y fondo oscuro
    dibujarRectangulo(x - 0.01f, y - 0.035f, ancho + 0.02f, alto + 0.045f, 0.10f, 0.10f, 0.14f, true);
    dibujarRectangulo(x - 0.01f, y - 0.035f, ancho + 0.02f, alto + 0.045f, 0.40f, 0.40f, 0.45f, false);

    // 2. Fondo rojo de vida perdida
    dibujarRectangulo(x, y, ancho, alto, 0.55f, 0.10f, 0.10f, true);

    float pctSalud = p.getSalud() / p.getSaludMax();
    float pctRetardo = p.getSaludRetardada() / p.getSaludMax();
    if (pctSalud < 0.0f) pctSalud = 0.0f;
    if (pctRetardo < 0.0f) pctRetardo = 0.0f;

    // 3. Barra amarilla de daño retardado
    float anchoRetardo = ancho * pctRetardo;
    if (invertida) {
        dibujarRectangulo(x + ancho - anchoRetardo, y, anchoRetardo, alto, 0.95f, 0.80f, 0.20f, true);
    } else {
        dibujarRectangulo(x, y, anchoRetardo, alto, 0.95f, 0.80f, 0.20f, true);
    }

    // 4. Barra verde/cian de salud actual
    float anchoSalud = ancho * pctSalud;
    float rSalud = (pctSalud > 0.5f) ? (1.0f - (pctSalud - 0.5f) * 2.0f) : 1.0f;
    float gSalud = (pctSalud > 0.5f) ? 0.9f : (pctSalud * 1.8f);
    if (invertida) {
        dibujarRectanguloDegradado(x + ancho - anchoSalud, y, anchoSalud, alto,
                                  rSalud * 0.7f, gSalud * 0.7f, 0.15f,
                                  rSalud, gSalud, 0.25f, true);
    } else {
        dibujarRectanguloDegradado(x, y, anchoSalud, alto,
                                  rSalud * 0.7f, gSalud * 0.7f, 0.15f,
                                  rSalud, gSalud, 0.25f, true);
    }

    // Borde de la barra de vida
    dibujarRectangulo(x, y, ancho, alto, 0.9f, 0.9f, 0.9f, false);

    // 5. Barra de Escudo / Bloqueo (Guard Meter) debajo de la salud
    float altoEscudo = 0.012f;
    float yEscudo = y - 0.020f;
    float pctEscudo = p.getEscudo() / p.getEscudoMax();
    if (pctEscudo < 0.0f) pctEscudo = 0.0f;

    // Fondo gris del escudo
    dibujarRectangulo(x, yEscudo, ancho, altoEscudo, 0.25f, 0.25f, 0.30f, true);

    // Color del escudo: cian cuando esta lleno, naranja cuando esta a punto de romperse
    float rEsc = (pctEscudo < 0.3f) ? 1.0f : 0.2f;
    float gEsc = (pctEscudo < 0.3f) ? 0.4f : 0.8f;
    float bEsc = (pctEscudo < 0.3f) ? 0.1f : 1.0f;
    float anchoEscudo = ancho * pctEscudo;

    if (invertida) {
        dibujarRectangulo(x + ancho - anchoEscudo, yEscudo, anchoEscudo, altoEscudo, rEsc, gEsc, bEsc, true);
    } else {
        dibujarRectangulo(x, yEscudo, anchoEscudo, altoEscudo, rEsc, gEsc, bEsc, true);
    }
    dibujarRectangulo(x, yEscudo, ancho, altoEscudo, 0.7f, 0.7f, 0.8f, false);

    // Etiqueta GUARD
    if (invertida) {
        dibujarTexto("GUARD", x + ancho - 0.07f, yEscudo - 0.018f, GLUT_BITMAP_HELVETICA_10, 0.7f, 0.8f, 0.9f);
    } else {
        dibujarTexto("GUARD", x, yEscudo - 0.018f, GLUT_BITMAP_HELVETICA_10, 0.7f, 0.8f, 0.9f);
    }

    // 6. Nombre del personaje
    if (invertida) {
        dibujarTextoConSombra(p.getNombre().c_str(), x + ancho - 0.14f, y + alto + 0.015f,
                              GLUT_BITMAP_HELVETICA_18, 1.0f, 0.9f, 0.3f);
    } else {
        dibujarTextoConSombra(p.getNombre().c_str(), x, y + alto + 0.015f,
                              GLUT_BITMAP_HELVETICA_18, 1.0f, 0.9f, 0.3f);
    }
}

void InterfazCombate::renderizar(const PersonajeFighter& p1, const PersonajeFighter& p2,
                                int tiempoRestante, int roundActual,
                                const char* mensajeCentral, bool alertaTransicionEscenario) {
    tiempoTotal += 0.016f;

    // 1. Barra de Vida y Escudo Jugador 1 (Lado Izquierdo)
    dibujarBarraJugador(-0.88f, 0.78f, 0.65f, 0.045f, p1, false);
    dibujarMarcadorRounds(-0.88f, 0.71f, p1.getRoundsGanados(), false);

    // 2. Barra de Vida y Escudo Jugador 2 (Lado Derecho)
    dibujarBarraJugador(0.23f, 0.78f, 0.65f, 0.045f, p2, true);
    dibujarMarcadorRounds(0.88f, 0.71f, p2.getRoundsGanados(), true);

    // 3. Reloj Central (Caja poligonal con temporizador)
    dibujarRectangulo(-0.08f, 0.74f, 0.16f, 0.12f, 0.12f, 0.12f, 0.18f, true);
    dibujarRectangulo(-0.08f, 0.74f, 0.16f, 0.12f, 0.85f, 0.75f, 0.20f, false);

    char bufReloj[16];
    std::snprintf(bufReloj, sizeof(bufReloj), "%02d", (tiempoRestante < 0) ? 0 : tiempoRestante);
    float colRelojR = (tiempoRestante <= 10) ? 1.0f : 1.0f;
    float colRelojG = (tiempoRestante <= 10) ? 0.2f : 0.95f;
    float colRelojB = (tiempoRestante <= 10) ? 0.2f : 0.3f;
    dibujarTextoConSombra(bufReloj, -0.04f, 0.78f, GLUT_BITMAP_TIMES_ROMAN_24, colRelojR, colRelojG, colRelojB);

    // Indicador del Round en curso
    char bufRound[16];
    std::snprintf(bufRound, sizeof(bufRound), "ROUND %d", roundActual);
    dibujarTextoConSombra(bufRound, -0.07f, 0.88f, GLUT_BITMAP_HELVETICA_12, 0.9f, 0.9f, 0.9f);

    // 4. Mensaje Central ("FIGHT!", "K.O.", etc.)
    if (mensajeCentral && mensajeCentral[0] != '\0') {
        float osc = std::sin(tiempoTotal * 8.0f) * 0.01f;
        // Fondo semi-transparente del letrero
        dibujarRectangulo(-0.50f, 0.18f + osc, 1.0f, 0.14f, 0.0f, 0.0f, 0.0f, true);
        dibujarRectangulo(-0.50f, 0.18f + osc, 1.0f, 0.14f, 1.0f, 0.8f, 0.2f, false);

        dibujarTextoConSombra(mensajeCentral, -0.25f, 0.23f + osc,
                              GLUT_BITMAP_TIMES_ROMAN_24, 1.0f, 0.85f, 0.15f);
    }

    // 5. Alerta de STAGE BREAK / Transicion de escenario
    if (alertaTransicionEscenario) {
        dibujarRectangulo(-0.55f, 0.42f, 1.10f, 0.10f, 0.75f, 0.10f, 0.10f, true);
        dibujarRectangulo(-0.55f, 0.42f, 1.10f, 0.10f, 1.00f, 0.90f, 0.20f, false);
        dibujarTextoConSombra("¡STAGE BREAK! - CAMBIO DE ESCENARIO", -0.42f, 0.455f,
                              GLUT_BITMAP_HELVETICA_18, 1.0f, 1.0f, 1.0f);
    }

    // 6. Barra inferior con resumen de controles para guiarse
    dibujarRectangulo(-1.0f, -0.99f, 2.0f, 0.055f, 0.08f, 0.08f, 0.12f, true);
    dibujarTexto("P1: WASD mover/saltar | F: Golp.Suave | G: Fuerte | H: Block | V: Esquive/Parry",
                 -0.95f, -0.965f, GLUT_BITMAP_HELVETICA_10, 0.7f, 0.8f, 0.9f);
    dibujarTexto("P2: Flechas mover/saltar | J: Golp.Suave | K: Fuerte | L: Block | N: Esquive/Parry  |  ESC: Pausa",
                 -0.05f, -0.965f, GLUT_BITMAP_HELVETICA_10, 0.9f, 0.8f, 0.7f);
}
