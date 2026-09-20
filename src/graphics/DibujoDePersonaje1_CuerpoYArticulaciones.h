#ifndef DIBUJO_PERSONAJE1_H
#define DIBUJO_PERSONAJE1_H

/**
 * ============================================================================
 * MODULO: DibujoDePersonaje1_CuerpoYArticulaciones (LEONARDOX)
 * ============================================================================
 * Modelo grafico vectorial para el personaje "Leonardox":
 * - Estilo: Peleador marcial con cinta roja en la cabeza que ondea, pantalon
 *   oscuro, torso definido y guantinas de combate rojas.
 * - Animacion de Esquive/Parry solicitada:
 *   "que leonardox sea su forma de esquivar levantar un brazo"
 * Todo dibujado exclusivamente con primitivas de OpenGL (lineas y poligonos).
 */

void renderizarLeonardox(float posX, float posY, int direccion,
                        int estado, float tiempoAnim,
                        float salud, float escudo, bool aturdido);

#endif // DIBUJO_PERSONAJE1_H
