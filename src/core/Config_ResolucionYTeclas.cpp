#include "core/Config_ResolucionYTeclas.h"
#include <fstream>
#include <iostream>
#include <sstream>

ConfiguracionJuego configGlobal;

// Resoluciones predefinidas disponibles en el menu de opciones
const int resolucionesDisponibles[3][2] = {
    {800, 600},
    {1024, 768},
    {1280, 720}
};

void cargarControlesPorDefecto() {
    configGlobal.anchoPantalla = ANCHO_PANTALLA_BASE;
    configGlobal.altoPantalla = ALTO_PANTALLA_BASE;
    configGlobal.pantallaCompleta = false;
    configGlobal.volumenMusica = 80;
    configGlobal.volumenEfectos = 100;
    configGlobal.indiceResolucion = 0;

    // --- JUGADOR 1 (WASD + Teclas de combate en F, G, H, V) ---
    configGlobal.p1.teclas[MOVER_IZQ]    = 'a';
    configGlobal.p1.esTeclaEspecial[MOVER_IZQ] = false;

    configGlobal.p1.teclas[MOVER_DER]    = 'd';
    configGlobal.p1.esTeclaEspecial[MOVER_DER] = false;

    configGlobal.p1.teclas[SALTAR]       = 'w';
    configGlobal.p1.esTeclaEspecial[SALTAR] = false;

    configGlobal.p1.teclas[AGCHARSE]     = 's';
    configGlobal.p1.esTeclaEspecial[AGCHARSE] = false;

    configGlobal.p1.teclas[GOLPE_SUAVE]  = 'f';
    configGlobal.p1.esTeclaEspecial[GOLPE_SUAVE] = false;

    configGlobal.p1.teclas[GOLPE_FUERTE] = 'g';
    configGlobal.p1.esTeclaEspecial[GOLPE_FUERTE] = false;

    configGlobal.p1.teclas[BLOQUEAR]     = 'h';
    configGlobal.p1.esTeclaEspecial[BLOQUEAR] = false;

    configGlobal.p1.teclas[ESQUIVAR]     = 'v';
    configGlobal.p1.esTeclaEspecial[ESQUIVAR] = false;

    // --- JUGADOR 2 (Flechas direccionales + Teclas J, K, L, N) ---
    configGlobal.p2.teclas[MOVER_IZQ]    = GLUT_KEY_LEFT;
    configGlobal.p2.esTeclaEspecial[MOVER_IZQ] = true;

    configGlobal.p2.teclas[MOVER_DER]    = GLUT_KEY_RIGHT;
    configGlobal.p2.esTeclaEspecial[MOVER_DER] = true;

    configGlobal.p2.teclas[SALTAR]       = GLUT_KEY_UP;
    configGlobal.p2.esTeclaEspecial[SALTAR] = true;

    configGlobal.p2.teclas[AGCHARSE]     = GLUT_KEY_DOWN;
    configGlobal.p2.esTeclaEspecial[AGCHARSE] = true;

    configGlobal.p2.teclas[GOLPE_SUAVE]  = 'j';
    configGlobal.p2.esTeclaEspecial[GOLPE_SUAVE] = false;

    configGlobal.p2.teclas[GOLPE_FUERTE] = 'k';
    configGlobal.p2.esTeclaEspecial[GOLPE_FUERTE] = false;

    configGlobal.p2.teclas[BLOQUEAR]     = 'l';
    configGlobal.p2.esTeclaEspecial[BLOQUEAR] = false;

    configGlobal.p2.teclas[ESQUIVAR]     = 'n';
    configGlobal.p2.esTeclaEspecial[ESQUIVAR] = false;
}

void aplicarResolucion(int indice) {
    if (indice < 0) indice = 0;
    if (indice > 2) indice = 2;
    configGlobal.indiceResolucion = indice;
    configGlobal.anchoPantalla = resolucionesDisponibles[indice][0];
    configGlobal.altoPantalla = resolucionesDisponibles[indice][1];

    if (!configGlobal.pantallaCompleta) {
        glutReshapeWindow(configGlobal.anchoPantalla, configGlobal.altoPantalla);
    }
}

