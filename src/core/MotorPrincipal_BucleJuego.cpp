#include "core/MotorPrincipal_BucleJuego.h"
#include "core/Config_ResolucionYTeclas.h"
#include "core/LecturaDeTeclado_P1_P2.h"
#include <GL/freeglut.h>
#include <iostream>

MotorJuego* MotorJuego::instancia = nullptr;

MotorJuego::MotorJuego() {
    instancia = this;
    milisegundosPrevios = 0;
}

MotorJuego& MotorJuego::obtenerInstancia() {
    if (!instancia) {
        instancia = new MotorJuego();
    }
    return *instancia;
}

void MotorJuego::inicializar(int argc, char** argv) {
    // 1. Cargar configuracion persistente desde config.txt si existe
    cargarConfiguracionDesdeArchivo();

    // 2. Inicializar subsistema GLUT
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(configGlobal.anchoPantalla, configGlobal.altoPantalla);
    glutInitWindowPosition(100, 80);
    glutCreateWindow("Proyecto Final - Juego de Peleas 2D (Computacion Grafica)");

    if (configGlobal.pantallaCompleta) {
        glutFullScreen();
    }

    // 3. Inicializar buffer de entrada de teclado
    inicializarTeclado();

    // 4. Inicializar maquina de estados
    administradorPantallas.inicializar();

    // 5. Configurar contexto OpenGL para 2D
    glClearColor(0.05f, 0.05f, 0.08f, 1.0f);
    glDisable(GL_DEPTH_TEST); // Para renderizado 2D directo

    // 6. Registrar callbacks de GLUT
    glutDisplayFunc(callbackRenderizar);
    glutReshapeFunc(callbackRedimensionar);
    glutTimerFunc(1000 / FPS, callbackTemporizador, 0);

    // Callbacks de teclado tanto para presionar como para soltar (soporte multi-tecla)
    glutKeyboardFunc(callbackTeclaNormal);
    glutKeyboardUpFunc(callbackTeclaNormalUp);
    glutSpecialFunc(callbackTeclaEspecial);
    glutSpecialUpFunc(callbackTeclaEspecialUp);

    milisegundosPrevios = glutGet(GLUT_ELAPSED_TIME);
}

void MotorJuego::ejecutar() {
    glutMainLoop();
}

void MotorJuego::callbackRenderizar() {
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

    if (instancia) {
        instancia->administradorPantallas.renderizarActual();
    }

    glutSwapBuffers();
}

void MotorJuego::callbackRedimensionar(int ancho, int alto) {
    if (alto == 0) alto = 1;
    glViewport(0, 0, ancho, alto);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    // Proyeccion ortografica normalizada en rango [-1.0, 1.0] para que la escala sea independiente de la resolucion
    gluOrtho2D(-1.0, 1.0, -1.0, 1.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void MotorJuego::callbackTemporizador(int valor) {
    if (instancia) {
        int tiempoActual = glutGet(GLUT_ELAPSED_TIME);
        float dt = (float)(tiempoActual - instancia->milisegundosPrevios) / 1000.0f;
        instancia->milisegundosPrevios = tiempoActual;

        // Limitar Delta Time para evitar saltos si hay demoras
        if (dt > 0.05f) dt = 0.05f;
        if (dt <= 0.0f) dt = 1.0f / (float)FPS;

        // Actualizar logica del estado actual
        instancia->administradorPantallas.actualizar(dt);

        // Actualizar estados 'just-pressed' del teclado al final del frame
        actualizarTecladoFinDeFrame();

        // Solicitar redibujado de la escena
        glutPostRedisplay();
    }

    glutTimerFunc(1000 / FPS, callbackTemporizador, 0);
}

void MotorJuego::callbackTeclaNormal(unsigned char tecla, int x, int y) {
    teclaNormalPresionada(tecla, x, y);
    if (instancia) {
        instancia->administradorPantallas.manejarTeclas((int)tecla, false);
    }
}

void MotorJuego::callbackTeclaNormalUp(unsigned char tecla, int x, int y) {
    teclaNormalSoltada(tecla, x, y);
}

void MotorJuego::callbackTeclaEspecial(int tecla, int x, int y) {
    teclaEspecialPresionada(tecla, x, y);
    if (instancia) {
        instancia->administradorPantallas.manejarTeclas(tecla, true);
    }
}

void MotorJuego::callbackTeclaEspecialUp(int tecla, int x, int y) {
    teclaEspecialSoltada(tecla, x, y);
}
