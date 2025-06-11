/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbuitrag <rbuitrag@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 10:12:16 by yrodrigu          #+#    #+#             */
/*   Updated: 2025/05/31 12:40:51 by rbuitrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void    ft_init_player(t_player *player)
{
    player->pos_x = player->pos_x * 64;
    player->pos_y = player->pos_y * 64;
    if (player->start_direction == 'S')
        player->angle = PI / 2;
    if (player->start_direction == 'W')
        player->angle = PI;
    if (player->start_direction == 'N')
        player->angle = (3 * PI) / 2;
    if (player->start_direction == 'E')
        player->angle = 2 * PI;
    player->dir_x = cos(player->angle);
    player->dir_y = sin(player->angle);
    player->plane_x = -player->dir_y * 0.66;
    player->plane_y = player->dir_x * 0.66;
    player->key_up = false;
    player->key_down = false;
    player->key_right = false;
    player->key_left = false;
    player->left_rotate = false;
    player->right_rotate = false;
}

int ft_key_press(int key_code, t_mlx_vars *vars)
{
    if (key_code == XK_Escape)
        ft_destroy_and_free(vars);
    if (key_code == XK_w)
        vars->config.player.key_up = true;
    if (key_code == XK_s)
        vars->config.player.key_down = true;
    if (key_code == XK_d)
        vars->config.player.key_right = true;
    if (key_code == XK_a)
        vars->config.player.key_left = true;
    if (key_code == XK_Left)
        vars->config.player.left_rotate = true;
    if (key_code == XK_Right)
        vars->config.player.right_rotate = true;
    return (0);
}

int ft_key_release(int key_code, t_mlx_vars *vars)
{
    if (key_code == XK_w)
        vars->config.player.key_up = false;
    if (key_code == XK_s)
        vars->config.player.key_down = false;
    if (key_code == XK_d)
        vars->config.player.key_right = false;
    if (key_code == XK_a)
        vars->config.player.key_left = false;
    if (key_code == XK_Left)
        vars->config.player.left_rotate = false;
    if (key_code == XK_Right)
        vars->config.player.right_rotate = false;
    return (0);
}
/*
int is_wall_at(double x, double y, t_mlx_vars *vars)
{
    double radius = 20.0;
    int tile_x, tile_y;

    tile_x = (int)((x + radius) / 64);
    tile_y = (int)((y + radius) / 64);
    if (vars->config.map.grid[tile_y][tile_x] == '1')
        return 1;

    tile_x = (int)((x - radius) / 64);
    tile_y = (int)((y + radius) / 64);
    if (vars->config.map.grid[tile_y][tile_x] == '1')
        return 1;

    tile_x = (int)((x + radius) / 64);
    tile_y = (int)((y - radius) / 64);
    if (vars->config.map.grid[tile_y][tile_x] == '1')
        return 1;

    tile_x = (int)((x - radius) / 64);
    tile_y = (int)((y - radius) / 64);
    if (vars->config.map.grid[tile_y][tile_x] == '1')
        return 1;

    return 0;
}


void ft_move_player(t_player *player, t_mlx_vars *vars)
{
    (void)vars;
    int speed = 1;
    float angle_speed = 0.03;
    float cos_angle = cos(player->angle);
    float sin_angle = sin(player->angle);

    if (player->left_rotate)
        player->angle -= angle_speed;
    if (player->right_rotate)
        player->angle += angle_speed;
    if (player->angle > 2 * PI)
        player->angle = 0;
    if (player->angle < 0)
        player->angle = 2 * PI;

    if (player->key_up)
    {
        player->pos_x += cos_angle * speed;
        player->pos_y += sin_angle * speed;
    }
    if (player->key_down)
    {
        player->pos_x -= cos_angle * speed;
        player->pos_y -= sin_angle * speed;
    }
    if (player->key_left)
    {
        player->pos_x += sin_angle * speed;
        player->pos_y -= cos_angle * speed;
    }
    if (player->key_right)
    {
        player->pos_x -= sin_angle * speed;
        player->pos_y += cos_angle * speed;
    }
}
*/
#define TILE_SIZE 64
 // To avoid getting stuck too close to walls
