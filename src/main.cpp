/**
 * ============================================================================
 * PROYECTO FINAL: JUEGO DE PELEAS 2D (COMPUTACION GRAFICA)
 * ============================================================================
 * Desarrollado en C++ con OpenGL clasico y GLUT / FreeGLUT para Code::Blocks.
 *
 * Caracteristicas academicas y tecnicas:
 * 1. Graficos 100% Vectoriales y Procedurales (GL_QUADS, GL_TRIANGLES, GL_LINES).
 * 2. Plantilla de Jugador (AtributosPersonaje_VidaPosicionEstado) reutilizable.
 * 3. Mecanica de Esquive/Parry: Pose de espera con contraataque inmediato si
 *    el rival ataca, o castigo de inmovilidad si falla.
 *    - Leonardox: Postura de esquive alzando un brazo en alto.
 *    - Guadalupe: Postura de esquive tocandose la mejilla/cara.
 * 4. Bloqueo con medidor de escudo y aturdimiento (Guard Break / Stun).
 * 5. Físicas completas de salto, gravedad, agacharse y colisiones AABB.
 * 6. Dos escenarios (Parque y Universidad) con ruptura y cambio por golpe fuerte.
 * 7. Menu interactivo con reasignacion de teclas para P1 y P2 guardado en config.txt.
 * ============================================================================
 */

#if defined(_WIN32)
#include <windows.h>
#endif

#include "core/MotorPrincipal_BucleJuego.h"

int main(int argc, char** argv) {
    // Obtener la instancia singleton del motor e inicializar
    MotorJuego& motor = MotorJuego::obtenerInstancia();
    motor.inicializar(argc, argv);

    // Iniciar el bucle de eventos de GLUT
    motor.ejecutar();

    return 0;
}
