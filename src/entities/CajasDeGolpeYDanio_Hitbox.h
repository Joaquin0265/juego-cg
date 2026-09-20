#ifndef CAJAS_GOLPE_DANIO_HITBOX_H
#define CAJAS_GOLPE_DANIO_HITBOX_H

/**
 * ============================================================================
 * MODULO: CajasDeGolpeYDanio_Hitbox
 * ============================================================================
 * Define las cajas de colision alineadas con los ejes (AABB - Axis-Aligned
 * Bounding Box) para el combate:
 * - Hurtbox: Area vulnerable del cuerpo donde el jugador recibe golpes.
 * - Hitbox: Area ofensiva que se activa en ciertos fotogramas de ataque.
 */

struct RectAABB {
    float x;      // Coordenada X (minima)
    float y;      // Coordenada Y (minima)
    float ancho;  // Ancho de la caja
    float alto;   // Alto de la caja

    RectAABB() : x(0.0f), y(0.0f), ancho(0.0f), alto(0.0f) {}
    RectAABB(float _x, float _y, float _w, float _h)
        : x(_x), y(_y), ancho(_w), alto(_h) {}

    // Verifica si dos rectangulos AABB se superponen
    bool intersecta(const RectAABB& otra) const {
        return (x < otra.x + otra.ancho &&
                x + ancho > otra.x &&
                y < otra.y + otra.alto &&
                y + alto > otra.y);
    }

    float centroX() const { return x + ancho * 0.5f; }
    float centroY() const { return y + alto * 0.5f; }
};

/**
 * Informacion sobre un golpe que genera la Hitbox ofensiva
 */
struct PropiedadesGolpe {
    float danioSalud;      // Danio directo a los puntos de vida
    float danioEscudo;     // Danio al medidor de bloqueo si el rival defiende
    float empujeX;         // Fuerza horizontal de impacto (knockback)
    float empujeY;         // Fuerza vertical (ej. elevar en el aire)
    bool esFuerte;         // Si es un golpe fuerte (capaz de mandar al rival contra el borde y cambiar escenario)
    bool causaAturdimiento;// Si puede aturdir directamente
};

/**
 * Clase Hitbox / Hurtbox
 */
class CajaColision {
public:
    RectAABB caja;
    bool activa;
    PropiedadesGolpe datosGolpe;

    CajaColision();
    void configurar(float x, float y, float w, float h, bool activa = true);

    // Dibuja el contorno de la caja para depuracion visual
    void renderizarDebug(float r, float g, float b) const;
};

#endif // CAJAS_GOLPE_DANIO_HITBOX_H
