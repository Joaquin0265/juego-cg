#include "core/LecturaDeTeclado_P1_P2.h"
#include <cstring>
#include <cctype>

// Estados booleanos de cada tecla (256 normales ASCII, 256 especiales GLUT)
static bool teclasNormalesActivas[256];
static bool teclasNormalesPrevias[256];

static bool teclasEspecialesActivas[256];
static bool teclasEspecialesPrevias[256];

static InfoUltimaTecla ultimaTeclaRegistrada = {false, 0, false};

void inicializarTeclado() {
    std::memset(teclasNormalesActivas, 0, sizeof(teclasNormalesActivas));
    std::memset(teclasNormalesPrevias, 0, sizeof(teclasNormalesPrevias));
    std::memset(teclasEspecialesActivas, 0, sizeof(teclasEspecialesActivas));
    std::memset(teclasEspecialesPrevias, 0, sizeof(teclasEspecialesPrevias));
    ultimaTeclaRegistrada.huboPulsacion = false;
}

void teclaNormalPresionada(unsigned char tecla, int x, int y) {
    // Normalizar a minusculas para evitar conflictos de Bloq Mayus en letras
    unsigned char t = tecla;
    if (t >= 'A' && t <= 'Z') {
        t = std::tolower(t);
    }
    teclasNormalesActivas[t] = true;

    ultimaTeclaRegistrada.huboPulsacion = true;
    ultimaTeclaRegistrada.codigo = t;
    ultimaTeclaRegistrada.esEspecial = false;
}

void teclaNormalSoltada(unsigned char tecla, int x, int y) {
    unsigned char t = tecla;
    if (t >= 'A' && t <= 'Z') {
        t = std::tolower(t);
    }
    teclasNormalesActivas[t] = false;
}

void teclaEspecialPresionada(int tecla, int x, int y) {
    if (tecla >= 0 && tecla < 256) {
        teclasEspecialesActivas[tecla] = true;

        ultimaTeclaRegistrada.huboPulsacion = true;
        ultimaTeclaRegistrada.codigo = tecla;
        ultimaTeclaRegistrada.esEspecial = true;
    }
}

void teclaEspecialSoltada(int tecla, int x, int y) {
    if (tecla >= 0 && tecla < 256) {
        teclasEspecialesActivas[tecla] = false;
    }
}

void actualizarTecladoFinDeFrame() {
    std::memcpy(teclasNormalesPrevias, teclasNormalesActivas, sizeof(teclasNormalesActivas));
    std::memcpy(teclasEspecialesPrevias, teclasEspecialesActivas, sizeof(teclasEspecialesActivas));
}

bool estaAccionActiva(int jugador, AccionJuego accion) {
    if (accion < 0 || accion >= TOTAL_ACCIONES) return false;

    const ControlesJugador& ctrl = (jugador == 1) ? configGlobal.p1 : configGlobal.p2;
    int codigo = ctrl.teclas[accion];
    bool esEsp = ctrl.esTeclaEspecial[accion];

    if (esEsp) {
        if (codigo >= 0 && codigo < 256) {
            return teclasEspecialesActivas[codigo];
        }
    } else {
        if (codigo >= 0 && codigo < 256) {
            return teclasNormalesActivas[codigo];
        }
    }
    return false;
}

bool fueAccionPresionada(int jugador, AccionJuego accion) {
    if (accion < 0 || accion >= TOTAL_ACCIONES) return false;

    const ControlesJugador& ctrl = (jugador == 1) ? configGlobal.p1 : configGlobal.p2;
    int codigo = ctrl.teclas[accion];
    bool esEsp = ctrl.esTeclaEspecial[accion];

    if (esEsp) {
        if (codigo >= 0 && codigo < 256) {
            return (teclasEspecialesActivas[codigo] && !teclasEspecialesPrevias[codigo]);
        }
    } else {
        if (codigo >= 0 && codigo < 256) {
            return (teclasNormalesActivas[codigo] && !teclasNormalesPrevias[codigo]);
        }
    }
    return false;
}

InfoUltimaTecla obtenerUltimaTeclaPresionada() {
    return ultimaTeclaRegistrada;
}

void limpiarUltimaTeclaPresionada() {
    ultimaTeclaRegistrada.huboPulsacion = false;
}
