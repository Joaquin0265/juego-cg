#include "graphics/DibujoFondoEscenario_MontaniasEdificios.h"
#include "graphics/FuncionesParaDibujarFigurasBasicas.h"
#include <GL/freeglut.h>
#include <cmath>

RenderizadorEscenario::RenderizadorEscenario() {}

void RenderizadorEscenario::renderizar(TipoEscenario tipo, int variacion, float nivelSuelo) {
    if (tipo == ESCENARIO_PARQUE) {
        renderizarParque(variacion, nivelSuelo);
    } else {
        renderizarUniversidad(variacion, nivelSuelo);
    }
}

// ============================================================================
// ESCENARIO 1: EL PARQUE
// ============================================================================
void RenderizadorEscenario::dibujarNube(float x, float y, float escala) {
    dibujarCirculo(x, y, 0.08f * escala, 14, 0.95f, 0.97f, 1.0f, true);
    dibujarCirculo(x + 0.07f * escala, y + 0.02f * escala, 0.07f * escala, 14, 0.95f, 0.97f, 1.0f, true);
    dibujarCirculo(x - 0.06f * escala, y - 0.01f * escala, 0.06f * escala, 14, 0.92f, 0.95f, 0.98f, true);
    dibujarCirculo(x + 0.12f * escala, y - 0.01f * escala, 0.05f * escala, 14, 0.92f, 0.95f, 0.98f, true);
}

void RenderizadorEscenario::dibujarArbol(float x, float y, float escala) {
    // Tronco de madera con ramas
    float troncoAncho = 0.06f * escala;
    float troncoAlto = 0.40f * escala;
    dibujarRectanguloDegradado(x - troncoAncho * 0.5f, y, troncoAncho, troncoAlto,
                              0.35f, 0.20f, 0.10f, 0.48f, 0.28f, 0.14f, false);

    // Rama izquierda y derecha
    dibujarLinea(x, y + troncoAlto * 0.6f, x - 0.08f * escala, y + troncoAlto * 0.8f, 4.0f, 0.42f, 0.24f, 0.12f);
    dibujarLinea(x, y + troncoAlto * 0.7f, x + 0.09f * escala, y + troncoAlto * 0.9f, 4.0f, 0.42f, 0.24f, 0.12f);

    // Copa de follaje frondoso generada por poligonos y circulos verdes
    float copaY = y + troncoAlto;
    // Sombra inferior de follaje
    dibujarCirculo(x, copaY, 0.18f * escala, 16, 0.12f, 0.42f, 0.15f, true);
    dibujarCirculo(x - 0.10f * escala, copaY + 0.05f * escala, 0.14f * escala, 16, 0.16f, 0.52f, 0.18f, true);
    dibujarCirculo(x + 0.10f * escala, copaY + 0.05f * escala, 0.14f * escala, 16, 0.16f, 0.52f, 0.18f, true);
    // Copa superior mas iluminada
    dibujarCirculo(x, copaY + 0.12f * escala, 0.15f * escala, 16, 0.22f, 0.65f, 0.24f, true);
    dibujarCirculo(x - 0.05f * escala, copaY + 0.10f * escala, 0.11f * escala, 14, 0.28f, 0.75f, 0.28f, true);
}

void RenderizadorEscenario::dibujarBancoParque(float x, float y) {
    // Patas de hierro forjado
    dibujarRectangulo(x - 0.08f, y, 0.015f, 0.08f, 0.15f, 0.15f, 0.15f, true);
    dibujarRectangulo(x + 0.065f, y, 0.015f, 0.08f, 0.15f, 0.15f, 0.15f, true);

    // Tablones de madera horizontal
    dibujarRectangulo(x - 0.10f, y + 0.07f, 0.20f, 0.02f, 0.55f, 0.32f, 0.14f, true);
    dibujarRectangulo(x - 0.10f, y + 0.095f, 0.20f, 0.018f, 0.62f, 0.36f, 0.16f, true);

    // Respaldo de madera
    dibujarRectangulo(x - 0.10f, y + 0.13f, 0.20f, 0.022f, 0.55f, 0.32f, 0.14f, true);
    dibujarRectangulo(x - 0.10f, y + 0.16f, 0.20f, 0.022f, 0.62f, 0.36f, 0.16f, true);

    // Soportes del respaldo
    dibujarRectangulo(x - 0.07f, y + 0.09f, 0.012f, 0.10f, 0.2f, 0.2f, 0.2f, true);
    dibujarRectangulo(x + 0.058f, y + 0.09f, 0.012f, 0.10f, 0.2f, 0.2f, 0.2f, true);
}

