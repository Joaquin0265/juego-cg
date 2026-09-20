#include "states/Pantalla_Opciones.h"
#include "graphics/FuncionesParaDibujarFigurasBasicas.h"
#include <GL/freeglut.h>
#include <cstdio>
#include <cmath>

PantallaOpciones::PantallaOpciones() {
    menuActual = 0;
    opcionSeleccionada = 0;
    modoReasignando = false;
    accionAEditar = 0;
    tiempoAnim = 0.0f;
    tiempoMensaje = 0.0f;
}

void PantallaOpciones::inicializar() {
    menuActual = 0;
    opcionSeleccionada = 0;
    modoReasignando = false;
    tiempoAnim = 0.0f;
    tiempoMensaje = 0.0f;
}

void PantallaOpciones::actualizar(float dt) {
    tiempoAnim += dt;
    if (tiempoMensaje > 0.0f) {
        tiempoMensaje -= dt;
        if (tiempoMensaje < 0.0f) tiempoMensaje = 0.0f;
    }
}

void PantallaOpciones::alternarPantallaCompleta() {
    configGlobal.pantallaCompleta = !configGlobal.pantallaCompleta;
    if (configGlobal.pantallaCompleta) {
        glutFullScreen();
    } else {
        glutReshapeWindow(configGlobal.anchoPantalla, configGlobal.altoPantalla);
        glutPositionWindow(100, 100);
    }
    guardarConfiguracionEnArchivo();
}

void PantallaOpciones::cambiarResolucion(int delta) {
    int nuevaRes = configGlobal.indiceResolucion + delta;
    if (nuevaRes < 0) nuevaRes = 2;
    if (nuevaRes > 2) nuevaRes = 0;
    aplicarResolucion(nuevaRes);
    guardarConfiguracionEnArchivo();
}

void PantallaOpciones::cambiarVolumen(bool esMusica, int delta) {
    if (esMusica) {
        configGlobal.volumenMusica += delta;
        if (configGlobal.volumenMusica < 0) configGlobal.volumenMusica = 0;
        if (configGlobal.volumenMusica > 100) configGlobal.volumenMusica = 100;
    } else {
        configGlobal.volumenEfectos += delta;
        if (configGlobal.volumenEfectos < 0) configGlobal.volumenEfectos = 0;
        if (configGlobal.volumenEfectos > 100) configGlobal.volumenEfectos = 100;
    }
    guardarConfiguracionEnArchivo();
}

