
# 🚀 Cub3D: Un Motor de Juego 3D al Estilo Wolfenstein 3D

Este proyecto implementa un motor de juego básico en 3D utilizando la librería MiniLibX, inspirado en el clásico Wolfenstein 3D. El objetivo es renderizar un entorno 3D a partir de un mapa 2D, permitiendo al jugador explorar un laberinto con texturas y colores.

---

## 🗂 1. Parsing del Archivo de Configuración y Mapa (Parse) - DONE

Esta fase se encarga de leer, validar y estructurar toda la información necesaria del archivo `.cub` proporcionado.

* **1.1. Validación del archivo:**
    * Leer y validar la existencia y extensión (`.cub`) del archivo.
    * Separar líneas vacías y las distintas secciones (configuración y mapa).

* **1.2. Configuración del juego:**
    * Validar que estén presentes todos los elementos de configuración requeridos: `NO` (textura Norte), `SO` (textura Sur), `EA` (textura Este), `WE` (textura Oeste), `F` (color de piso), `C` (color de techo).
    * Validar que los valores de los colores (`F` y `C`) estén en el rango correcto (0-255) para cada componente RGB.
    * Validar que las rutas a las texturas (`NO`, `SO`, `EA`, `WE`) existan y sean accesibles.

* **1.3. Extracción y validación del mapa:**
    * Extraer la cuadrícula del mapa que se encuentra al final del archivo.
    * Validar los caracteres del mapa: solo se permiten `0` (espacio vacío), `1` (pared), ` ` (espacio), y `N`, `S`, `E`, `W` (posición inicial del jugador).
    * Validar que el mapa esté completamente cerrado (rodeado de paredes) para evitar salirse del entorno.
    * Asegurarse de que haya una única posición inicial para el jugador (`N`, `S`, `E`, `W`).

---

## 🎨 2. Texturas y Recursos Gráficos (Graphics) - DONE

Gestión de la carga y asociación de todos los elementos visuales del juego.

* **2.1. Carga de texturas:**
    * Cargar las imágenes (archivos `.xpm`) de las texturas de los muros (`NO`, `SO`, `EA`, `WE`) utilizando las funciones de MiniLibX (`mlx_xpm_file_to_image`).
    * Guardar las referencias a estas texturas cargadas en la estructura de datos principal del programa (`t_data` o `t_textures`).

* **2.2. Colores de piso y techo:**
    * Leer y almacenar los valores de color para el piso y el techo, ya parseados, para su posterior renderizado.

---

## 🧮 3. Motor de Raycasting

Implementación del algoritmo de raycasting para proyectar la vista 3D del jugador.

* **3.1. Lógica y matemática del raycasting:**
    * Calcular la dirección de cada rayo lanzado desde la posición del jugador a través del campo de visión.
    * Implementar el algoritmo **DDA (Digital Differential Analyzer)** para determinar la intersección de cada rayo con los muros en el mapa. - DONE
    * Determinar con precisión las coordenadas de intersección del rayo con los muros. - DONE
    * Calcular la distancia perpendicular (fisheye correction) desde el jugador hasta el punto de impacto del rayo con el muro.
    * Calcular la altura de la porción del muro a dibujar en la pantalla en función de la distancia.

* **3.2. Parte visual y renderizado con MiniLibX:**
    * Dibujar cada columna vertical de la pantalla, que representa una "rebanada" del muro visible.
    * Asignar la textura correcta a cada lado del muro (Norte, Sur, Este, Oeste) según la orientación de la colisión del rayo.
    * Aplicar la textura a la columna, calculando qué parte de la textura debe dibujarse en cada píxel vertical.
    * Dibujar el piso y el techo con sus respectivos colores sólidos.

---

## 🎮 4. Eventos de Movimiento y Teclado

Manejo de la interacción del jugador con el entorno.

* **4.1. Movimiento del jugador:**
    * Implementar el movimiento hacia adelante (`W`), atrás (`S`), izquierda (`A`) y derecha (`D`) dentro del laberinto. - *Falta implementar el movimiento porcentual (suave).*
    * Asegurar que el jugador no pueda atravesar los muros.

* **4.2. Rotación de la vista:**
    * Implementar la rotación del punto de vista del jugador usando las flechas izquierda y derecha del teclado. - DONE

* **4.3. Control de la aplicación:**
    * Manejar el evento de presionar la tecla `ESC` para cerrar la ventana y salir del programa de forma limpia. - DONE
    * Manejar el evento de clic en el botón de cerrar la ventana (la cruz roja) para salir del programa de forma segura. - DONE

---

## 🖼 5. Inicialización Gráfica y Renderizado

Configuración inicial de MiniLibX y el bucle principal de renderizado.

* **5.1. Configuración de MiniLibX:**
    * Inicializar la librería MiniLibX (`mlx_init()`). - DONE
    * Crear la ventana de visualización del juego (`mlx_new_window()`). - DONE

* **5.2. Bucle principal y renderizado:**
    * Configurar el bucle principal de eventos de MiniLibX (`mlx_loop()`).
    * En cada iteración del bucle, redibujar la escena completa utilizando la lógica del motor de raycasting (`mlx_loop_hook`). Esto asegura que cada frame se renderice correctamente, creando la ilusión de movimiento.

---

## 🚨 6. Gestión de Errores - DONE (revisar las funciones con MLX)

Implementación de un robusto sistema de manejo de errores para una experiencia de usuario clara.

* **6.1. Errores de configuración:**
    * Mostrar un mensaje de "Error\n" seguido de un mensaje descriptivo si faltan elementos de textura o colores en el archivo de configuración.
    * Manejar errores relacionados con rutas de texturas inválidas o archivos XPM corruptos.

* **6.2. Errores de mapa:**
    * Mostrar un mensaje de "Error\n" si el mapa no está correctamente cerrado.
    * Indicar un error si se detecta más de una posición inicial para el jugador o caracteres inválidos en el mapa.

* **6.3. Funciones de liberación segura:**
    * Implementar funciones de liberación de memoria seguras (`free_all`, `free_args`, `free_config`, `free_flags`) para evitar fugas de memoria, especialmente en caso de errores durante la inicialización.
    * Revisar el manejo de errores en las funciones relacionadas con MiniLibX para liberar adecuadamente los recursos si `mlx_init`, `mlx_new_window`, o `mlx_xpm_file_to_image` fallan.