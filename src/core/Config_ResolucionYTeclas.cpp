#include "core/Config_ResolucionYTeclas.h"
#include <fstream>
#include <iostream>

ConfiguracionJuego configGlobal;

void cargarControlesPorDefecto() {
    // --- JUGADOR 1 (Lado Izquierdo: WASD + Teclas de combate en FGVBTY) ---
    configGlobal.p1.teclas[MOVER_IZQ]    = 'a';
    configGlobal.p1.teclas[MOVER_DER]    = 'd';
    configGlobal.p1.teclas[SALTAR]       = 'w';
    configGlobal.p1.teclas[AGCHARSE]     = 's';
    configGlobal.p1.teclas[GOLPE_SUAVE]  = 'f';
    configGlobal.p1.teclas[GOLPE_FUERTE] = 'g';
    configGlobal.p1.teclas[BLOQUEAR]     = 'h';
    configGlobal.p1.teclas[ESQUIVAR]     = 'v';
    configGlobal.p1.teclas[MODO_ULTI]    = 't';

    // --- JUGADOR 2 (Lado Derecho: Flechas + Teclado Numérico o IJKLUO) ---
    // Nota: Para las flechas usamos los códigos de GLUT (ej. GLUT_KEY_LEFT)
    configGlobal.p2.teclas[MOVER_IZQ]    = GLUT_KEY_LEFT;
    configGlobal.p2.teclas[MOVER_DER]    = GLUT_KEY_RIGHT;
    configGlobal.p2.teclas[SALTAR]       = GLUT_KEY_UP;
    configGlobal.p2.teclas[AGCHARSE]     = GLUT_KEY_DOWN;
    configGlobal.p2.teclas[GOLPE_SUAVE]  = 'j';
    configGlobal.p2.teclas[GOLPE_FUERTE] = 'k';
    configGlobal.p2.teclas[BLOQUEAR]     = 'l';
    configGlobal.p2.teclas[ESQUIVAR]     = 'n';
    configGlobal.p2.teclas[MODO_ULTI]    = 'i';
}

// Guarda la configuración actual en un archivo de texto plano
void guardarConfiguracionEnArchivo() {
    std::ofstream archivo("config.txt");
    if (!archivo.is_open()) return;

    archivo << configGlobal.anchoPantalla << " " << configGlobal.altoPantalla << "\n";
    archivo << configGlobal.pantallaCompleta << "\n";
    archivo << configGlobal.volumenMusica << " " << configGlobal.volumenEfectos << "\n";

    for (int i = 0; i < TOTAL_ACCIONES; i++) {
        archivo << configGlobal.p1.teclas[i] << " ";
    }
    archivo << "\n";

    for (int i = 0; i < TOTAL_ACCIONES; i++) {
        archivo << configGlobal.p2.teclas[i] << " ";
    }
    archivo << "\n";

    archivo.close();
}

// Carga la configuración al iniciar el juego
void cargarConfiguracionDesdeArchivo() {
    std::ifstream archivo("config.txt");
    if (!archivo.is_open()) {
        cargarControlesPorDefecto(); // Si no existe el archivo, usar defaults
        return;
    }

    archivo >> configGlobal.anchoPantalla >> configGlobal.altoPantalla;
    archivo >> configGlobal.pantallaCompleta;
    archivo >> configGlobal.volumenMusica >> configGlobal.volumenEfectos;

    for (int i = 0; i < TOTAL_ACCIONES; i++) {
        archivo >> configGlobal.p1.teclas[i];
    }
    for (int i = 0; i < TOTAL_ACCIONES; i++) {
        archivo >> configGlobal.p2.teclas[i];
    }

    archivo.close();
}