/*
void ft_move_player(t_player *player, t_mlx_vars *vars)
{
    int speed = 1;
    float angle_speed = 0.03;
    float cos_angle = cos(player->angle);
    float sin_angle = sin(player->angle);

    if (player->left_rotate)
        player->angle -= angle_speed;
    if (player->right_rotate)
        player->angle += angle_speed;

    if (player->angle > 2 * PI)
        player->angle -= 2 * PI;
    if (player->angle < 0)
        player->angle += 2 * PI;

    float new_x = player->pos_x;
    float new_y = player->pos_y;

    // Movement logic
    if (player->key_up)
    {
        new_x += cos_angle * speed;
        new_y += sin_angle * speed;
    }
    if (player->key_down)
    {
        new_x -= cos_angle * speed;
        new_y -= sin_angle * speed;
    }
    if (player->key_left)
    {
        new_x += sin_angle * speed;
        new_y -= cos_angle * speed;
    }
    if (player->key_right)
    {
        new_x -= sin_angle * speed;
        new_y += cos_angle * speed;
    }

    // Collision check
    int map_x = (int)(new_x / TILE_SIZE);
    int map_y = (int)(new_y / TILE_SIZE);

    if (vars->config.map.grid[map_y][(int)(player->pos_x / TILE_SIZE)] != '1')
        player->pos_y = new_y;
    if (vars->config.map.grid[(int)(player->pos_y / TILE_SIZE)][map_x] != '1')
        player->pos_x = new_x;
}
*/
void ft_move_player(t_player *player, t_mlx_vars *vars)
{
    int speed = 1;
    float angle_speed = 0.03;
    float cos_angle = cos(player->angle);
    float sin_angle = sin(player->angle);

    if (player->left_rotate)
        player->angle -= angle_speed;
    if (player->right_rotate)
        player->angle += angle_speed;

    if (player->angle > 2 * PI)
        player->angle -= 2 * PI;
    if (player->angle < 0)
        player->angle += 2 * PI;

    float new_x = player->pos_x;
    float new_y = player->pos_y;

    if (player->key_up)
    {
        new_x += cos_angle * speed;
        new_y += sin_angle * speed;
    }
    if (player->key_down)
    {
        new_x -= cos_angle * speed;
        new_y -= sin_angle * speed;
    }
    if (player->key_left)
    {
        new_x += sin_angle * speed;
        new_y -= cos_angle * speed;
    }
    if (player->key_right)
    {
        new_x -= sin_angle * speed;
        new_y += cos_angle * speed;
    }

    // Convert to map tile positions with margin
    int map_x = (int)((new_x + 10 * (new_x > player->pos_x ? 1 : -1)) / TILE_SIZE);
    int map_y = (int)((new_y + 10 * (new_y > player->pos_y ? 1 : -1)) / TILE_SIZE);

    int current_map_x = (int)(player->pos_x / TILE_SIZE);
    int current_map_y = (int)(player->pos_y / TILE_SIZE);

    // Check X movement only if no wall in X direction
    if (vars->config.map.grid[current_map_y][map_x] != '1')
        player->pos_x = new_x;

    // Check Y movement only if no wall in Y direction
    if (vars->config.map.grid[map_y][current_map_x] != '1')
        player->pos_y = new_y;
}


/*
void ft_move_player(t_player *player, t_mlx_vars *vars)
{
    int     speed = 1;
    double  angle_speed = 0.01;
    double  cos_angle = cos(player->angle);
    double  sin_angle = sin(player->angle);
    double  next_x, next_y;

    if (player->left_rotate)
        player->angle -= angle_speed;
    if (player->right_rotate)
        player->angle += angle_speed;
    if (player->angle > 2 * PI)
        player->angle = 0;
    if (player->angle < 0)
        player->angle = 2 * PI;

    if (player->key_up)
    {
        next_x = player->pos_x + cos_angle * speed;
        next_y = player->pos_y + sin_angle * speed;
        if (!is_wall_at(next_x, player->pos_y, vars))
            player->pos_x = next_x;
        if (!is_wall_at(player->pos_x, next_y, vars))
            player->pos_y = next_y;
    }

    if (player->key_down)
    {
        next_x = player->pos_x - cos_angle * speed;
        next_y = player->pos_y - sin_angle * speed;
       if (!is_wall_at(next_x, player->pos_y, vars))
            player->pos_x = next_x;
        if (!is_wall_at(player->pos_x, next_y, vars))
            player->pos_y = next_y;
    }

    if (player->key_right)
    {
        next_x = player->pos_x - sin_angle * speed;
        next_y = player->pos_y + cos_angle * speed;
        if (!is_wall_at(next_x, player->pos_y, vars))
            player->pos_x = next_x;
        if (!is_wall_at(player->pos_x, next_y, vars))
            player->pos_y = next_y;
    }

    if (player->key_left)
    {
        next_x = player->pos_x + sin_angle * speed;
        next_y = player->pos_y - cos_angle * speed;
        if (!is_wall_at(next_x, player->pos_y, vars))
            player->pos_x = next_x;
        if (!is_wall_at(player->pos_x, next_y, vars))
            player->pos_y = next_y;
    }
}
*/

int ft_x_close(t_mlx_vars *vars)
{
    ft_destroy_and_free(vars);
    return (0);
}