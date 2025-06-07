/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbuitrag <rbuitrag@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 10:28:15 by rbuitrag          #+#    #+#             */
/*   Updated: 2025/06/07 15:18:50 by rbuitrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void put_pixel(int x, int y, int color, t_mlx_vars *game)
{
    if(x >= RES_WINWIDHT|| y >= RES_WINHEIGHT || x < 0 || y < 0)
        return;
    
    int index = y * game->line_length + x * game->bits_per_pixel / 8;
    game->addr[index] = color & 0xFF;
    game->addr[index + 1] = (color >> 8) & 0xFF;
    game->addr[index + 2] = (color >> 16) & 0xFF;
}

void draw_square(int x, int y, int size, int color, t_mlx_vars *game)
{
    int i = 0;
    while (i < size)
    {
        put_pixel(x + i, y, color, game);
        i++;
    }
    i = 0;
    while (i < size)
    {
        put_pixel(x, y + i, color, game);
        i++;
    }
    i = 0;
    while (i < size)
    {
        put_pixel(x + size, y + i, color, game);
        i++;
    }
    i = 0;
    while (i < size)
    {
        put_pixel(x + i, y + size, color, game);
        i++;
    }
}

double distance(double x, double y){
    return sqrt(x * x + y * y);
}

double fixed_dist(double x1, double y1, double x2, double y2, t_mlx_vars *vars)
{
    double delta_x = x2 - x1;
    double delta_y = y2 - y1;
    double angle = atan2(delta_y, delta_x) - vars->config.player.angle;
    double fix_dist = distance(delta_x, delta_y) * cos(angle);
    return fix_dist;
}


void	ft_destroy_and_free(t_mlx_vars *vars)
{
		mlx_destroy_window(vars->mlx_ptr, vars->win_ptr);
		mlx_destroy_image(vars->mlx_ptr, vars->img_ptr);
		mlx_destroy_display(vars->mlx_ptr);
		free(vars->mlx_ptr);
		exit(0);
}

void	draw_map(t_mlx_vars *vars)
{
	char **map;

	map = vars->config.map.grid;
	for (int y = 0; map[y]; y++)
		for (int x = 0; map[y][x]; x++)
			if (map[y][x] == '1')
				draw_square(x * 64, y * 64, 64, 0xFFAAFF, vars);
}

bool ft_make_contact(double px, double py, t_mlx_vars *vars)
{
    int x = px / 64;
    int y = py / 64;
	if (vars->config.map.grid[y][x] == '1')
        return true;
    return false;
}

void	clear_image(t_mlx_vars *vars)
{
	int	x;
	int	y;

	y = 0;
	while (y < RES_WINHEIGHT)
	{
		x = 0;
		while (x < RES_WINWIDHT)
		{
			if (y < RES_WINHEIGHT / 2)
				put_pixel(x, y, vars->config.ceiling_color.combined, vars);
			else
				put_pixel(x, y, vars->config.floor_color.combined, vars); 
			x++;
		}
		y++;
	}
}

int	get_texture_pixel_color(t_texture *tex, int x, int y)
{
    int	offset;

    if (!tex || !tex->addr)
        return (0);
    if (x < 0 || x >= tex->width || y < 0 || y >= tex->height)
        return (0);
    offset = y * tex->line_length + x * (tex->bits_per_pixel / 8);
    return (*(int *)(tex->addr + offset));
}

static t_texture	*select_texture(t_mlx_vars *vars, int side, double ray_dir_x, double ray_dir_y)
{
    if (side == 0 && ray_dir_x > 0)
        return (&vars->config.east_tex);
    if (side == 0 && ray_dir_x < 0)
        return (&vars->config.west_tex);
    if (side == 1 && ray_dir_y > 0)
        return (&vars->config.south_tex);
    return (&vars->config.north_tex);
}

static int	calc_tex_x(t_texture *tex, int side, double wall_x, double ray_dir_x, double ray_dir_y)
{
    int	tex_x;

    tex_x = (int)(wall_x * (double)tex->width);
    if (side == 0 && ray_dir_x > 0)
        tex_x = tex->width - tex_x - 1;
    if (side == 1 && ray_dir_y < 0)
        tex_x = tex->width - tex_x - 1;
    return (tex_x);
}

static void	draw_texture_column(t_mlx_vars *vars, t_texture *tex, int i,
	int draw_start, int draw_end, int line_height, int tex_x)
{
int	y;
int	d;
int	tex_y;
int	color;

y = draw_start;
while (y < draw_end)
{
	d = y * 32 - RES_WINHEIGHT * 16 + line_height * 16;
	tex_y = ((d * tex->height) / line_height) / 32;
	color = get_texture_pixel_color(tex, tex_x, tex_y);
	put_pixel(i, y, color, vars);
	y++;
}
}
/*
void	draw_line(t_mlx_vars *vars, double start_x, int i)
{
    double	ray_x = vars->config.player.pos_x;
    double	ray_y = vars->config.player.pos_y;
    double	ray_dir_x = cos(start_x);
    double	ray_dir_y = sin(start_x);
    int		map_x, map_y, side;
    double	perp_wall_dist, wall_x;
    t_texture *tex;
    int		tex_x;

    side = 0;
    while (!ft_make_contact(ray_x, ray_y, vars))
    {
        map_x = (int)(ray_x / 64);
        map_y = (int)(ray_y / 64);
        if (map_y < 0 || map_y >= vars->config.map.height || !vars->config.map.grid[map_y])
            break;
        if (map_x < 0 || map_x >= (int)ft_strlen(vars->config.map.grid[map_y]))
            break;
        ray_x += ray_dir_x;
        ray_y += ray_dir_y;
    }
    perp_wall_dist = fixed_dist(vars->config.player.pos_x, vars->config.player.pos_y, ray_x, ray_y, vars);
    tex = select_texture(vars, side, ray_dir_x, ray_dir_y);
    if (side == 0)
        wall_x = vars->config.player.pos_y + perp_wall_dist * ray_dir_y;
    else
        wall_x = vars->config.player.pos_x + perp_wall_dist * ray_dir_x;
    wall_x -= floor(wall_x);
    tex_x = calc_tex_x(tex, side, wall_x, ray_dir_x, ray_dir_y);
    double line_height = (64 / perp_wall_dist) * (RES_WINWIDHT/ 2);
	double draw_start = (RES_WINHEIGHT - line_height) / 2;
	int draw_end = draw_start + line_height;
    draw_texture_column(vars, tex, i, draw_start, draw_end, line_height, tex_x);
}*/

