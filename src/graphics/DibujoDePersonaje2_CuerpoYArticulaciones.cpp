#include "graphics/DibujoDePersonaje2_CuerpoYArticulaciones.h"
#include "graphics/FuncionesParaDibujarFigurasBasicas.h"
#include <GL/freeglut.h>
#include <cmath>

void renderizarGuadalupe(float posX, float posY, int direccion,
                         int estado, float tiempoAnim,
                         float salud, float escudo, bool aturdido) {
    glPushMatrix();

    // Trasladar y espejar en X segun direccion
    glTranslatef(posX, posY, 0.0f);
    glScalef((direccion >= 0) ? 1.0f : -1.0f, 1.0f, 1.0f);

    // 1. Sombra bajo los pies
    dibujarOvalo(0.0f, 0.0f, 0.085f, 0.022f, 14, 0.1f, 0.1f, 0.12f, true);

    // Variables de articulacion y dinamica
    float oscilacion = std::sin(tiempoAnim * 6.5f) * 0.012f;
    float angPierna1 = 0.0f;
    float angPierna2 = 0.0f;
    float brazoFrontalX = 0.07f;
    float brazoFrontalY = 0.17f;
    float brazoTraseroX = -0.05f;
    float brazoTraseroY = 0.15f;

    // Evaluacion del estado de combate
    if (estado == 1) { // CAMINANDO
        angPierna1 = std::sin(tiempoAnim * 11.0f) * 0.045f;
        angPierna2 = -angPierna1;
        brazoFrontalX += std::sin(tiempoAnim * 11.0f) * 0.025f;
        brazoTraseroX -= std::sin(tiempoAnim * 11.0f) * 0.025f;
    } else if (estado == 2) { // SALTANDO
        angPierna1 = -0.035f;
        angPierna2 = 0.015f;
        brazoFrontalY += 0.04f;
        brazoTraseroY += 0.04f;
    } else if (estado == 3) { // AGACHADO
        oscilacion -= 0.05f;
        angPierna1 = 0.03f;
        angPierna2 = -0.03f;
    } else if (estado == 4) { // GOLPE SUAVE (Palma / Golpe rapido)
        brazoFrontalX = 0.18f;
        brazoFrontalY = 0.18f;
    } else if (estado == 5) { // GOLPE FUERTE (Patada lateral alta o puño cargado)
        brazoFrontalX = 0.23f;
        brazoFrontalY = 0.20f;
        angPierna1 = 0.08f;
    } else if (estado == 6) { // BLOQUEANDO (Guardia compacta)
        brazoFrontalX = 0.05f;
        brazoFrontalY = 0.22f;
        brazoTraseroX = 0.03f;
        brazoTraseroY = 0.18f;
    } else if (estado == 7) { // POSTURA DE ESQUIVE / PARRY (Tocandose la cara)
        // REQUISITO: "y de guadalipe como tocandose la cara"
        brazoFrontalX = 0.028f;
        brazoFrontalY = 0.285f; // Mano llevada directamente a la mejilla/rostro
        brazoTraseroX = -0.06f;
        brazoTraseroY = 0.14f;
    } else if (estado == 8) { // CONTRAATAQUE
        brazoFrontalX = 0.24f;
        brazoFrontalY = 0.19f;
    } else if (estado == 9) { // CASTIGO POR FALLAR PARRY
        brazoFrontalX = 0.02f;
        brazoFrontalY = 0.07f;
        brazoTraseroX = -0.03f;
        brazoTraseroY = 0.06f;
        oscilacion -= 0.02f;
    } else if (estado == 10) { // DERROTADO (KO)
        glRotatef(75.0f, 0.0f, 0.0f, 1.0f);
        glTranslatef(0.1f, -0.15f, 0.0f);
    }

    float pelvisY = 0.11f + oscilacion;
    float torsoY  = 0.16f + oscilacion;
    float cuelloY = 0.25f + oscilacion;
    float cabezaY = 0.30f + oscilacion;

    // 2. Pierna Trasera (calzas deportivas oscuras con franja violeta)
    dibujarCapsula(-0.022f, pelvisY, -0.035f + angPierna2, 0.015f, 0.020f, 0.18f, 0.18f, 0.24f);
    // Zapatilla trasera
    dibujarRectangulo(-0.055f + angPierna2, 0.0f, 0.042f, 0.022f, 0.15f, 0.75f, 0.85f, true);

    // 3. Brazo Trasero
    dibujarCapsula(-0.02f, cuelloY - 0.02f, brazoTraseroX, brazoTraseroY + oscilacion, 0.016f, 0.94f, 0.78f, 0.65f);
    // Guantina violeta trasera
    dibujarCirculo(brazoTraseroX, brazoTraseroY + oscilacion, 0.019f, 10, 0.65f, 0.20f, 0.75f, true);

    // 4. Pierna Delantera
    dibujarCapsula(0.022f, pelvisY, 0.035f + angPierna1, 0.015f, 0.022f, 0.22f, 0.22f, 0.30f);
    // Franja lateral decorativa cian en la pierna
    dibujarLinea(0.022f, pelvisY - 0.02f, 0.035f + angPierna1, 0.03f, 2.0f, 0.15f, 0.75f, 0.85f);
    // Zapatilla delantera
    dibujarRectangulo(0.02f + angPierna1, 0.0f, 0.048f, 0.024f, 0.15f, 0.75f, 0.85f, true);

    // 5. Torso / Top deportivo cian y violeta
    float vxTop[4] = { -0.045f, 0.045f, 0.035f, -0.035f };
    float vyTop[4] = { cuelloY, cuelloY, torsoY, torsoY };
    dibujarPoligono(vxTop, vyTop, 4, 0.15f, 0.75f, 0.85f); // Color cian principal

    // Ribete superior violeta del top
    dibujarRectangulo(-0.045f, cuelloY - 0.02f, 0.09f, 0.018f, 0.65f, 0.20f, 0.75f, true);

    // Cintura / Cinturon de entrenamiento
    dibujarRectangulo(-0.042f, pelvisY + 0.01f, 0.084f, 0.022f, 0.20f, 0.20f, 0.25f, true);

    // 6. Cabeza y Cabello con Coleta Ondulante
    // Cabeza (tono piel)
    dibujarCirculo(0.0f, cabezaY, 0.039f, 16, 0.94f, 0.78f, 0.65f, true);

    // Cabello principal frontal y flequillo
    float vxCabello[5] = { -0.04f, 0.035f, 0.015f, -0.025f, -0.045f };
    float vyCabello[5] = { cabezaY + 0.01f, cabezaY + 0.015f, cabezaY + 0.048f, cabezaY + 0.050f, cabezaY + 0.03f };
    dibujarPoligono(vxCabello, vyCabello, 5, 0.35f, 0.18f, 0.10f); // Castaño calido

    // Coleta alta en la parte posterior
    float ondaColeta = std::sin(tiempoAnim * 12.0f) * 0.015f;
    float coletaBaseX = -0.035f;
    float coletaBaseY = cabezaY + 0.03f;
    // Lazo violeta de la coleta
    dibujarCirculo(coletaBaseX, coletaBaseY, 0.012f, 8, 0.75f, 0.25f, 0.85f, true);
    // Mechones ondulantes de la coleta
    float cX[4] = { coletaBaseX, coletaBaseX - 0.05f, coletaBaseX - 0.09f, coletaBaseX - 0.04f };
    float cY[4] = { coletaBaseY, coletaBaseY + 0.03f + ondaColeta, coletaBaseY - 0.04f + ondaColeta, coletaBaseY - 0.02f };
    dibujarPoligono(cX, cY, 4, 0.38f, 0.20f, 0.12f);

    // Ojos y rasgo de Guadalupe
    dibujarLinea(0.010f, cabezaY + 0.007f, 0.025f, cabezaY + 0.009f, 1.8f, 0.15f, 0.10f, 0.10f);
    dibujarCirculo(0.018f, cabezaY + 0.004f, 0.0035f, 8, 0.15f, 0.45f, 0.55f, true); // Ojos turquesa

    // 7. Brazo Delantero
    dibujarCapsula(0.018f, cuelloY - 0.01f, brazoFrontalX, brazoFrontalY + oscilacion, 0.017f, 0.94f, 0.78f, 0.65f);
    // Guantina violeta de Guadalupe
    dibujarCirculo(brazoFrontalX, brazoFrontalY + oscilacion, 0.021f, 12, 0.65f, 0.20f, 0.75f, true);

    // 8. Efecto de Bloqueo
    if (estado == 6 && escudo > 0.0f) {
        float escRad = 0.13f * (escudo / 100.0f);
        if (escRad < 0.05f) escRad = 0.05f;
        dibujarCirculo(0.09f, torsoY + 0.05f, escRad, 16, 0.7f, 0.3f, 0.9f, false);
        dibujarEstrella(0.09f, torsoY + 0.05f, escRad, escRad * 0.7f, 6, tiempoAnim * 3.0f, 0.8f, 0.4f, 1.0f);
    }

    // 9. Destello de Parry Activo (aura cian brillante)
    if (estado == 7) {
        float auraRad = 0.11f + std::sin(tiempoAnim * 20.0f) * 0.02f;
        dibujarCirculo(brazoFrontalX, brazoFrontalY, auraRad, 12, 0.2f, 0.9f, 1.0f, false);
    }

    // 10. Efecto de Aturdimiento / Stun
    if (aturdido) {
        for (int i = 0; i < 3; i++) {
            float ang = tiempoAnim * 8.0f + (float)i * (2.0f * PI_CONST / 3.0f);
            float ex = std::cos(ang) * 0.065f;
            float ey = cabezaY + 0.065f + std::sin(ang) * 0.022f;
            dibujarEstrella(ex, ey, 0.018f, 0.008f, 5, tiempoAnim * 10.0f, 0.3f, 0.9f, 1.0f);
        }
    }

    glPopMatrix();
}
