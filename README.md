# Cub3d
Cub3d 42

## Estructura basica de archivos del proyecto

  ```/cub3d
  |-- /srcs             # Código fuente .c
  |   |-- main.c
  |   |-- parsing/
  |   |   |-- parse_scene.c
  |   |   |-- parse_map.c
  |   |   |-- parse_utils.c
  |   |   |-- validation.c
  |   |   |-- validation_utils.c
  |   |-- rendering/
  |   |   |-- raycasting.c
  |   |   |-- textures.c
  |   |   |-- drawing.c
  |   |   |-- floor_ceiling.c # (Opcional, si se hace texturizado)
  |   |-- player/
  |   |   |-- movement.c
  |   |   |-- rotation.c
  |   |-- mlx_setup/
  |   |   |-- window.c
  |   |   |-- hooks.c         # Gestión de eventos (teclado, cierre)
  |   |-- utils/
  |   |   |-- memory.c        # Funciones seguras de malloc/free (opcional)
  |   |   |-- error.c         # Gestión centralizada de errores
  |   |   |-- string_utils.c  # Funciones útiles para strings (split, etc.)
  |   |   |-- math_utils.c    # Funciones matemáticas (grados a radianes, etc.)
  |-- /includes         # Archivos de cabecera .h
  |   |-- cub3d.h         # Cabecera principal con estructuras y prototipos
  |-- /libft            # Tu librería Libft (como submódulo git o copiada)
  |-- /minilibx         # La MiniLibX (compilada o como fuente)
  |-- /maps             # Directorio para guardar los mapas de prueba .cub
  |-- Makefile 
</html></p> 


## Secciones de Desarrollo (Plan de Trabajo):

Sección 0: Fundación y Configuración
****************************************************

Objetivo: Establecer el entorno de desarrollo básico.

Tareas:
Configurar el repositorio git.

Crear la estructura de directorios básica.

Configurar el Makefile inicial (compilar Libft, enlazar MiniLibX, compilar main.c).

Crear includes/cub3d.h con include guards y las estructuras iniciales (pueden estar vacías al principio).

Crear srcs/main.c con la estructura básica main(argc, argv).

Implementar una función centralizada de errores en srcs/utils/error.c (ej. exit_error("Mensaje descriptivo",
optional_details) que limpie memoria si es necesario antes de salir).



Sección 1: Parsing y Validación del Fichero .cub
*****************************************************

Objetivo: Leer el archivo de escena, extraer la información de configuración (resolución, texturas, colores)
y el mapa. Validar rigurosamente todo.

Tareas:
Abrir y leer el archivo .cub línea por línea (usando get_next_line de tu Libft o la versión de 42).

Identificar el tipo de cada línea (R, NO, SO, WE, EA, S, F, C, línea de mapa, vacía, inválida).

Parseo de Elementos:

Resolución (R): Extraer ancho y alto. Validar que sean números positivos.

Texturas (NO, SO, WE, EA, S): Extraer la ruta del archivo. Validar que la ruta no esté vacía.
No cargues la textura aún, solo guarda la ruta.

Colores (F, C): Extraer los valores R,G,B. Validar que estén en el rango [0, 255] y que el formato
sea correcto (ej. "F 100, 150, 200"). Combina el color en un solo int (0xRRGGBB).

Control de Duplicados: Asegúrate de que cada elemento (R, NO, SO, etc.) aparezca exactamente
una vez. Usa flags en tu struct t_config.

Parseo del Mapa: Una vez encontrados todos los elementos anteriores, empieza a leer las líneas
del mapa. Almacénalas temporalmente (ej. en una lista enlazada). Ignora líneas vacías antes del mapa.

Validación del Mapa (¡Crítico!):
Caracteres válidos: Solo '0' (espacio vacío), '1' (muro), '2' (sprite - bonus), ' ' (espacio
fuera del mapa), y exactamente uno de 'N', 'S', 'E', 'W' (posición inicial del jugador).

Mapa Cerrado: El mapa debe estar completamente rodeado por muros ('1') o espacios (' ').
Un '0' o la posición del jugador ('N','S','E','W') nunca deben tocar un espacio o salirse
de los límites del mapa leído. Una buena técnica es usar un algoritmo tipo "flood fill"
partiendo de un espacio exterior para verificar que no se puede llegar a un '0' interior.

No debe haber líneas vacías dentro de la definición del mapa.

Gestión de Errores: Si cualquier validación falla, llama a tu función exit_error con un
mensaje claro indicando qué falló y en qué línea (si es posible). Libera toda la memoria que
hayas reservado hasta ese momento.



Sección 2: Inicialización Gráfica (MiniLibX)
************************************************************

Objetivo: Configurar la ventana y el buffer de imagen donde se dibujará.

Tareas:
mlx_init(): Inicializar la conexión con el servidor gráfico.

mlx_new_window(): Crear la ventana usando las dimensiones parseadas
(config.win_width, config.win_height).

mlx_new_image(): Crear un buffer de imagen del mismo tamaño que la ventana.

mlx_get_data_addr(): Obtener la información del buffer (dirección de memoria,
bpp, line_length, endian) para poder escribir píxeles.

Almacenar los punteros (mlx_ptr, win_ptr, img_ptr, etc.) en la estructura t_mlx_vars.

Gestión de Errores: Comprobar que ninguna de estas funciones devuelva NULL.
Si fallan, llamar a exit_error.



Sección 3: Bucle Principal y Eventos Básicos
*****************************************************

Objetivo: Tener un bucle que se ejecute, pueda cerrarse y eventualmente llame a la función de renderizado.

Tareas:
mlx_loop_hook(): Registrar una función que se llamará repetidamente (el bucle principal de renderizado).

mlx_hook(): Registrar funciones para eventos:
KeyPress: Para detectar pulsaciones de teclas (movimiento, salir).
DestroyNotify (o el evento 17): Para detectar el clic en el botón de cerrar ventana.
mlx_loop(): Iniciar el bucle de eventos de MiniLibX.

Implementar las funciones de hook:
handle_keypress(): Comprobar qué tecla se pulsó (ej. ESC para salir, W/A/S/D para moverse).
Modificar el estado del jugador (sección 4).

handle_destroy(): Llamar a una función de limpieza y exit(0).

render_frame(): La función llamada por mlx_loop_hook. Inicialmente puede solo
pintar el fondo o un píxel. Más adelante llamará al raycasting.


Sección 4: Jugador y Movimiento Básico
**************************************************

Objetivo: Implementar la lógica para mover y rotar al jugador dentro del mapa.

Tareas:
Inicializar la posición (pos_x, pos_y) y dirección (dir_x, dir_y, plane_x, plane_y)
del jugador basándose en el carácter 'N', 'S', 'E', 'W' encontrado durante el parseo del mapa.

N: dir=(-1, 0), plane=(0, 0.66) (0.66 es el FOV típico)
S: dir=(1, 0), plane=(0, -0.66)
E: dir=(0, 1), plane=(0.66, 0)
W: dir=(0, -1), plane=(-0.66, 0)

Implementar funciones de movimiento (en movement.c):
move_forward/backward(): Calcula la nueva posición sumando/restando dir_x/dir_y * move_speed.
strafe_left/right(): Calcula la nueva posición sumando/restando plane_x/plane_y * move_speed.

Detección de Colisiones: Antes de actualizar la posición del jugador, comprueba si
la nueva posición (new_x, new_y) caería dentro de un muro ('1') en el map.grid.
Si hay colisión, no actualices la posición. Considera un pequeño margen para no quedarse atascado.

Implementar funciones de rotación (en rotation.c):
rotate_left/right(): Aplica la matriz de rotación a los vectores dir
y plane usando rot_speed.
new_dir_x = dir_x * cos(a) - dir_y * sin(a)
new_dir_y = dir_x * sin(a) + dir_y * cos(a)
(Lo mismo para plane_x, plane_y)


Sección 5: Raycasting Básico (Paredes sin Textura)
***********************************************************

Objetivo: Dibujar las paredes como líneas verticales de un solo color,
calculando su distancia y altura.

Tareas:

Bucle principal de renderizado (render_frame): Iterar por cada columna vertical
de píxeles de la ventana (de x = 0 a x = win_width - 1).

Para cada x:
Calcular la posición y dirección del rayo:
camera_x = 2 * x / (double)win_width - 1; // Coordenada x en el espacio de la cámara (-1 a 1)
ray_dir_x = player.dir_x + player.plane_x * camera_x;
ray_dir_y = player.dir_y + player.plane_y * camera_x;

Obtener la casilla del mapa donde está el jugador (map_x, map_y).

Calcular delta_dist_x/y: Distancia que el rayo recorre para avanzar una unidad en x o y.
delta_dist = abs(1 / ray_dir) (cuidado con división por cero si ray_dir es 0).

Calcular step_x/y y side_dist_x/y (Algoritmo DDA - Digital Differential Analysis):

Determina en qué dirección avanzar (step = +1 o -1) y la distancia inicial
hasta el primer borde de casilla.

Bucle DDA: Avanza el rayo casilla por casilla (map_x += step_x o map_y += step_y) hasta que golpee un muro (map.grid[map_y][map_x] == '1'). En cada paso, incrementa side_dist por delta_dist y comprueba qué lado (X o Y) se alcanza primero. Guarda qué lado fue golpeado (side).

Calcular la distancia perpendicular al muro (perp_wall_dist) para evitar el efecto
"ojo de pez". Depende de side, pos, ray_dir, step.

Calcular la altura de la línea a dibujar en pantalla:
(line_height = (int)(win_height / perp_wall_dist)).

Calcular los píxeles de inicio y fin para dibujar la línea vertical
 (draw_start = -line_height / 2 + win_height / 2, draw_end = line_height / 2 + win_height / 2).
 Asegúrate de que draw_start y draw_end estén dentro de los límites de la ventana [0, win_height).

Elegir un color para la pared (puede depender del lado side golpeado para diferenciar N/S de E/W).

Dibujar la línea vertical en el buffer de imagen (vars.addr) en la columna x desde draw_start
hasta draw_end con el color elegido. Usa una función my_mlx_pixel_put(vars, x, y, color).


Sección 6: Texturizado de Paredes
***********************************************************

Objetivo: Reemplazar las líneas de color sólido con las texturas correctas.

Tareas:
Seleccionar Textura: Dentro del bucle de raycasting, después de detectar el hit y el side,
y conocer ray_dir_x/y, determina qué textura usar (North, South, East, West).

Calcular wall_x: Determina la coordenada X exacta donde el rayo golpeó la pared.
Esto da el punto horizontal en la textura.

if (side == 0) wall_x = player.pos_y + perp_wall_dist * ray_dir_y;
else wall_x = player.pos_x + perp_wall_dist * ray_dir_x;
wall_x -= floor(wall_x); // Obtener solo la parte fraccionaria (0.0 a 1.0)
Calcular tex_x: Convierte wall_x a la coordenada X de la textura.
tex_x = (int)(wall_x * (double)texture.width);

Ajusta tex_x si la textura debe invertirse (dependiendo de la dirección del rayo y el lado golpeado).
if(side == 0 && ray_dir_x > 0) tex_x = texture.width - tex_x - 1;
if(side == 1 && ray_dir_y < 0) tex_x = texture.width - tex_x - 1;
Bucle de Dibujo Vertical: Modifica el bucle que dibujaba la línea de color sólido.

Para cada píxel y de la línea vertical (desde draw_start hasta draw_end):
Calcula la coordenada Y de la textura (tex_y) correspondiente a ese píxel y de la pantalla.
Esto implica una interpolación basada en y, line_height y texture.height.

d = y * 256 - win_height * 128 + line_height * 128; // 256 y 128 son para evitar floats
tex_y = ((d * texture.height) / line_height) / 256;

Obtén el color del píxel de la textura en (tex_x, tex_y) usando la dirección de memoria de la textura (texture.addr).
color = get_texture_pixel_color(&texture, tex_x, tex_y);
Dibuja ese color en la pantalla en (x, y) usando my_mlx_pixel_put.


Sección 7: Dibujo de Suelo y Techo
******************************************

Objetivo: Rellenar las partes superior e inferior de la pantalla con los colores definidos.

Tareas:
En render_frame, antes del bucle de raycasting (o dentro, dibujando antes y después de la pared):
Dibuja un rectángulo desde y = 0 hasta draw_start (el inicio de la pared) con el color del techo (config.ceiling_color.combined).
Dibuja un rectángulo desde y = draw_end (el final de la pared) hasta win_height - 1 con el color del suelo (config.floor_color.combined).


Sección 8: Sprites (Bonus)
**********************************************

Objetivo: Dibujar objetos 2D (sprites) en el mundo 3D.

Tareas:
Parseo: Identificar posiciones de sprites ('2') en el mapa y almacenar sus coordenadas (x, y) y tipo (si hay diferentes texturas de sprite).

Almacenamiento: Guardar la lista de sprites y sus posiciones.

Carga de Textura: Cargar la textura del sprite (S).

Renderizado (después de las paredes):
Crear un "z-buffer" (double z_buffer[win_width]) y llenarlo con perp_wall_dist para cada columna x durante el raycasting de paredes.
Iterar por cada sprite:
Calcular la posición del sprite relativa al jugador.

Transformar la posición del sprite usando la inversa de la matriz de cámara (inv_det = 1.0 / (plane_x * dir_y - dir_x * plane_y)).
Calcular la posición del sprite en pantalla (sprite_screen_x) y su altura/anchura.

Determinar las columnas de pantalla (draw_start_x, draw_end_x) y filas (draw_start_y, draw_end_y)
donde se dibujará el sprite.
Bucle de Dibujo del Sprite: Iterar por cada columna vertical (stripe) del sprite en pantalla
(desde draw_start_x hasta draw_end_x):
Si la columna stripe está dentro de la pantalla y la distancia transformada del sprite (transform_y)
es positiva (delante del jugador) y menor que la distancia de la pared en esa columna (z_buffer[stripe]):

Calcular la coordenada tex_x de la textura del sprite.

Iterar por cada píxel vertical y del sprite en pantalla:

Calcular tex_y.

Obtener el color de la textura del sprite.
Si el color no es transparente (necesitas manejar transparencia, a menudo un color específico como el rosa 0xFF00FF), dibuja el píxel en (stripe, y) usando my_mlx_pixel_put.
```
## Ray casting
https://www.youtube.com/watch?v=G9i78WoBBIU

### Colision de rayos DDA Algoritmo
https://www.youtube.com/watch?v=NbSee-XM7WA

## Eval controller
https://github.com/mharriso/school21-checklists/blob/master/ng_2_cub3d.pdf 