void PantallaOpciones::manejarTeclas(int codigoTecla, bool esEspecial) {
    // Si estamos en modo de captura de tecla para reasignar
    if (modoReasignando) {
        if (!esEspecial && codigoTecla == 27) { // ESC cancela
            modoReasignando = false;
            mensajeEstado = "REASIGNACION CANCELADA";
            tiempoMensaje = 1.5f;
            return;
        }

        // Asignar tecla al jugador correspondiente
        ControlesJugador& ctrl = (menuActual == 1) ? configGlobal.p1 : configGlobal.p2;
        ctrl.teclas[accionAEditar] = codigoTecla;
        ctrl.esTeclaEspecial[accionAEditar] = esEspecial;

        guardarConfiguracionEnArchivo();
        modoReasignando = false;

        mensajeEstado = "TECLA REASIGNADA CON EXITO";
        tiempoMensaje = 1.8f;
        return;
    }

    // Modo normal: Menu Principal de Opciones (menuActual == 0)
    if (menuActual == 0) {
        const int TOTAL_OPCIONES_MAIN = 8;

        if (esEspecial) {
            if (codigoTecla == GLUT_KEY_UP) {
                opcionSeleccionada = (opcionSeleccionada - 1 + TOTAL_OPCIONES_MAIN) % TOTAL_OPCIONES_MAIN;
            } else if (codigoTecla == GLUT_KEY_DOWN) {
                opcionSeleccionada = (opcionSeleccionada + 1) % TOTAL_OPCIONES_MAIN;
            } else if (codigoTecla == GLUT_KEY_LEFT) {
                if (opcionSeleccionada == 0) cambiarResolucion(-1);
                else if (opcionSeleccionada == 2) cambiarVolumen(true, -10);
                else if (opcionSeleccionada == 3) cambiarVolumen(false, -10);
            } else if (codigoTecla == GLUT_KEY_RIGHT) {
                if (opcionSeleccionada == 0) cambiarResolucion(1);
                else if (opcionSeleccionada == 2) cambiarVolumen(true, 10);
                else if (opcionSeleccionada == 3) cambiarVolumen(false, 10);
            }
        } else {
            if (codigoTecla == 13) { // ENTER
                if (opcionSeleccionada == 0) {
                    cambiarResolucion(1);
                } else if (opcionSeleccionada == 1) {
                    alternarPantallaCompleta();
                } else if (opcionSeleccionada == 2) {
                    cambiarVolumen(true, 10);
                } else if (opcionSeleccionada == 3) {
                    cambiarVolumen(false, 10);
                } else if (opcionSeleccionada == 4) { // Submenú Teclas P1
                    menuActual = 1;
                    opcionSeleccionada = 0;
                } else if (opcionSeleccionada == 5) { // Submenú Teclas P2
                    menuActual = 2;
                    opcionSeleccionada = 0;
                } else if (opcionSeleccionada == 6) { // Restaurar controles
                    cargarControlesPorDefecto();
                    guardarConfiguracionEnArchivo();
                    mensajeEstado = "CONTROLES POR DEFECTO RESTAURADOS";
                    tiempoMensaje = 2.0f;
                } else if (opcionSeleccionada == 7) { // Guardar y regresar
                    guardarConfiguracionEnArchivo();
                }
            }
        }
    }
    // Submenú de Teclas de P1 o P2 (menuActual == 1 o 2)
    else if (menuActual == 1 || menuActual == 2) {
        int totalAcciones = TOTAL_ACCIONES + 1; // +1 para opción "Volver"

        if (esEspecial) {
            if (codigoTecla == GLUT_KEY_UP) {
                opcionSeleccionada = (opcionSeleccionada - 1 + totalAcciones) % totalAcciones;
            } else if (codigoTecla == GLUT_KEY_DOWN) {
                opcionSeleccionada = (opcionSeleccionada + 1) % totalAcciones;
            }
        } else {
            if (codigoTecla == 13) { // ENTER
                if (opcionSeleccionada < TOTAL_ACCIONES) {
                    // Entrar en modo reasignar tecla
                    modoReasignando = true;
                    accionAEditar = opcionSeleccionada;
                } else {
                    // Regresar al menu principal de opciones
                    menuActual = 0;
                    opcionSeleccionada = (menuActual == 1) ? 4 : 5;
                }
            } else if (codigoTecla == 27) { // ESC para volver
                menuActual = 0;
                opcionSeleccionada = 0;
            }
        }
    }
}

