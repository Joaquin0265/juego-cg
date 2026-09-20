#ifndef VECTORES_Y_MATEMATICAS_2D_H
#define VECTORES_Y_MATEMATICAS_2D_H

#include <cmath>

/**
 * ============================================================================
 * ESTRUCTURA: Vector2D
 * ============================================================================
 * Representa una posición, velocidad o aceleración en el espacio 2D.
 * Utilizado ampliamente en las físicas de los personajes (movimiento, salto,
 * gravedad y empuje de golpes).
 */
struct Vector2D {
    float x;
    float y;

    // Constructores
    Vector2D() : x(0.0f), y(0.0f) {}
    Vector2D(float _x, float _y) : x(_x), y(_y) {}

    // Operadores básicos para operaciones vectoriales
    Vector2D operator+(const Vector2D& otro) const {
        return Vector2D(x + otro.x, y + otro.y);
    }

    Vector2D operator-(const Vector2D& otro) const {
        return Vector2D(x - otro.x, y - otro.y);
    }

    Vector2D operator*(float escalar) const {
        return Vector2D(x * escalar, y * escalar);
    }

    Vector2D& operator+=(const Vector2D& otro) {
        x += otro.x;
        y += otro.y;
        return *this;
    }

    Vector2D& operator*=(float escalar) {
        x *= escalar;
        y *= escalar;
        return *this;
    }

    // Magnitud o longitud del vector
    float longitud() const {
        return std::sqrt(x * x + y * y);
    }

    // Distancia euclidiana entre dos puntos
    float distancia(const Vector2D& otro) const {
        float dx = x - otro.x;
        float dy = y - otro.y;
        return std::sqrt(dx * dx + dy * dy);
    }
};

/**
 * Función auxiliar de Interpolación Lineal (LERP)
 * Permite realizar transiciones suaves entre dos valores (por ejemplo,
 * animaciones de brazos y piernas, o barra de vida retardada).
 */
inline float interpolacionLineal(float inicio, float fin, float t) {
    if (t < 0.0f) t = 0.0f;
    if (t > 1.0f) t = 1.0f;
    return inicio + t * (fin - inicio);
}

/**
 * Constantes matemáticas útiles
 */
#ifndef PI_CONST
#define PI_CONST 3.14159265358979323846f
#endif

#endif // VECTORES_Y_MATEMATICAS_2D_H