void guardarConfiguracionEnArchivo() {
    std::ofstream archivo("config.txt");
    if (!archivo.is_open()) return;

    archivo << configGlobal.anchoPantalla << " " << configGlobal.altoPantalla << "\n";
    archivo << configGlobal.pantallaCompleta << "\n";
    archivo << configGlobal.volumenMusica << " " << configGlobal.volumenEfectos << "\n";
    archivo << configGlobal.indiceResolucion << "\n";

    // Guardar teclas y marcas especiales de P1
    for (int i = 0; i < TOTAL_ACCIONES; i++) {
        archivo << configGlobal.p1.teclas[i] << " " << (configGlobal.p1.esTeclaEspecial[i] ? 1 : 0) << " ";
    }
    archivo << "\n";

    // Guardar teclas y marcas especiales de P2
    for (int i = 0; i < TOTAL_ACCIONES; i++) {
        archivo << configGlobal.p2.teclas[i] << " " << (configGlobal.p2.esTeclaEspecial[i] ? 1 : 0) << " ";
    }
    archivo << "\n";

    archivo.close();
}

void cargarConfiguracionDesdeArchivo() {
    std::ifstream archivo("config.txt");
    if (!archivo.is_open()) {
        cargarControlesPorDefecto();
        return;
    }

    archivo >> configGlobal.anchoPantalla >> configGlobal.altoPantalla;
    archivo >> configGlobal.pantallaCompleta;
    archivo >> configGlobal.volumenMusica >> configGlobal.volumenEfectos;
    archivo >> configGlobal.indiceResolucion;

    for (int i = 0; i < TOTAL_ACCIONES; i++) {
        int esp = 0;
        archivo >> configGlobal.p1.teclas[i] >> esp;
        configGlobal.p1.esTeclaEspecial[i] = (esp == 1);
    }

    for (int i = 0; i < TOTAL_ACCIONES; i++) {
        int esp = 0;
        archivo >> configGlobal.p2.teclas[i] >> esp;
        configGlobal.p2.esTeclaEspecial[i] = (esp == 1);
    }

    archivo.close();
}

std::string obtenerNombreAccion(int accion) {
    switch (accion) {
        case MOVER_IZQ:    return "Mover Izquierda";
        case MOVER_DER:    return "Mover Derecha";
        case SALTAR:       return "Saltar";
        case AGCHARSE:     return "Agacharse";
        case GOLPE_SUAVE:  return "Golpe Suave";
        case GOLPE_FUERTE: return "Golpe Fuerte";
        case BLOQUEAR:     return "Bloquear (Guardia)";
        case ESQUIVAR:     return "Esquive / Parry";
        default:           return "Desconocida";
    }
}

std::string obtenerNombreTecla(int codigoTecla, bool esEspecial) {
    if (esEspecial) {
        switch (codigoTecla) {
            case GLUT_KEY_LEFT:  return "FLECHA IZQ";
            case GLUT_KEY_RIGHT: return "FLECHA DER";
            case GLUT_KEY_UP:    return "FLECHA ARRIBA";
            case GLUT_KEY_DOWN:  return "FLECHA ABAJO";
            case GLUT_KEY_PAGE_UP: return "REPAG";
            case GLUT_KEY_PAGE_DOWN: return "AVPAG";
            case GLUT_KEY_HOME: return "INICIO";
            case GLUT_KEY_END: return "FIN";
            case GLUT_KEY_INSERT: return "INSERT";
            case GLUT_KEY_F1: return "F1";
            case GLUT_KEY_F2: return "F2";
            case GLUT_KEY_F3: return "F3";
            case GLUT_KEY_F4: return "F4";
            case GLUT_KEY_F5: return "F5";
            default: {
                std::stringstream ss;
                ss << "ESP(" << codigoTecla << ")";
                return ss.str();
            }
        }
    } else {
        if (codigoTecla >= 'a' && codigoTecla <= 'z') {
            std::string s = "";
            s += (char)(codigoTecla - 32); // Convertir a mayuscula para mostrar
            return s;
        } else if (codigoTecla >= 'A' && codigoTecla <= 'Z') {
            std::string s = "";
            s += (char)codigoTecla;
            return s;
        } else if (codigoTecla >= '0' && codigoTecla <= '9') {
            std::string s = "";
            s += (char)codigoTecla;
            return s;
        } else if (codigoTecla == 32) {
            return "ESPACIO";
        } else if (codigoTecla == 13) {
            return "ENTER";
        } else if (codigoTecla == 27) {
            return "ESC";
        } else if (codigoTecla == 9) {
            return "TAB";
        } else {
            std::string s = "'";
            s += (char)codigoTecla;
            s += "'";
            return s;
        }
    }
}
