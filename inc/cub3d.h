/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbuitrag <rbuitrag@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 09:17:43 by rbuitrag          #+#    #+#             */
/*   Updated: 2025/06/14 14:26:20 by yrodrigu         ###   ########.fr       */
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
# define MOVE_SPEED 1.3
# define COLLISION_MARGIN 10 // Evita quedarse pegado, revisar unidad
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
# define T1 " _  _  ____    ____                      _ \n"
# define T2 " | || ||___ \\  | __ )  __ _ _ __ ___ ___| | ___  _ __   __ _ \n"
# define T3 " | || |_ __) | |  _ \\ / _` | '__/ __/ _ | |/ _ \\| '_ \\ / _ `| "
# define T4 "\n |__   _/ __/  | |_) | (_| | | | (_|  __| | (_) | | | | (_| | \n"
# define T5 "   |_||_____|  |____/ \\__,_|_|  \\___\\___|_|\\___/|_| |_|\\__,_|"
# ifndef O_DIRECTORY
#  define O_DIRECTORY 00200000
# endif
# define RESET	"\e[0m"
# define BLACK	"\e[30m"
# define RED	"\e[31m"
# define GREEN	"\e[32m"
# define YELLOW	"\e[33m"
# define BLUE	"\e[34m"
# define PURPLE	"\e[35m"
# define CYAN	"\e[36m"
# define WHITE	"\e[37m"

typedef struct s_texture
{
	void	*img_ptr;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		width;
	int		height;
	char	*path;
}	t_texture;

typedef struct s_rendering_2d
{
	double	ray_x_planes;
	double	ray_y_planes;
	double	cos_angle;
	double	sin_angle;
}	t_rendering_2d;

typedef struct s_rendering_3d
{
	double		camera_x;
	double		ray_dir_x;
	double		ray_dir_y;
	double		ray_x;
	double		ray_y;
	int			map_x;
	int			map_y;
	double		delta_dist_x;
	double		delta_dist_y;
	double		wall_dist;
	double		proj_plane_dist;
	double		wall_height;
	double		start_y;
	double		end_y;
	double		wall_x;
	double		side_dist_x;
	double		side_dist_y;
	int			step_x;
	int			step_y;
	int			side;
	int			tex_x;
	double		tex_step;
	double		tex_pos;
	t_texture	*tex;
}	t_rendering_3d;

typedef struct s_fill_info
{
	char	**grid;
	int		**visited;
	int		height;
	int		width;
}	t_fill_info;

typedef struct s_color
{
	int	r;
	int	g;
	int	b;
	int	combined;
	int	is_set;
}	t_color;

typedef struct s_map
{
	char	**grid;
	int		width;
	int		height;
}	t_map;

typedef struct s_player
{
	double	pos_x;
	double	pos_y;
	double	angle;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
	char	start_direction;
	int		found;
	bool	key_up;
	bool	key_down;
	bool	key_right;
	bool	key_left;
	bool	left_rotate;
	bool	right_rotate;
}	t_player;

typedef struct s_config
{
	int			win_width;
	int			win_height;
	int			res_set;
	t_texture	north_tex;
	t_texture	south_tex;
	t_texture	west_tex;
	t_texture	east_tex;
	t_color		floor_color;
	t_color		ceiling_color;
	t_map		map;
	t_player	player;
	int			elements_found;
}	t_config;

typedef struct s_mlx_vars
{
	void		*mlx_ptr;
	void		*win_ptr;
	void		*img_ptr;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
	t_config	config;
}	t_mlx_vars;

/* INIT*/
void	init_config(t_config *config);
int		init_window_and_image(t_mlx_vars *vars);

/* PARSING*/
int		parser_scene(char **av, t_mlx_vars *vars);
int		parse_scene_file(char *filename, t_config *config);
int		add_map_line(char *line);
int		store_map_line(t_config *config, char *line, int index);
int		is_map_line(char *line);
int		process_file_lines(t_config *config, int fd);
int		parse_config_line(char **tokens, t_config *config);
int		parse_color(char **tokens, t_config *config);
int		parse_texture(char **tokens, t_config *config);
void	process_map_data(t_config *config);
void	transfer_config_to_vars(t_config *config, t_mlx_vars *vars);

/* VALIDATE*/
void	validate_scene_elements(t_config *config);
void	validate_map(t_config *config);
void	validate_map_closed(char **grid, int height, int width);
void	validate_enclosure(char **grid, int i, int j);
int		validate_map_borders(char **grid, int height, int width);
int		is_valid_map_char(char c);
int		is_valid_cell(t_fill_info *info, int i, int j);

/* LOADING */
int		load_textures(t_mlx_vars *vars);
void	ft_clear_2d(t_mlx_vars *vars);
void	ft_clear_3d(t_mlx_vars *vars);
void	draw_map(t_mlx_vars *vars);
void	draw_square(int x, int y, int size, t_mlx_vars *game);

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
void	free_map_grid(t_config *config);
void	free_texture_paths(t_config *config);
void	free_visited(int **visited, int height);
int		count_tokens(char **tokens);

/* MLX UTILS WINDOW*/
int		quit_cub3d(t_mlx_vars *vars);
void	clean_exit(t_mlx_vars *vars, int code);
int		listen_mlx_input(t_mlx_vars *vars);
int		ft_x_close(t_mlx_vars *vars);

/* DRAWING MAP*/
int		drawing_loop(t_mlx_vars *vars);
void	draw_maze(t_mlx_vars *vars, int i, double start_x);
void	put_pixel(int x, int y, int color, t_mlx_vars *game);
int		get_texel_color(t_texture *tex, int x, int y);

/*UTILS RENDERING*/
void	clear_image(t_mlx_vars *vars);
bool	ft_make_contact(double px, double py, t_mlx_vars *vars);
void	ft_render_2d(t_mlx_vars *vars, double start_x);
void	ft_init_3d_vars(t_rendering_3d *render, t_player *player, int i);
void	ft_ray_direction(t_rendering_3d *render);
void	ft_dda_loop(t_rendering_3d *render, t_mlx_vars *vars);
void	ft_wall_distance(t_rendering_3d *render);
void	ft_distance_for_texture(t_rendering_3d *render);
void	ft_texture_init(t_rendering_3d *render, t_mlx_vars *vars);
void	ft_print_texture(t_rendering_3d *render, int i, t_mlx_vars *vars);
void	ft_axis_player(t_player *player);

/*PLAYER AND RAYCASTING*/
void	ft_init_player(t_player *player);
int		ft_key_press(int key_code, t_mlx_vars *vars);
int		ft_key_release(int key_code, t_mlx_vars *vars);
void	ft_move_player(t_player *player, t_mlx_vars *vars);

#endif
