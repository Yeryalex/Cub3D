#include "../../inc/cub3d.h"

void    ft_init_player(t_player *player)
{
    player->pos_x = WIDTH / 2;
    player->pos_y = HEIGHT / 2;
    player->angle = PI / 2;
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
        vars->player.key_up = true;
    if (key_code == XK_s)
        vars->player.key_down = true;
    if (key_code == XK_d)
        vars->player.key_right = true;
    if (key_code == XK_a)
        vars->player.key_left = true;
    if (key_code == XK_Left)
        vars->player.left_rotate = true;
    if (key_code == XK_Right)
        vars->player.right_rotate = true;
    return (0);
}

int ft_key_release(int key_code, t_mlx_vars *vars)
{
    if (key_code == XK_w)
        vars->player.key_up = false;
    if (key_code == XK_s)
        vars->player.key_down = false;
    if (key_code == XK_d)
        vars->player.key_right = false;
    if (key_code == XK_a)
        vars->player.key_left = false;
    if (key_code == XK_Left)
        vars->player.left_rotate = false;
    if (key_code == XK_Right)
        vars->player.right_rotate = false;
    return (0);
}

int is_wall_at(double x, double y, t_mlx_vars *vars)
{
    double radius = 3.0;
    int tile_x, tile_y;

    tile_x = (int)((x + radius) / 64);
    tile_y = (int)((y + radius) / 64);
    if (vars->map[tile_y][tile_x] == '1')
        return 1;

    tile_x = (int)((x - radius) / 64);
    tile_y = (int)((y + radius) / 64);
    if (vars->map[tile_y][tile_x] == '1')
        return 1;

    tile_x = (int)((x + radius) / 64);
    tile_y = (int)((y - radius) / 64);
    if (vars->map[tile_y][tile_x] == '1')
        return 1;

    tile_x = (int)((x - radius) / 64);
    tile_y = (int)((y - radius) / 64);
    if (vars->map[tile_y][tile_x] == '1')
        return 1;

    return 0;
}

/*
int is_wall_at(double x, double y, t_mlx_vars *vars)
{
    int map_x = (int)(x / 64);  // 64 is usually 64
    int map_y = (int)(y / 64);

    if (vars->map[map_y][map_x] == '1')  // or whatever you use for walls
        return 1;
    return 0;
}

*/
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
