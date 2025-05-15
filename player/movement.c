/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbuitrag <rbuitrag@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 12:47:18 by rbuitrag          #+#    #+#             */
/*   Updated: 2025/05/13 12:47:18 by rbuitrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

include "../../inc/cub3d.h"

static int	is_valid_move(t_mlx_vars *vars, double new_x, double new_y)
{
    int x;
    int y;

    x = (int)new_x;
    y = (int)new_y;
    if (x < 0 || x >= vars->config.map.width || y < 0
        || y >= vars->config.map.height)
        return (0);
    if (vars->config.map.grid[y][x] == '1')
        return (0);
    return (1);
}
static void	move_player(t_mlx_vars *vars, int direction)
{
    double new_x;
    double new_y;

    new_x = vars->player.pos_x;
    new_y = vars->player.pos_y;
    if (direction == XK_s)
    {
        new_x -= vars->player.dir_x * MOVE_SPEED;
        new_y -= vars->player.dir_y * MOVE_SPEED;
    }
    else if (direction == XK_w)
    {
        new_x += vars->player.dir_x * MOVE_SPEED;
        new_y += vars->player.dir_y * MOVE_SPEED;
    }
    else if (direction == XK_Left)
    {
        new_x -= vars->player.plane_x * MOVE_SPEED;
        new_y -= vars->player.plane_y * MOVE_SPEED;
    }
    else if (direction == XK_Right)
    {
        new_x += vars->player.plane_x * MOVE_SPEED;
        new_y += vars->player.plane_y * MOVE_SPEED;
    }
    if (is_valid_move(vars, new_x, new_y))
    {
        vars->player.pos_x = new_x;
        vars->player.pos_y = new_y;
    }
}
static void	rotate_player(t_mlx_vars *vars, int direction)
{
    double old_dir_x;
    double old_plane_x;
    double rotation_angle;

    rotation_angle = (direction == ROTATE_LEFT) ? -ROTATE_SPEED : ROTATE_SPEED;
    old_dir_x = vars->player.dir_x;
    vars->player.dir_x = vars->player.dir_x * cos(rotation_angle)
        - vars->player.dir_y * sin(rotation_angle);
    vars->player.dir_y = old_dir_x * sin(rotation_angle)
        + vars->player.dir_y * cos(rotation_angle);
    old_plane_x = vars->player.plane_x;
    vars->player.plane_x = vars->player.plane_x * cos(rotation_angle)
        - vars->player.plane_y * sin(rotation_angle);
    vars->player.plane_y = old_plane_x * sin(rotation_angle)
        + vars->player.plane_y * cos(rotation_angle);
}