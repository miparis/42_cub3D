
🗂 1. Parsing del archivo  >parse - DONE
	- Leer y validar la existencia del archivo.
	- Separar líneas vacías y secciones.
	- Validar que:
	- Estén todos los elementos requeridos (NO, SO, EA, WE, F, C).
	- Los valores de colores estén entre 0 y 255.
	- Las rutas a texturas existan.
	- Extraer el mapa al final del archivo.
	- Validar:
	- Que haya solo 0, 1, (espacio), y N, S, E, W.
	- Que esté cerrado (rodeado de paredes).
	- Una única posición de jugador.

🎨 2. Texturas y recursos gráficos >graphics - DONE
	- Cargar las imágenes con MiniLibX.
	- Asociar texturas según orientación (N/S/E/O).
	- Guardar referencias a texturas en estructura principal.
	- Leer colores para piso y techo.

🧮 3. Motor Raycasting 
	- Implementar DDA para lanzar rayos. - DONE
	- Determinar intersección con muros. - DONE
	- Calcular la distancia de cada rayo.
	- Dibujar columna por columna (perspectiva).
	- Asignar textura a cada lado del muro dependiendo de orientación.
	- Subdivisión:
		- Lógica y matemática del raycasting.
		- Parte visual con MiniLibX (imágenes y dibujo).

🎮 4. Eventos de movimiento y teclado 
	- Movimiento con W, A, S, D. - Falta movimiento porcentual
	- Rotación con flechas. - DONE
	- ESC para cerrar ventana. - DONE
	- Manejo del clic en la cruz roja. -DONE

🖼 5. Inicialización gráfica y renderizado
	- Iniciar MiniLibX. -DONE
	- Crear ventana y bucle principal. -DONE
	- Dibujar cada frame desde el raycasting.

🚨 6. Gestión de errores -DONE (revisar las funciones con MLX)
	- Si falta alguna textura o color, mostrar "Error\n" y mensaje.
	- Si el mapa no está cerrado, o hay múltiples jugadores, error.
	- Manejo de errores en funciones propias (exit_safe, etc.).