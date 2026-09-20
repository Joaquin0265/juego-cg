#ifndef DIBUJO_PERSONAJE2_H
#define DIBUJO_PERSONAJE2_H

/**
 * ============================================================================
 * MODULO: DibujoDePersonaje2_CuerpoYArticulaciones (GUADALUPE)
 * ============================================================================
 * Modelo grafico vectorial para el personaje "Guadalupe":
 * - Estilo: Luchadora agil y elegante, cabello recogido en coleta alta que ondea,
 *   top y guantinas cian/purpura, calzas de combate y zapatillas deportivas.
 * - Animacion de Esquive/Parry solicitada:
 *   "y de guadalipe como tocandose la cara"
 * Todo generado 100% mediante primitivas de OpenGL (Computacion Grafica).
 */

void renderizarGuadalupe(float posX, float posY, int direccion,
                         int estado, float tiempoAnim,
                         float salud, float escudo, bool aturdido);

#endif // DIBUJO_PERSONAJE2_H