void RenderizadorEscenario::dibujarFarola(float x, float y) {
    // Base de hierro
    dibujarRectangulo(x - 0.025f, y, 0.05f, 0.04f, 0.2f, 0.22f, 0.25f, true);
    // Poste vertical
    dibujarRectangulo(x - 0.012f, y + 0.04f, 0.024f, 0.40f, 0.25f, 0.27f, 0.30f, true);
    // Brazo decorativo superior
    dibujarRectangulo(x - 0.04f, y + 0.42f, 0.08f, 0.02f, 0.2f, 0.22f, 0.25f, true);

    // Farol / Linterna poligonal
    float fx[4] = { x - 0.035f, x + 0.035f, x + 0.025f, x - 0.025f };
    float fy[4] = { y + 0.44f,  y + 0.44f,  y + 0.36f,  y + 0.36f };
    dibujarPoligono(fx, fy, 4, 1.0f, 0.92f, 0.45f); // Luz brillante amarilla

    // Techo del farol
    float tx[3] = { x - 0.045f, x + 0.045f, x };
    float ty[3] = { y + 0.44f,  y + 0.44f,  y + 0.48f };
    dibujarPoligono(tx, ty, 3, 0.18f, 0.20f, 0.22f);
}

void RenderizadorEscenario::renderizarParque(int variacion, float nivelSuelo) {
    // 1. Cielo con degradado diurno soleado
    dibujarRectanguloDegradado(-1.0f, nivelSuelo, 2.0f, 1.0f - nivelSuelo,
                              0.85f, 0.92f, 0.98f,  // Cerca del horizonte
                              0.30f, 0.60f, 0.95f,  // Cenit azul cielo
                              true);

    // 2. Sol poligonal
    dibujarCirculo(0.65f, 0.70f, 0.10f, 24, 1.0f, 0.90f, 0.20f, true);
    dibujarCirculo(0.65f, 0.70f, 0.13f, 24, 1.0f, 0.95f, 0.40f, false);

    // 3. Nubes en el cielo
    dibujarNube(-0.65f, 0.75f, 1.1f);
    dibujarNube(-0.15f, 0.82f, 0.8f);
    dibujarNube(0.25f, 0.68f, 0.9f);

    // 4. Colinas distantes (poligonos de fondo)
    float colina1X[5] = { -1.0f, -0.6f, -0.1f, 0.4f, 1.0f };
    float colina1Y[5] = { nivelSuelo, nivelSuelo + 0.25f, nivelSuelo + 0.15f, nivelSuelo + 0.28f, nivelSuelo };
    dibujarPoligono(colina1X, colina1Y, 5, 0.25f, 0.55f, 0.35f);

    // 5. Suelo del parque: cesped y sendero adoquinado
    dibujarRectanguloDegradado(-1.0f, -1.0f, 2.0f, nivelSuelo - (-1.0f),
                              0.20f, 0.14f, 0.08f,  // Tierra inferior
                              0.18f, 0.50f, 0.15f,  // Cesped superior
                              true);

    // Borde de cesped recortado
    dibujarRectangulo(-1.0f, nivelSuelo - 0.02f, 2.0f, 0.02f, 0.28f, 0.65f, 0.20f, true);

    // Sendero peatonal en el suelo
    dibujarRectangulo(-0.95f, nivelSuelo - 0.09f, 1.9f, 0.06f, 0.65f, 0.62f, 0.58f, true);
    // Rayas de baldosas del sendero
    for (float bx = -0.90f; bx < 0.95f; bx += 0.10f) {
        dibujarLinea(bx, nivelSuelo - 0.09f, bx + 0.02f, nivelSuelo - 0.03f, 1.5f, 0.52f, 0.50f, 0.46f);
    }

    // 6. Elementos modulares del parque segun la variacion
    if (variacion == 0) {
        dibujarArbol(-0.75f, nivelSuelo, 1.1f);
        dibujarArbol(-0.40f, nivelSuelo, 0.85f);
        dibujarBancoParque(-0.15f, nivelSuelo);
        dibujarFarola(0.35f, nivelSuelo);
        dibujarArbol(0.75f, nivelSuelo, 1.15f);
    } else if (variacion == 1) {
        dibujarFarola(-0.70f, nivelSuelo);
        dibujarArbol(-0.35f, nivelSuelo, 1.0f);
        dibujarBancoParque(0.0f, nivelSuelo);
        dibujarArbol(0.40f, nivelSuelo, 0.9f);
        dibujarFarola(0.75f, nivelSuelo);
    } else {
        dibujarArbol(-0.80f, nivelSuelo, 1.2f);
        dibujarBancoParque(-0.45f, nivelSuelo);
        dibujarFarola(-0.10f, nivelSuelo);
        dibujarBancoParque(0.35f, nivelSuelo);
        dibujarArbol(0.70f, nivelSuelo, 1.05f);
    }

    // Pequeñas flores decorativas en el cesped
    for (int i = 0; i < 8; i++) {
        float fx = -0.85f + (float)i * 0.24f;
        float fy = nivelSuelo - 0.015f;
        dibujarCirculo(fx, fy, 0.012f, 8, 0.95f, 0.85f, 0.2f, true);
        dibujarCirculo(fx, fy + 0.005f, 0.006f, 6, 0.95f, 0.2f, 0.3f, true);
    }
}


