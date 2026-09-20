#include "entities/CajasDeGolpeYDanio_Hitbox.h"
#include <GL/freeglut.h>

CajaColision::CajaColision() {
    caja = RectAABB(0.0f, 0.0f, 0.0f, 0.0f);
    activa = false;
    datosGolpe.danioSalud = 10.0f;
    datosGolpe.danioEscudo = 20.0f;
    datosGolpe.empujeX = 0.05f;
    datosGolpe.empujeY = 0.0f;
    datosGolpe.esFuerte = false;
    datosGolpe.causaAturdimiento = false;
}

void CajaColision::configurar(float x, float y, float w, float h, bool _activa) {
    caja.x = x;
    caja.y = y;
    caja.ancho = w;
    caja.alto = h;
    activa = _activa;
}

void CajaColision::renderizarDebug(float r, float g, float b) const {
    if (!activa) return;

    glColor3f(r, g, b);
    glLineWidth(2.0f);
    glBegin(GL_LINE_LOOP);
        glVertex2f(caja.x, caja.y);
        glVertex2f(caja.x + caja.ancho, caja.y);
        glVertex2f(caja.x + caja.ancho, caja.y + caja.alto);
        glVertex2f(caja.x, caja.y + caja.alto);
    glEnd();
    glLineWidth(1.0f);
}