void PantallaOpciones::renderizar() {
    // 1. Fondo degradado oscuro
    dibujarRectanguloDegradado(-1.0f, -1.0f, 2.0f, 2.0f,
                              0.05f, 0.06f, 0.12f,
                              0.10f, 0.14f, 0.22f,
                              true);

    // Titulo superior
    if (menuActual == 0) {
        dibujarTextoConSombra("CONFIGURACION GENERAL Y CONTROLES", -0.44f, 0.85f,
                              GLUT_BITMAP_TIMES_ROMAN_24, 1.0f, 0.85f, 0.20f);
    } else if (menuActual == 1) {
        dibujarTextoConSombra("REASIGNAR TECLAS: JUGADOR 1 (WASD)", -0.40f, 0.85f,
                              GLUT_BITMAP_TIMES_ROMAN_24, 0.3f, 0.85f, 1.0f);
    } else {
        dibujarTextoConSombra("REASIGNAR TECLAS: JUGADOR 2 (FLECHAS)", -0.44f, 0.85f,
                              GLUT_BITMAP_TIMES_ROMAN_24, 1.0f, 0.45f, 0.45f);
    }

    // 2. Renderizado del Menu Principal de Opciones
    if (menuActual == 0) {
        char bufOpciones[8][128];

        const char* strRes = (configGlobal.indiceResolucion == 0) ? "800 x 600" :
                             (configGlobal.indiceResolucion == 1) ? "1024 x 768" : "1280 x 720";
        std::snprintf(bufOpciones[0], sizeof(bufOpciones[0]), "RESOLUCION: [ %s ] (Flechas Izq/Der)", strRes);
        std::snprintf(bufOpciones[1], sizeof(bufOpciones[1]), "PANTALLA COMPLETA: [ %s ]", configGlobal.pantallaCompleta ? "SI" : "NO");
        std::snprintf(bufOpciones[2], sizeof(bufOpciones[2]), "VOLUMEN MUSICA: [ %d %% ]", configGlobal.volumenMusica);
        std::snprintf(bufOpciones[3], sizeof(bufOpciones[3]), "VOLUMEN EFECTOS: [ %d %% ]", configGlobal.volumenEfectos);
        std::snprintf(bufOpciones[4], sizeof(bufOpciones[4]), "CONFIGURAR TECLAS JUGADOR 1 ->");
        std::snprintf(bufOpciones[5], sizeof(bufOpciones[5]), "CONFIGURAR TECLAS JUGADOR 2 ->");
        std::snprintf(bufOpciones[6], sizeof(bufOpciones[6]), "RESTAURAR CONTROLES POR DEFECTO");
        std::snprintf(bufOpciones[7], sizeof(bufOpciones[7]), "GUARDAR Y SALIR (o presiona ESC)");

        float yBase = 0.65f;
        float sep = 0.16f;

        for (int i = 0; i < 8; i++) {
            float y = yBase - (float)i * sep * 0.95f;
            bool sel = (opcionSeleccionada == i);

            if (sel) {
                float pulso = 0.006f * std::sin(tiempoAnim * 8.0f);
                dibujarRectangulo(-0.62f - pulso, y - 0.028f, 1.24f + pulso * 2.0f, 0.075f, 0.15f, 0.35f, 0.55f, true);
                dibujarRectangulo(-0.62f - pulso, y - 0.028f, 1.24f + pulso * 2.0f, 0.075f, 0.2f, 1.0f, 0.6f, false);
                dibujarTextoConSombra(">", -0.58f, y, GLUT_BITMAP_HELVETICA_18, 0.2f, 1.0f, 0.6f);
                dibujarTextoConSombra(bufOpciones[i], -0.52f, y, GLUT_BITMAP_HELVETICA_18, 0.2f, 1.0f, 0.6f);
            } else {
                dibujarRectangulo(-0.60f, y - 0.028f, 1.20f, 0.075f, 0.08f, 0.10f, 0.16f, true);
                dibujarRectangulo(-0.60f, y - 0.028f, 1.20f, 0.075f, 0.30f, 0.32f, 0.40f, false);
                dibujarTexto(bufOpciones[i], -0.52f, y, GLUT_BITMAP_HELVETICA_18, 0.8f, 0.8f, 0.85f);
            }
        }
    }
    // 3. Submenú de Edición de Teclas de P1 o P2
    else {
        const ControlesJugador& ctrl = (menuActual == 1) ? configGlobal.p1 : configGlobal.p2;

        float yBase = 0.65f;
        float sep = 0.14f;

        for (int i = 0; i < TOTAL_ACCIONES; i++) {
            float y = yBase - (float)i * sep * 0.95f;
            bool sel = (opcionSeleccionada == i);

            std::string nomAccion = obtenerNombreAccion(i);
            std::string nomTecla  = obtenerNombreTecla(ctrl.teclas[i], ctrl.esTeclaEspecial[i]);

            char linea[128];
            std::snprintf(linea, sizeof(linea), "%-22s :   [ %s ]", nomAccion.c_str(), nomTecla.c_str());

            if (sel) {
                float pulso = 0.006f * std::sin(tiempoAnim * 8.0f);
                dibujarRectangulo(-0.62f - pulso, y - 0.028f, 1.24f + pulso * 2.0f, 0.072f, 0.15f, 0.35f, 0.55f, true);
                dibujarRectangulo(-0.62f - pulso, y - 0.028f, 1.24f + pulso * 2.0f, 0.072f, 0.2f, 1.0f, 0.6f, false);
                dibujarTextoConSombra(">", -0.58f, y, GLUT_BITMAP_HELVETICA_18, 0.2f, 1.0f, 0.6f);
                dibujarTextoConSombra(linea, -0.52f, y, GLUT_BITMAP_HELVETICA_18, 0.2f, 1.0f, 0.6f);
            } else {
                dibujarRectangulo(-0.60f, y - 0.028f, 1.20f, 0.072f, 0.08f, 0.10f, 0.16f, true);
                dibujarRectangulo(-0.60f, y - 0.028f, 1.20f, 0.072f, 0.30f, 0.32f, 0.40f, false);
                dibujarTexto(linea, -0.52f, y, GLUT_BITMAP_HELVETICA_18, 0.8f, 0.8f, 0.85f);
            }
        }

        // Opción "VOLVER AL MENU PRINCIPAL DE OPCIONES"
        float yVolver = yBase - (float)TOTAL_ACCIONES * sep * 0.95f;
        bool selVolver = (opcionSeleccionada == TOTAL_ACCIONES);
        if (selVolver) {
            dibujarRectangulo(-0.62f, yVolver - 0.028f, 1.24f, 0.072f, 0.45f, 0.25f, 0.15f, true);
            dibujarRectangulo(-0.62f, yVolver - 0.028f, 1.24f, 0.072f, 1.0f, 0.6f, 0.2f, false);
            dibujarTextoConSombra(">  <-- VOLVER", -0.58f, yVolver, GLUT_BITMAP_HELVETICA_18, 1.0f, 0.8f, 0.2f);
        } else {
            dibujarRectangulo(-0.60f, yVolver - 0.028f, 1.20f, 0.072f, 0.15f, 0.12f, 0.12f, true);
            dibujarRectangulo(-0.60f, yVolver - 0.028f, 1.20f, 0.072f, 0.4f, 0.3f, 0.3f, false);
            dibujarTexto("   <-- VOLVER", -0.58f, yVolver, GLUT_BITMAP_HELVETICA_18, 0.8f, 0.7f, 0.7f);
        }
    }

    // 4. Modal / Overlay si estamos esperando una tecla para reasignar
    if (modoReasignando) {
        dibujarRectangulo(-0.75f, -0.25f, 1.50f, 0.50f, 0.02f, 0.02f, 0.05f, true);
        dibujarRectangulo(-0.75f, -0.25f, 1.50f, 0.50f, 1.00f, 0.85f, 0.20f, false);

        std::string nomAcc = obtenerNombreAccion(accionAEditar);
        char aviso[128];
        std::snprintf(aviso, sizeof(aviso), "REASIGNANDO: %s", nomAcc.c_str());

        dibujarTextoConSombra(aviso, -0.32f, 0.10f, GLUT_BITMAP_TIMES_ROMAN_24, 1.0f, 0.85f, 0.2f);
        dibujarTextoConSombra("Presiona CUALQUIER TECLA en el teclado para vincularla...",
                              -0.48f, -0.02f, GLUT_BITMAP_HELVETICA_18, 0.2f, 1.0f, 0.8f);
        dibujarTextoConSombra("(Presiona ESC para cancelar)",
                              -0.20f, -0.14f, GLUT_BITMAP_HELVETICA_12, 0.7f, 0.7f, 0.7f);
    }

    // 5. Mensaje de retroalimentacion temporal
    if (tiempoMensaje > 0.0f) {
        dibujarRectangulo(-0.45f, -0.78f, 0.90f, 0.08f, 0.1f, 0.4f, 0.1f, true);
        dibujarRectangulo(-0.45f, -0.78f, 0.90f, 0.08f, 0.3f, 1.0f, 0.3f, false);
        dibujarTextoConSombra(mensajeEstado.c_str(), -0.35f, -0.745f, GLUT_BITMAP_HELVETICA_18, 1.0f, 1.0f, 1.0f);
    }

    // 6. Barra inferior con instrucciones
    dibujarRectangulo(-1.0f, -0.98f, 2.0f, 0.06f, 0.05f, 0.05f, 0.08f, true);
    dibujarTextoConSombra("FLECHAS ARRIBA/ABAJO: Navegar  |  ENTER: Cambiar/Reasignar  |  ESC: Salir al Menu",
                          -0.62f, -0.955f, GLUT_BITMAP_HELVETICA_12, 0.7f, 0.8f, 0.9f);
}