// ============================================================================
// ESCENARIO 2: ENTRADA DE LA UNIVERSIDAD
// ============================================================================
void RenderizadorEscenario::dibujarColumna(float x, float y, float ancho, float alto) {
    // Base escalonada de la columna (Plinto)
    dibujarRectangulo(x - ancho * 0.7f, y, ancho * 1.4f, alto * 0.08f, 0.75f, 0.74f, 0.76f, true);
    dibujarRectangulo(x - ancho * 0.55f, y + alto * 0.08f, ancho * 1.1f, alto * 0.05f, 0.82f, 0.81f, 0.83f, true);

    // Fuste de la columna con degradado y estrias verticales
    dibujarRectanguloDegradado(x - ancho * 0.4f, y + alto * 0.13f, ancho * 0.8f, alto * 0.74f,
                              0.78f, 0.77f, 0.80f,  // Lado sombreado
                              0.92f, 0.91f, 0.94f,  // Lado claro
                              false);

    // Estrias verticales clásicas
    float estriaX1 = x - ancho * 0.2f;
    float estriaX2 = x;
    float estriaX3 = x + ancho * 0.2f;
    dibujarLinea(estriaX1, y + alto * 0.15f, estriaX1, y + alto * 0.85f, 2.0f, 0.65f, 0.64f, 0.67f);
    dibujarLinea(estriaX2, y + alto * 0.15f, estriaX2, y + alto * 0.85f, 2.0f, 0.65f, 0.64f, 0.67f);
    dibujarLinea(estriaX3, y + alto * 0.15f, estriaX3, y + alto * 0.85f, 2.0f, 0.65f, 0.64f, 0.67f);

    // Capitel de la columna (Ábaco y Equino clásico)
    dibujarRectangulo(x - ancho * 0.6f, y + alto * 0.87f, ancho * 1.2f, alto * 0.06f, 0.85f, 0.84f, 0.87f, true);
    dibujarRectangulo(x - ancho * 0.75f, y + alto * 0.93f, ancho * 1.5f, alto * 0.07f, 0.75f, 0.74f, 0.77f, true);
    // Voluta o adorno curvo
    dibujarCirculo(x - ancho * 0.6f, y + alto * 0.90f, 0.02f, 10, 0.70f, 0.69f, 0.72f, true);
    dibujarCirculo(x + ancho * 0.6f, y + alto * 0.90f, 0.02f, 10, 0.70f, 0.69f, 0.72f, true);
}

