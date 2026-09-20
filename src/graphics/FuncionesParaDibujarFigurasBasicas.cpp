#include "graphics/FuncionesParaDibujarFigurasBasicas.h"
#include <cmath>

#ifndef PI_CONST
#define PI_CONST 3.14159265358979323846f
#endif

void dibujarRectangulo(float x, float y, float ancho, float alto,
                       float r, float g, float b, bool relleno) {
    glColor3f(r, g, b);
    if (relleno) {
        glBegin(GL_QUADS);
            glVertex2f(x, y);
            glVertex2f(x + ancho, y);
            glVertex2f(x + ancho, y + alto);
            glVertex2f(x, y + alto);
        glEnd();
    } else {
        glBegin(GL_LINE_LOOP);
            glVertex2f(x, y);
            glVertex2f(x + ancho, y);
            glVertex2f(x + ancho, y + alto);
            glVertex2f(x, y + alto);
        glEnd();
    }
}

void dibujarRectanguloDegradado(float x, float y, float ancho, float alto,
                               float r1, float g1, float b1,
                               float r2, float g2, float b2,
                               bool vertical) {
    glBegin(GL_QUADS);
    if (vertical) {
        // De abajo (r1, g1, b1) hacia arriba (r2, g2, b2)
        glColor3f(r1, g1, b1);
        glVertex2f(x, y);
        glVertex2f(x + ancho, y);
        glColor3f(r2, g2, b2);
        glVertex2f(x + ancho, y + alto);
        glVertex2f(x, y + alto);
    } else {
        // De izquierda (r1, g1, b1) hacia derecha (r2, g2, b2)
        glColor3f(r1, g1, b1);
        glVertex2f(x, y);
        glColor3f(r2, g2, b2);
        glVertex2f(x + ancho, y);
        glVertex2f(x + ancho, y + alto);
        glColor3f(r1, g1, b1);
        glVertex2f(x, y + alto);
    }
    glEnd();
}

void dibujarCirculo(float cx, float cy, float radio, int segmentos,
                    float r, float g, float b, bool relleno) {
    glColor3f(r, g, b);
    if (relleno) {
        glBegin(GL_TRIANGLE_FAN);
            glVertex2f(cx, cy); // Centro
            for (int i = 0; i <= segmentos; i++) {
                float angulo = 2.0f * PI_CONST * ((float)i / (float)segmentos);
                float x = cx + radio * std::cos(angulo);
                float y = cy + radio * std::sin(angulo);
                glVertex2f(x, y);
            }
        glEnd();
    } else {
        glBegin(GL_LINE_LOOP);
            for (int i = 0; i < segmentos; i++) {
                float angulo = 2.0f * PI_CONST * ((float)i / (float)segmentos);
                float x = cx + radio * std::cos(angulo);
                float y = cy + radio * std::sin(angulo);
                glVertex2f(x, y);
            }
        glEnd();
    }
}

void dibujarOvalo(float cx, float cy, float radioX, float radioY, int segmentos,
                  float r, float g, float b, bool relleno) {
    glColor3f(r, g, b);
    if (relleno) {
        glBegin(GL_TRIANGLE_FAN);
            glVertex2f(cx, cy);
            for (int i = 0; i <= segmentos; i++) {
                float angulo = 2.0f * PI_CONST * ((float)i / (float)segmentos);
                float x = cx + radioX * std::cos(angulo);
                float y = cy + radioY * std::sin(angulo);
                glVertex2f(x, y);
            }
        glEnd();
    } else {
        glBegin(GL_LINE_LOOP);
            for (int i = 0; i < segmentos; i++) {
                float angulo = 2.0f * PI_CONST * ((float)i / (float)segmentos);
                float x = cx + radioX * std::cos(angulo);
                float y = cy + radioY * std::sin(angulo);
                glVertex2f(x, y);
            }
        glEnd();
    }
}

void dibujarLinea(float x1, float y1, float x2, float y2, float grosor,
                  float r, float g, float b) {
    glLineWidth(grosor);
    glColor3f(r, g, b);
    glBegin(GL_LINES);
        glVertex2f(x1, y1);
        glVertex2f(x2, y2);
    glEnd();
    glLineWidth(1.0f); // Restaurar grosor estándar
}

void dibujarPoligono(const float* vx, const float* vy, int cantidadVertices,
                     float r, float g, float b) {
    if (cantidadVertices < 3) return;
    glColor3f(r, g, b);
    glBegin(GL_POLYGON);
    for (int i = 0; i < cantidadVertices; i++) {
        glVertex2f(vx[i], vy[i]);
    }
    glEnd();
}

void dibujarEstrella(float cx, float cy, float radioExt, float radioInt,
                     int puntas, float anguloRotacion,
                     float r, float g, float b) {
    glColor3f(r, g, b);
    int totalPuntos = puntas * 2;
    glBegin(GL_TRIANGLE_FAN);
        glVertex2f(cx, cy);
        for (int i = 0; i <= totalPuntos; i++) {
            float angulo = anguloRotacion + (2.0f * PI_CONST * ((float)i / (float)totalPuntos));
            float rad = (i % 2 == 0) ? radioExt : radioInt;
            float px = cx + rad * std::cos(angulo);
            float py = cy + rad * std::sin(angulo);
            glVertex2f(px, py);
        }
    glEnd();
}

void dibujarCapsula(float x1, float y1, float x2, float y2, float radio,
                    float r, float g, float b) {
    // Calcula el vector perpendicular para unir los dos extremos
    float dx = x2 - x1;
    float dy = y2 - y1;
    float len = std::sqrt(dx * dx + dy * dy);
    if (len < 0.0001f) {
        dibujarCirculo(x1, y1, radio, 12, r, g, b, true);
        return;
    }

    float nx = -dy / len * radio;
    float ny =  dx / len * radio;

    // Cuerpo rectangular central
    glColor3f(r, g, b);
    glBegin(GL_QUADS);
        glVertex2f(x1 + nx, y1 + ny);
        glVertex2f(x2 + nx, y2 + ny);
        glVertex2f(x2 - nx, y2 - ny);
        glVertex2f(x1 - nx, y1 - ny);
    glEnd();

    // Tapas circulares en ambos extremos
    dibujarCirculo(x1, y1, radio, 12, r, g, b, true);
    dibujarCirculo(x2, y2, radio, 12, r, g, b, true);
}

void dibujarTexto(const char* texto, float x, float y, void* fuente,
                  float r, float g, float b) {
    if (!texto) return;
    glColor3f(r, g, b);
    glRasterPos2f(x, y);
    for (const char* c = texto; *c != '\0'; c++) {
        glutBitmapCharacter(fuente, *c);
    }
}

void dibujarTextoConSombra(const char* texto, float x, float y, void* fuente,
                           float r, float g, float b) {
    if (!texto) return;
    // Sombra oscura desplazada
    dibujarTexto(texto, x + 0.004f, y - 0.004f, fuente, 0.0f, 0.0f, 0.0f);
    // Texto frontal
    dibujarTexto(texto, x, y, fuente, r, g, b);
}
