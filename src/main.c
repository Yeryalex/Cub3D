/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbuitrag <rbuitrag@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 09:48:56 by rbuitrag          #+#    #+#             */
/*   Updated: 2025/05/15 15:14:47 by rbuitrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void put_pixel(int x, int y, int color, t_mlx_vars *game)
{
    if(x >= WIDTH || y >= HEIGHT || x < 0 || y < 0)
        return;
    
    int index = y * game->line_length + x * game->bits_per_pixel / 8;
    game->addr[index] = color & 0xFF;
    game->addr[index + 1] = (color >> 8) & 0xFF;
    game->addr[index + 2] = (color >> 16) & 0xFF;
}

void draw_square(int x, int y, int size, int color, t_mlx_vars *game)
{
    for(int i = 0; i < size; i++)
        put_pixel(x + i, y, color, game);
    for(int i = 0; i < size; i++)
        put_pixel(x, y + i, color, game);
    for(int i = 0; i < size; i++)
        put_pixel(x + size, y + i, color, game);
    for(int i = 0; i < size; i++)
        put_pixel(x + i, y + size, color, game);
}

double distance(double x, double y){
    return sqrt(x * x + y * y);
}

double fixed_dist(double x1, double y1, double x2, double y2, t_mlx_vars *vars)
{
    double delta_x = x2 - x1;
    double delta_y = y2 - y1;
    double angle = atan2(delta_y, delta_x) - vars->player.angle;
    double fix_dist = distance(delta_x, delta_y) * cos(angle);
    return fix_dist;
}

void	ft_free_array(char **map)
{
	int i = 0;
	while (map[i])
	{
		free(map[i]);
		i++;
	}
	free(map);
}

void	ft_destroy_and_free(t_mlx_vars *vars)
{
		mlx_destroy_window(vars->mlx_ptr, vars->win_ptr);
		mlx_destroy_image(vars->mlx_ptr, vars->img_ptr);
		mlx_destroy_display(vars->mlx_ptr);
		free(vars->mlx_ptr);
		exit(0);
}

char **get_map(void)
{
    char **map = malloc(sizeof(char *) * 11);
    map[0] = "111111111111111";
    map[1] = "100000000000001";
    map[2] = "100000000000001";
    map[3] = "100000100000001";
    map[4] = "100000000000001";
    map[5] = "100000010000001";
    map[6] = "100001000000001";
    map[7] = "100000000000001";
    map[8] = "100000000000001";
    map[9] = "111111111111111";
    map[10] = NULL;
    return (map);
}

void	draw_map(t_mlx_vars *vars)
{
	char **map;

	map = vars->map;
	for (int y = 0; map[y]; y++)
		for (int x = 0; map[y][x]; x++)
			if (map[y][x] == '1')
				draw_square(x * 64, y * 64, 64, 0xFFAAFF, vars);
}

bool ft_make_contact(float px, float py, t_mlx_vars *vars)
{
    int x = px / 64;
    int y = py / 64;
    if(vars->map[y][x] == '1')
        return true;
    return false;
}

void	ft_init_windows(t_mlx_vars *vars)
{
	ft_init_player(&vars->player);
	vars->map = get_map();
	vars->mlx_ptr = mlx_init();
	vars->win_ptr = mlx_new_window(vars->mlx_ptr, WIDTH, HEIGHT, WIN_TITLE);
	vars->img_ptr = mlx_new_image(vars->mlx_ptr, WIDTH, HEIGHT);
	vars->addr = mlx_get_data_addr(vars->img_ptr, &vars->bits_per_pixel, &vars->line_length, &vars->endian);
	mlx_put_image_to_window(vars->mlx_ptr, vars->win_ptr, vars->img_ptr, 0, 0);
}

void clear_image(t_mlx_vars *vars)
{
    for(int y = 0; y < HEIGHT; y++)
        for(int x = 0; x < WIDTH; x++)
            put_pixel(x, y, 0, vars);
}

void	draw_line(t_player *player, t_mlx_vars *vars, double start_x, int i)
{
	double	ray_x = player->pos_x;
	double	ray_y = player->pos_y;
	double	cos_angle = cos(start_x);
	double  sin_angle = sin(start_x);

	while (!ft_make_contact(ray_x, ray_y, vars))
	{
		if (PLANES)
			put_pixel(ray_x, ray_y, 0xFF0000, vars);
		ray_x += cos_angle;
		ray_y += sin_angle;
	}
	if (!PLANES)
	{
		double dist = fixed_dist(player->pos_x, player->pos_y, ray_x, ray_y, vars);
		double height = (64 / dist) * (WIDTH / 2);
		double start_y = (HEIGHT - height) / 2;
		int end = start_y + height;
		while (start_y < end)
		{
			put_pixel(i, start_y, 255, vars);
			start_y++;
		}
	}
}


int	drawing_loop(t_mlx_vars *vars)
{
	t_player *player;

	player = &vars->player;
	ft_move_player(player, vars);
	clear_image(vars);
	if (PLANES)
	{
		draw_square(player->pos_x, player->pos_y, 10, 0x00FF00, vars);
		draw_map(vars);
	}
	double	fraction = PI / 3 / WIDTH;
	double	start_x = player->angle - PI / 6;
	int i = 0;
	while (i < WIDTH)
	{
		draw_line(player, vars, start_x, i);
		start_x += fraction;
		i++;
	}
	mlx_put_image_to_window(vars->mlx_ptr, vars->win_ptr, vars->img_ptr, 0, 0);
	return (0);
}

int	main(int argc, char **argv)
{
	t_mlx_vars vars;

	(void)argc, (void)argv;
	
	ft_init_windows(&vars);
	mlx_hook(vars.win_ptr, KeyPress, KeyPressMask, ft_key_press, &vars);
	mlx_hook(vars.win_ptr, KeyRelease, KeyReleaseMask, ft_key_release, &vars);
	mlx_loop_hook(vars.mlx_ptr, drawing_loop, &vars);
	mlx_loop(vars.mlx_ptr);
	return (0);
}