void RenderizadorEscenario::dibujarEscalinata(float nivelSuelo) {
    // Serie de peldaños de granito
    int totalPeldanos = 4;
    float altoPeldano = 0.035f;
    for (int i = 0; i < totalPeldanos; i++) {
        float py = nivelSuelo - (float)i * altoPeldano;
        float bordeSombra = (i % 2 == 0) ? 0.72f : 0.68f;
        dibujarRectangulo(-0.95f, py - altoPeldano, 1.9f, altoPeldano,
                          bordeSombra, bordeSombra, bordeSombra + 0.02f, true);
        // Borde superior iluminado del peldaño
        dibujarLinea(-0.95f, py, 0.95f, py, 2.0f, 0.88f, 0.88f, 0.90f);
    }
}

void RenderizadorEscenario::dibujarPorticoUniversidad(float centroX, float nivelSuelo) {
    // Fachada del edificio principal de fondo
    dibujarRectanguloDegradado(-0.90f, nivelSuelo, 1.80f, 0.85f,
                              0.55f, 0.52f, 0.56f,
                              0.38f, 0.36f, 0.42f,
                              true);

    // Ventanas de los pisos superiores con luz academica encendida
    for (float wx = -0.80f; wx < 0.85f; wx += 0.22f) {
        if (std::abs(wx - centroX) > 0.18f) { // Dejar espacio para la puerta central
            // Ventana piso 2
            dibujarRectangulo(wx, nivelSuelo + 0.55f, 0.12f, 0.18f, 0.95f, 0.88f, 0.45f, true);
            dibujarRectangulo(wx, nivelSuelo + 0.55f, 0.12f, 0.18f, 0.20f, 0.20f, 0.25f, false);
            dibujarLinea(wx + 0.06f, nivelSuelo + 0.55f, wx + 0.06f, nivelSuelo + 0.73f, 1.5f, 0.20f, 0.20f, 0.25f);
            dibujarLinea(wx, nivelSuelo + 0.64f, wx + 0.12f, nivelSuelo + 0.64f, 1.5f, 0.20f, 0.20f, 0.25f);

            // Ventana piso 1
            dibujarRectangulo(wx, nivelSuelo + 0.28f, 0.12f, 0.18f, 0.88f, 0.82f, 0.40f, true);
            dibujarRectangulo(wx, nivelSuelo + 0.28f, 0.12f, 0.18f, 0.20f, 0.20f, 0.25f, false);
            dibujarLinea(wx + 0.06f, nivelSuelo + 0.28f, wx + 0.06f, nivelSuelo + 0.46f, 1.5f, 0.20f, 0.20f, 0.25f);
            dibujarLinea(wx, nivelSuelo + 0.37f, wx + 0.12f, nivelSuelo + 0.37f, 1.5f, 0.20f, 0.20f, 0.25f);
        }
    }

    // Puerta de entrada monumental de doble hoja
    dibujarRectangulo(centroX - 0.16f, nivelSuelo, 0.32f, 0.45f, 0.22f, 0.14f, 0.08f, true);
    // Arco superior de la puerta
    dibujarCirculo(centroX, nivelSuelo + 0.45f, 0.16f, 16, 0.22f, 0.14f, 0.08f, true);
    // Cristaleras del arco
    dibujarCirculo(centroX, nivelSuelo + 0.45f, 0.13f, 16, 0.85f, 0.90f, 0.95f, true);
    // Moldura exterior de la puerta
    dibujarRectangulo(centroX - 0.17f, nivelSuelo, 0.34f, 0.47f, 0.68f, 0.67f, 0.70f, false);

    // Arquitrabe / Cornisa horizontal superior
    dibujarRectangulo(-0.85f, nivelSuelo + 0.65f, 1.70f, 0.08f, 0.78f, 0.77f, 0.80f, true);
    dibujarRectangulo(-0.88f, nivelSuelo + 0.73f, 1.76f, 0.05f, 0.84f, 0.83f, 0.86f, true);

    // Fronton triangular clasico sobre el portico
    float triX[3] = { -0.75f, 0.75f, 0.0f };
    float triY[3] = { nivelSuelo + 0.78f, nivelSuelo + 0.78f, nivelSuelo + 0.96f };
    dibujarPoligono(triX, triY, 3, 0.75f, 0.74f, 0.78f);
    // Relieve interior del fronton
    float triInX[3] = { -0.68f, 0.68f, 0.0f };
    float triInY[3] = { nivelSuelo + 0.80f, nivelSuelo + 0.80f, nivelSuelo + 0.93f };
    dibujarPoligono(triInX, triInY, 3, 0.62f, 0.61f, 0.65f);

    // Letrero de la Universidad en el arquitrabe
    dibujarTextoConSombra("FACULTAD DE COMPUTACION & INGENIERIA", -0.42f, nivelSuelo + 0.68f,
                          GLUT_BITMAP_HELVETICA_12, 1.0f, 0.85f, 0.25f);
}

