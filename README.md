# Fighting Game 2D - GLUT / Code::Blocks Edition

¡Bienvenido al repositorio oficial del proyecto! Este es un juego de peleas 2D desarrollado en **C++** utilizando **GLUT / OpenGL** clásico en **Code::Blocks**. 

El objetivo principal del proyecto es construir un juego completo de peleas **generado 100% por código**, sin utilizar sprites, imágenes externas ni pixel art importado. Toda la estética visual (personajes, escenarios, animaciones e interfaz) se genera vectorialmente y mediante primitivas geométricas de OpenGL.

---

## 🛠️ Requisitos e Instalación

1. **Entorno de Desarrollo:** Code::Blocks (versión recomendada con MinGW).
2. **Librerías:** GLUT / FreeGLUT configurado en el proyecto.
3. **Flujo de Trabajo:**
   - Clonar el repositorio.
   - Abrir el archivo de proyecto `.cbp` en Code::Blocks.
   - Asegurarse de que las librerías de OpenGL (`-lopengl32`, `-lglu32`, `-lglut32` o `-lfreeglut`) estén enlazadas en las opciones de compilación.

---

## 📁 Estructura del Proyecto

El código está organizado modularmente para separar la lógica de juego, la matemática, los estados y la renderización visual:

```text
mi_juego_peleas/
│
├── bin/                       # Ejecutables compilados (.exe)
├── obj/                       # Archivos objeto (.o)
├── mi_juego_peleas.cbp        # Proyecto de Code::Blocks
│
└── src/
    ├── main.cpp               # Punto de entrada (main, glutInit, loop principal)
    │
    ├── core/                  # Motor base y utilidades
    │   ├── Game.h / .cpp      # Bucle principal, control de FPS y Delta Time
    │   ├── InputManager.h/.cpp# Captura de teclado (glutKeyboardFunc, glutSpecialFunc)
    │   ├── Vector2D.h         # Estructura de vectores 2D para posiciones y velocidades
    │   └── Constants.h        # Ancho, alto de pantalla, gravedad, colores globales
    │
    ├── states/                # Máquina de estados del juego (State Pattern)
    │   ├── GameState.h        # Clase base/interfaz para los estados
    │   ├── StateManager.h/.cpp# Controla la transición entre estados
    │   ├── MenuState.h / .cpp # Menú principal y selección de modos
    │   ├── PlayState.h / .cpp # Estado de pelea activo
    │   └── ResultState.h/.cpp # Pantalla de victoria / KO
    │
    ├── entities/              # Lógica de juego pura
    │   ├── Fighter.h / .cpp   # Jugador: salud, estados, físicas
    │   ├── Hitbox.h / .cpp    # Cajas de colisión (AABB) para golpes y daño
    │   └── Stage.h / .cpp     # Lógica y límites de la plataforma/mapa
    │
    └── graphics/              # Renderizado 100% vectorial / procedural
        ├── Renderer2D.h/.cpp  # Helpers para dibujar primitivas (rectángulos, círculos, líneas)
        ├── CharacterMesh.h/.cpp# Modelos vectoriales de los personajes por articulación
        ├── StageRenderer.h/.cpp# Dibujo procedural del fondo (cielo, suelo, edificios)
        └── UI.h / .cpp        # Barras de vida, temporizador, texto (glutBitmapCharacter)
```

---

## 📐 Conceptos Clave del Desarrollo

### 1. Personajes Renderizados por Código
Los personajes se construyen como **modelos articulados** usando jerarquías de matrices en OpenGL (`glPushMatrix`, `glPopMatrix`, `glRotatef`, `glTranslatef`). Cada extremidad (brazos, piernas, torso, cabeza) se dibuja mediante primitivas (`GL_QUADS`, `GL_TRIANGLE_FAN`, `GL_LINES`).

### 2. Sistema de Animaciones (Interpolación Lineal)
Para animar los personajes sin sprites:
- Se definen estados de acción: `IDLE`, `WALK`, `JUMP`, `ATTACK_PUNCH`, `BLOCK`, `HIT`.
- Cada estado define los ángulos objetivos para las articulaciones.
- Se aplica interpolación lineal (Lerp) entre frames para lograr movimientos fluidos:
  $$\theta_{\text{actual}} = \theta_{\text{inicio}} + t \cdot (\theta_{\text{destino}} - \theta_{\text{inicio}})$$

### 3. Combate mediante Hitboxes y Hurtboxes (AABB)
El sistema de combate utiliza colisiones de cajas alineadas a los ejes (**AABB**):
- **Hurtbox:** Define el área donde el personaje recibe daño.
- **Hitbox:** Caja ofensiva activa únicamente en los frames de ataque.

### 4. Escenarios Procedurales
Los fondos se dibujan vectorialmente combinando cuadriláteros con degradados de color (`glColor3f`), algoritmos simples para generar montañas o edificios con bucles, y un efecto básico de **Paralaje** para simular profundidad.

---

## 🚀 Roadmap de Tareas / División de Trabajo

Para avanzar de forma organizada, el desarrollo se divide en los siguientes hitos:

- [ ] **Fase 1: Motor Base y Plantilla**
  - Configurar loop de GLUT y control de framerate / Delta Time en `Game`.
  - Crear `InputManager` para manejar teclas del Jugador 1 y Jugador 2.
  - Implementar la base de la máquina de estados (`StateManager` y `GameState`).

- [ ] **Fase 2: Gráficos Primitivos y Rig del Personaje**
  - Implementar funciones auxiliares en `Renderer2D` (dibujar rectángulos, círculos, cápsulas).
  - Diseñar el modelo articular básico del personaje en `CharacterMesh`.
  - Crear la lógica de físicas básicas en `Fighter` (gravedad, salto, movimiento lateral).

- [ ] **Fase 3: Animaciones y Colisiones**
  - Crear el sistema de lerp para transición entre poses (idle, movimiento, ataque).
  - Implementar la clase `Hitbox` con verificación de intersecciones AABB.
  - Conectar el sistema de daño, recepción de golpes (knockback) y reducción de salud.

- [ ] **Fase 4: Escenarios, UI y Pulido**
  - Diseñar 1 o 2 escenarios procedurales con degradados y estructuras geométricas.
  - Dibujar barras de vida dinámicas y temporizador con `UI`.
  - Crear la pantalla de Menú Principal y la pantalla de KO/Victoria.

---

## ⌨️ Controles Provisionales

| Acción | Jugador 1 | Jugador 2 |
| :--- | :---: | :---: |
| Moverse Izquierda / Derecha | `A` / `D` | `Flecha Izq` / `Flecha Der` |
| Saltar | `W` | `Flecha Arriba` |
| Bloquear / Agacharse | `S` | `Flecha Abajo` |
| Ataque / Puñetazo | `F` | `K` |
| Patada | `G` | `L` |

---

¡A programar! Si tienes preguntas sobre algún módulo, revisa la estructura de directorios arriba o abre una discusión/issue en el repositorio.
