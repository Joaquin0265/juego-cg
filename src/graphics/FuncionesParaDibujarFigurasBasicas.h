#ifndef FUNCIONES_DIBUJO_FIGURAS_BASICAS_H
#define FUNCIONES_DIBUJO_FIGURAS_BASICAS_H

#include <GL/freeglut.h>

#ifndef PI_CONST
#define PI_CONST 3.14159265358979323846f
#endif

/**
 * ============================================================================
 * MODULO: FuncionesParaDibujarFigurasBasicas
 * ============================================================================
 * Provee herramientas graficas 100% vectoriales basadas en primitivas de OpenGL:
 * GL_LINES, GL_LINE_LOOP, GL_TRIANGLES, GL_QUADS, GL_POLYGON y GL_TRIANGLE_FAN.
 * Cumple con el objetivo academico de Computacion Grafica: sin texturas externas,
 * todo se calcula y rasteriza mediante geometria matematica y color por vertice.
 */

// Dibuja un rectangulo solido o delineado
void dibujarRectangulo(float x, float y, float ancho, float alto,
                       float r, float g, float b, bool relleno = true);

// Dibuja un rectangulo con degradado suave entre dos colores (vertical u horizontal)
void dibujarRectanguloDegradado(float x, float y, float ancho, float alto,
                               float r1, float g1, float b1,
                               float r2, float g2, float b2,
                               bool vertical = true);

// Dibuja un circulo solido o delineado usando aproximacion con GL_TRIANGLE_FAN
void dibujarCirculo(float cx, float cy, float radio, int segmentos,
                    float r, float g, float b, bool relleno = true);

// Dibuja un ovalo / elipse
void dibujarOvalo(float cx, float cy, float radioX, float radioY, int segmentos,
                  float r, float g, float b, bool relleno = true);

// Dibuja una linea con grosor definido
void dibujarLinea(float x1, float y1, float x2, float y2, float grosor,
                  float r, float g, float b);

// Dibuja un poligono convexo arbitrario a partir de coordenadas X e Y
void dibujarPoligono(const float* vx, const float* vy, int cantidadVertices,
                     float r, float g, float b);

// Dibuja una estrella de n puntas (ideal para el efecto de aturdimiento / stun)
void dibujarEstrella(float cx, float cy, float radioExt, float radioInt,
                     int puntas, float anguloRotacion,
                     float r, float g, float b);

// Dibuja una capsula / extremidad redondeada (para brazos y piernas articuladas)
void dibujarCapsula(float x1, float y1, float x2, float y2, float radio,
                    float r, float g, float b);

// Renderizado de texto vectorial / bitmap en pantalla
void dibujarTexto(const char* texto, float x, float y, void* fuente,
                  float r, float g, float b);

void dibujarTextoConSombra(const char* texto, float x, float y, void* fuente,
                           float r, float g, float b);

#endif // FUNCIONES_DIBUJO_FIGURAS_BASICAS_H