void RenderizadorEscenario::renderizarUniversidad(int variacion, float nivelSuelo) {
    // 1. Cielo crepuscular / atardecer academico elegante
    dibujarRectanguloDegradado(-1.0f, nivelSuelo, 2.0f, 1.0f - nivelSuelo,
                              0.85f, 0.45f, 0.35f,  // Naranja/rosado calido horizonte
                              0.15f, 0.15f, 0.35f,  // Azul noche superior
                              true);

    // 2. Luna creciente poligonal
    dibujarCirculo(0.72f, 0.78f, 0.06f, 16, 0.95f, 0.95f, 0.85f, true);
    dibujarCirculo(0.74f, 0.79f, 0.05f, 16, 0.22f, 0.20f, 0.38f, true); // Recorte de la luna

    // 3. Estructura arquitectonica principal
    dibujarPorticoUniversidad(0.0f, nivelSuelo);

    // 4. Columnas clasicas en el frente segun la variacion
    if (variacion == 0) {
        dibujarColumna(-0.68f, nivelSuelo, 0.08f, 0.65f);
        dibujarColumna(-0.35f, nivelSuelo, 0.08f, 0.65f);
        dibujarColumna( 0.35f, nivelSuelo, 0.08f, 0.65f);
        dibujarColumna( 0.68f, nivelSuelo, 0.08f, 0.65f);
    } else if (variacion == 1) {
        dibujarColumna(-0.75f, nivelSuelo, 0.09f, 0.65f);
        dibujarColumna(-0.45f, nivelSuelo, 0.09f, 0.65f);
        dibujarColumna(-0.18f, nivelSuelo, 0.08f, 0.65f);
        dibujarColumna( 0.18f, nivelSuelo, 0.08f, 0.65f);
        dibujarColumna( 0.45f, nivelSuelo, 0.09f, 0.65f);
        dibujarColumna( 0.75f, nivelSuelo, 0.09f, 0.65f);
    } else {
        dibujarColumna(-0.60f, nivelSuelo, 0.085f, 0.65f);
        dibujarColumna(-0.25f, nivelSuelo, 0.085f, 0.65f);
        dibujarColumna( 0.25f, nivelSuelo, 0.085f, 0.65f);
        dibujarColumna( 0.60f, nivelSuelo, 0.085f, 0.65f);
    }

    // 5. Escalinata y suelo adoquinado
    dibujarEscalinata(nivelSuelo);

    // Suelo inferior adoquinado
    dibujarRectanguloDegradado(-1.0f, -1.0f, 2.0f, (nivelSuelo - 0.14f) - (-1.0f),
                              0.18f, 0.18f, 0.22f,
                              0.32f, 0.32f, 0.36f,
                              true);

    // Lineas de adoquines en perspectiva
    for (float ax = -0.92f; ax < 0.95f; ax += 0.12f) {
        dibujarLinea(ax, -1.0f, ax * 0.9f, nivelSuelo - 0.14f, 1.2f, 0.24f, 0.24f, 0.28f);
    }
}
