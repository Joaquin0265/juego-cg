#ifndef LECTURA_TECLADO_H
#define LECTURA_TECLADO_H

#include "core/Config_ResolucionYTeclas.h"

/**
 * ============================================================================
 * MODULO: LecturaDeTeclado_P1_P2
 * ============================================================================
 * Administra el estado en tiempo real de las teclas del teclado tanto para
 * caracteres ASCII normales como para teclas especiales de GLUT (flechas, F1..).
 * Permite que ambos jugadores jueguen al mismo tiempo sin que una tecla cancele
 * a la otra (pulsacion multiple simultanea).
 */

// Inicializa los arrays de estado del teclado
void inicializarTeclado();

// Callbacks que se registran en GLUT
void teclaNormalPresionada(unsigned char tecla, int x, int y);
void teclaNormalSoltada(unsigned char tecla, int x, int y);
void teclaEspecialPresionada(int tecla, int x, int y);
void teclaEspecialSoltada(int tecla, int x, int y);

// Se llama al inicio de cada frame para actualizar los estados de disparo unico (just-pressed)
void actualizarTecladoFinDeFrame();

// Consulta de accion para un jugador (jugador: 1 para P1, 2 para P2)
// Retorna true si la tecla correspondiente a la accion esta siendo MANTENIDA
bool estaAccionActiva(int jugador, AccionJuego accion);

// Retorna true solo en el INSTANTE en que la tecla fue presionada (un solo frame)
// Ideal para golpes, salto y esquive/parry
bool fueAccionPresionada(int jugador, AccionJuego accion);

// Estructura para capturar la ultima tecla presionada (util para el menu de reasignacion de teclas)
struct InfoUltimaTecla {
    bool huboPulsacion;
    int codigo;
    bool esEspecial;
};

InfoUltimaTecla obtenerUltimaTeclaPresionada();
void limpiarUltimaTeclaPresionada();

#endif // LECTURA_TECLADO_H