void	draw_line(t_mlx_vars *vars, double start_x, int i)
{
    double	ray_dir_x = cos(start_x);
    double	ray_dir_y = sin(start_x);
    int		map_x = (int)(vars->config.player.pos_x / 64);
    int		map_y = (int)(vars->config.player.pos_y / 64);
    double	side_dist_x, side_dist_y;
    double	delta_dist_x = fabs(1 / ray_dir_x);
    double	delta_dist_y = fabs(1 / ray_dir_y);
    int		step_x, step_y;
    int		hit = 0, side;
    double	perp_wall_dist, wall_x;
    t_texture *tex;
    int		tex_x;

    // Inicialización de step y side_dist
    if (ray_dir_x < 0)
    {
        step_x = -1;
        side_dist_x = (vars->config.player.pos_x / 64 - map_x) * delta_dist_x;
    }
    else
    {
        step_x = 1;
        side_dist_x = (map_x + 1.0 - vars->config.player.pos_x / 64) * delta_dist_x;
    }
    if (ray_dir_y < 0)
    {
        step_y = -1;
        side_dist_y = (vars->config.player.pos_y / 64 - map_y) * delta_dist_y;
    }
    else
    {
        step_y = 1;
        side_dist_y = (map_y + 1.0 - vars->config.player.pos_y / 64) * delta_dist_y;
    }

    // DDA
    while (!hit)
    {
        if (side_dist_x < side_dist_y)
        {
            side_dist_x += delta_dist_x;
            map_x += step_x;
            side = 0;
        }
        else
        {
            side_dist_y += delta_dist_y;
            map_y += step_y;
            side = 1;
        }
        if (map_y < 0 || map_y >= vars->config.map.height || !vars->config.map.grid[map_y])
            break;
        if (map_x < 0 || map_x >= (int)ft_strlen(vars->config.map.grid[map_y]))
            break;
        if (vars->config.map.grid[map_y][map_x] == '1')
            hit = 1;
    }

    /* Calcula perpendicular revisada*/
    if (side == 0)
        perp_wall_dist = ((map_x - vars->config.player.pos_x / 64) + (1 - step_x) / 2) / ray_dir_x;
    else
        perp_wall_dist = ((map_y - vars->config.player.pos_y / 64) + (1 - step_y) / 2) / ray_dir_y;
    tex = select_texture(vars, side, ray_dir_x, ray_dir_y);
    if (side == 0)
        wall_x = vars->config.player.pos_y / 64 + perp_wall_dist * ray_dir_y;
    else
        wall_x = vars->config.player.pos_x / 64 + perp_wall_dist * ray_dir_x;
    wall_x -= floor(wall_x);
    tex_x = calc_tex_x(tex, side, wall_x, ray_dir_x, ray_dir_y);
    int line_height = (int)(RES_WINHEIGHT / (perp_wall_dist + 0.0001));
    int draw_start = -line_height / 2 + RES_WINHEIGHT / 2;
    if (draw_start < 0)
        draw_start = 0;
    int draw_end = line_height / 2 + RES_WINHEIGHT / 2;
    if (draw_end >= RES_WINHEIGHT)
        draw_end = RES_WINHEIGHT - 1;

    draw_texture_column(vars, tex, i, draw_start, draw_end, line_height, tex_x);
}


int	drawing_loop(t_mlx_vars *vars)
{
	t_player *player;

	player = &vars->config.player;
	ft_move_player(player, vars);
	clear_image(vars);
	if (PLANES)
	{
		draw_square(vars->config.player.pos_x, vars->config.player.pos_y, 10, vars->config.floor_color.combined, vars);
		draw_map(vars);
	}
	double	fraction = PI / 3 / RES_WINWIDHT;
	double	start_x = vars->config.player.angle - PI / 6;
	int i = 0;
	while (i < RES_WINWIDHT)
	{
		draw_line(vars, start_x, i);
		start_x += fraction;
		i++;
	}
	mlx_put_image_to_window(vars->mlx_ptr, vars->win_ptr, vars->img_ptr, 0, 0);
	return (0);
}