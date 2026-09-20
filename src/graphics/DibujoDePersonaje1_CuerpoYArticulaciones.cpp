#include "graphics/DibujoDePersonaje1_CuerpoYArticulaciones.h"
#include "graphics/FuncionesParaDibujarFigurasBasicas.h"
#include <GL/freeglut.h>
#include <cmath>

void renderizarLeonardox(float posX, float posY, int direccion,
                        int estado, float tiempoAnim,
                        float salud, float escudo, bool aturdido) {
    glPushMatrix();

    // Trasladar al origen del personaje y aplicar orientacion (espejo con glScalef)
    glTranslatef(posX, posY, 0.0f);
    glScalef((direccion >= 0) ? 1.0f : -1.0f, 1.0f, 1.0f);

    // 1. Sombra bajo los pies
    dibujarOvalo(0.0f, 0.0f, 0.09f, 0.025f, 14, 0.1f, 0.1f, 0.12f, true);

    // Variables de articulacion segun estado y tiempo
    float oscilacion = std::sin(tiempoAnim * 6.0f) * 0.015f;
    float angPierna1 = 0.0f;
    float angPierna2 = 0.0f;
    float brazoFrontalX = 0.08f;
    float brazoFrontalY = 0.18f;
    float brazoTraseroX = -0.06f;
    float brazoTraseroY = 0.16f;

    // Evaluacion del estado de animacion
    if (estado == 1) { // CAMINANDO
        angPierna1 = std::sin(tiempoAnim * 10.0f) * 0.04f;
        angPierna2 = -angPierna1;
        brazoFrontalX += std::sin(tiempoAnim * 10.0f) * 0.03f;
        brazoTraseroX -= std::sin(tiempoAnim * 10.0f) * 0.03f;
    } else if (estado == 2) { // SALTANDO
        angPierna1 = -0.03f;
        angPierna2 = 0.02f;
        brazoFrontalY += 0.04f;
        brazoTraseroY += 0.03f;
    } else if (estado == 3) { // AGACHADO
        oscilacion -= 0.05f;
        angPierna1 = 0.03f;
        angPierna2 = -0.03f;
    } else if (estado == 4) { // GOLPE SUAVE (Jab frontal rapido)
        brazoFrontalX = 0.17f; // Extension rapida de puño
        brazoFrontalY = 0.19f;
    } else if (estado == 5) { // GOLPE FUERTE (Gancho o derechazo cargado)
        brazoFrontalX = 0.22f; // Maxima extension
        brazoFrontalY = 0.21f;
        brazoTraseroX = -0.10f;
    } else if (estado == 6) { // BLOQUEANDO (Guardia frontal con brazos cruzados)
        brazoFrontalX = 0.06f;
        brazoFrontalY = 0.22f;
        brazoTraseroX = 0.04f;
        brazoTraseroY = 0.18f;
    } else if (estado == 7) { // POSTURA DE ESQUIVE / PARRY (Levantar un brazo en alto)
        // REQUISITO: "que leonardox sea su forma de esquivar levantar un brazo"
        brazoFrontalX = 0.04f;
        brazoFrontalY = 0.32f; // Brazo completamente en alto desafiante
        brazoTraseroX = -0.05f;
        brazoTraseroY = 0.14f;
    } else if (estado == 8) { // CONTRAATAQUE (Golpe fulminante tras parry exitoso)
        brazoFrontalX = 0.25f;
        brazoFrontalY = 0.20f;
    } else if (estado == 9) { // CASTIGO POR FALLAR PARRY (Inmovil y desprotegido)
        brazoFrontalX = 0.02f;
        brazoFrontalY = 0.08f; // Brazos caidos
        brazoTraseroX = -0.03f;
        brazoTraseroY = 0.07f;
        oscilacion -= 0.02f;
    } else if (estado == 10) { // DERROTADO (KO en el suelo)
        // Rotar al suelo
        glRotatef(75.0f, 0.0f, 0.0f, 1.0f);
        glTranslatef(0.1f, -0.15f, 0.0f);
    }

    // Altura base de pelvis y torso con oscilacion
    float pelvisY = 0.11f + oscilacion;
    float torsoY  = 0.16f + oscilacion;
    float cuelloY = 0.26f + oscilacion;
    float cabezaY = 0.31f + oscilacion;

    // 2. Pierna Trasera (pantalones marciales oscuros)
    dibujarCapsula(-0.025f, pelvisY, -0.04f + angPierna2, 0.015f, 0.022f, 0.15f, 0.15f, 0.18f);
    // Bota/pie trasero
    dibujarRectangulo(-0.06f + angPierna2, 0.0f, 0.045f, 0.025f, 0.85f, 0.2f, 0.2f, true);

    // 3. Brazo Trasero
    dibujarCapsula(-0.02f, cuelloY - 0.02f, brazoTraseroX, brazoTraseroY + oscilacion, 0.018f, 0.88f, 0.70f, 0.55f);
    // Guante rojo trasero
    dibujarCirculo(brazoTraseroX, brazoTraseroY + oscilacion, 0.022f, 10, 0.85f, 0.15f, 0.15f, true);

    // 4. Pierna Delantera
    dibujarCapsula(0.025f, pelvisY, 0.04f + angPierna1, 0.015f, 0.024f, 0.20f, 0.20f, 0.24f);
    // Bota/pie delantero
    dibujarRectangulo(0.02f + angPierna1, 0.0f, 0.05f, 0.025f, 0.85f, 0.2f, 0.2f, true);

    // 5. Torso / Kimono marcial sin mangas
    // Pecho y abdomen (color ropa de combate oscuro con detalles)
    float vxTorso[4] = { -0.05f, 0.05f, 0.04f, -0.04f };
    float vyTorso[4] = { cuelloY, cuelloY, torsoY, torsoY };
    dibujarPoligono(vxTorso, vyTorso, 4, 0.22f, 0.22f, 0.26f);

    // Cinturon / Faja roja marcial
    dibujarRectangulo(-0.055f, pelvisY + 0.01f, 0.11f, 0.025f, 0.85f, 0.15f, 0.15f, true);
    // Cabos colgantes de la cinta del cinturon
    dibujarLinea(0.01f, pelvisY + 0.01f, 0.02f, pelvisY - 0.04f, 2.5f, 0.85f, 0.15f, 0.15f);
    dibujarLinea(0.02f, pelvisY + 0.01f, 0.035f, pelvisY - 0.035f, 2.5f, 0.85f, 0.15f, 0.15f);

    // 6. Cabeza y Rostro
    // Cabeza (piel)
    dibujarCirculo(0.0f, cabezaY, 0.042f, 16, 0.92f, 0.74f, 0.58f, true);
    // Cabello marcial castaño/oscuro con puntas
    float vxPelo[5] = { -0.045f, 0.04f, 0.02f, -0.02f, -0.05f };
    float vyPelo[5] = { cabezaY + 0.02f, cabezaY + 0.02f, cabezaY + 0.055f, cabezaY + 0.058f, cabezaY + 0.04f };
    dibujarPoligono(vxPelo, vyPelo, 5, 0.18f, 0.12f, 0.08f);

    // Cinta roja en la frente caracteristica de Leonardox
    dibujarRectangulo(-0.042f, cabezaY + 0.01f, 0.084f, 0.015f, 0.88f, 0.12f, 0.12f, true);
    // Colas ondeantes de la cinta de la cabeza
    float ondaCinta = std::sin(tiempoAnim * 12.0f) * 0.01f;
    dibujarLinea(-0.042f, cabezaY + 0.015f, -0.09f, cabezaY + 0.02f + ondaCinta, 3.0f, 0.88f, 0.12f, 0.12f);
    dibujarLinea(-0.042f, cabezaY + 0.010f, -0.08f, cabezaY + 0.005f + ondaCinta, 3.0f, 0.88f, 0.12f, 0.12f);

    // Ojo y ceja
    dibujarLinea(0.012f, cabezaY + 0.008f, 0.028f, cabezaY + 0.008f, 1.8f, 0.1f, 0.1f, 0.1f);
    dibujarCirculo(0.022f, cabezaY + 0.004f, 0.004f, 8, 0.1f, 0.1f, 0.1f, true);

    // 7. Brazo Delantero
    dibujarCapsula(0.02f, cuelloY - 0.01f, brazoFrontalX, brazoFrontalY + oscilacion, 0.020f, 0.92f, 0.74f, 0.58f);
    // Guante rojo de Leonardox
    dibujarCirculo(brazoFrontalX, brazoFrontalY + oscilacion, 0.025f, 12, 0.88f, 0.12f, 0.12f, true);

    // 8. Efecto visual de Bloqueo (Escudo poligonal celeste)
    if (estado == 6 && escudo > 0.0f) {
        float escRad = 0.14f * (escudo / 100.0f);
        if (escRad < 0.05f) escRad = 0.05f;
        dibujarCirculo(0.10f, torsoY + 0.05f, escRad, 16, 0.2f, 0.8f, 1.0f, false);
        dibujarEstrella(0.10f, torsoY + 0.05f, escRad, escRad * 0.7f, 6, tiempoAnim * 3.0f, 0.4f, 0.9f, 1.0f);
    }

    // 9. Destello de Parry Activo (aura amarilla de anticipacion)
    if (estado == 7) {
        float auraRad = 0.12f + std::sin(tiempoAnim * 20.0f) * 0.02f;
        dibujarCirculo(brazoFrontalX, brazoFrontalY, auraRad, 12, 1.0f, 0.85f, 0.1f, false);
    }

    // 10. Efecto de Aturdimiento / Stun (estrellas girando en orbita sobre la cabeza)
    if (aturdido) {
        for (int i = 0; i < 3; i++) {
            float ang = tiempoAnim * 8.0f + (float)i * (2.0f * PI_CONST / 3.0f);
            float ex = std::cos(ang) * 0.07f;
            float ey = cabezaY + 0.07f + std::sin(ang) * 0.025f;
            dibujarEstrella(ex, ey, 0.020f, 0.009f, 5, tiempoAnim * 10.0f, 1.0f, 0.9f, 0.1f);
        }
    }

    glPopMatrix();
}
