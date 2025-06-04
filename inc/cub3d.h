/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbuitrag <rbuitrag@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 09:17:43 by rbuitrag          #+#    #+#             */
/*   Updated: 2025/05/31 13:54:03 by rbuitrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../inc/libft/libft.h"
# include "../inc/minilibx/mlx.h"
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <unistd.h>
# include <math.h>
# include <string.h>
# include <stdbool.h>
# include <fcntl.h>
# include <errno.h>
# include <X11/keysym.h>
# include <X11/X.h>

    /* --- Constantes --- */
# define WIN_TITLE "Cub3D por yrodrigu & rbuitrag en 42 BCN 2025"
# define MOVE_SPEED 0.1
# define COLLISION_MARGIN 0.1 // Evita quedarse pegado, revisar unidad
# define SUCCESS 1
# define ERROR 0
# define MAP_LINE 2
# define NORTH 0x01
# define SOUTH 0x02
# define WEST  0x04
# define EAST  0x08
# define FLOOR 0x12
# define CEILING 0x25
# define MAX_MAP_HEIGHT 200
# define RES_WINHEIGHT 860
# define RES_WINWIDHT 1024
# define PI 3.14159265359
# define PLANES 0
#ifndef O_DIRECTORY
# define O_DIRECTORY 00200000
#endif

/* COLORS */
# define RESET	"\e[0m"
# define BLACK	"\e[30m"
# define RED	"\e[31m"
# define GREEN	"\e[32m"
# define YELLOW	"\e[33m"
# define BLUE	"\e[34m"
# define PURPLE	"\e[35m"
# define CYAN	"\e[36m"
# define WHITE	"\e[37m"

  /* --- Estructuras --- */
typedef struct s_texture
{
	void    *img_ptr;
	char    *addr;
	int     bits_per_pixel;
	int     line_length;
	int     endian;
	int     width;
	int     height;
	char    *path; // Guardar la ruta original de texturas
} t_texture;

typedef struct s_color
{
	int r;
	int g;
	int b;
	int combined; // Color combinado para mlx (ej: 0xRRGGBB)
	int is_set;   // Flag para saber si ya se parseó
} t_color;

typedef struct s_map
{
	char    **grid;
	int     width;
	int     height;
} t_map;

typedef struct s_player
{
	double  pos_x;
	double  pos_y;
	double	angle;
//	double  dir_x; // Vector de direccion
//	double  dir_y;
//	double  plane_x; // Plano de la cámara (perpendicular a dir) ROTATE tmb raton
//	double  plane_y;
	char    start_direction; // 'N', 'S', 'E', 'W'
	int     found; // Flag para asegurar que solo hay un jugador
	bool	key_up;
	bool	key_down;
	bool	key_right;
	bool	key_left;
	bool	left_rotate;
	bool	right_rotate;
} t_player;

typedef struct s_config
{
	int         win_width;
	int         win_height;
	int         res_set; // Flag para saber si la resolucion se parseo
	t_texture   north_tex;
	t_texture   south_tex;
	t_texture   west_tex;
	t_texture   east_tex;
	t_color     floor_color;
	t_color     ceiling_color;
	t_map       map;
	t_player    player;
	int         elements_found; // Bitmask o contador para elementos obligatorios
} t_config;

typedef struct s_mlx_vars
{
	void        *mlx_ptr;
	void        *win_ptr;
	void        *img_ptr; // Buffer de imagen para dibujar
	char        *addr;    // Direccion del buffer
	int         bits_per_pixel;
	int         line_length;
	int         endian;
	t_config    config; // Contiene toda la configuracion parseada
} t_mlx_vars;

/* INIT*/
void	init_config(t_config *config);
int		init_window_and_image(t_mlx_vars *vars);

/* PARSING*/
int		parser_scene(char **av, t_mlx_vars *vars);
int		parse_scene_file(char *filename, t_config *config);
int		add_map_line(char *line);
int		store_map_line(t_config *config, char *line, int index);
int		is_map_line(char *line);
int		parse_color(char **tokens, t_config *config);
int		parse_texture(char **tokens, t_config *config);

/* VALIDATE*/
void	validate_scene_elements(t_config *config);
void	process_map_data(t_config *config);
void	transfer_config_to_vars(t_config *config, t_mlx_vars *vars);
void	validate_map(t_config *config);
void	validate_map_closed(char **grid, int height, int width);

/* LOADING */
int		load_textures(t_mlx_vars *vars);
void	draw_background(t_mlx_vars *vars);
void	draw_textures_preview(t_mlx_vars *vars);

/* KEYS MLX WINDOWS*/
int		action_key(int keycode, t_mlx_vars *vars);
int		action_mouse(int x, int y, t_mlx_vars *vars);
int		key_release(int key, t_mlx_vars *vars);
int		mouse_move(int x, int y, t_mlx_vars *vars);

/* UTILS*/
void	exit_error(char *message, char *details, t_mlx_vars *vars);
void	free_config(t_config *config);
int		is_config_identifier(char *token);
int		is_empty_line(char *line);
void	free_split(char **tokens);
void	free_textures(t_mlx_vars *vars);

/* MLX UTILS WINDOW*/
int		quit_cub3d(t_mlx_vars *vars);
void	clean_exit(t_mlx_vars *vars, int code);
int		listen_mlx_input(t_mlx_vars *vars);
int		ft_x_close(t_mlx_vars *vars);

/* DRAWING MAP*/
int		drawing_loop(t_mlx_vars *vars);
void	draw_line(t_mlx_vars *vars, double start_x, int i);
void 	clear_image(t_mlx_vars *vars);
bool	ft_make_contact(double px, double py, t_mlx_vars *vars);
void	draw_map(t_mlx_vars *vars);
void	ft_destroy_and_free(t_mlx_vars *vars);
double	distance(double x, double y);
void	draw_square(int x, int y, int size, int color, t_mlx_vars *game);
void 	put_pixel(int x, int y, int color, t_mlx_vars *game);


/*PLAYER AND RAYCASTING*/
void	ft_init_player(t_player *player);
int		ft_key_press(int key_code, t_mlx_vars *vars);
int		ft_key_release(int key_code, t_mlx_vars *vars);
void	ft_move_player(t_player *player, t_mlx_vars *vars);





#endif
