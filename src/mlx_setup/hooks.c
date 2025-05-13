/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbuitrag <rbuitrag@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 12:41:44 by rbuitrag          #+#    #+#             */
/*   Updated: 2025/05/13 12:41:44 by rbuitrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

include "../../inc/cub3d.h"

static void mouse_move(int x, int y, t_mlx_vars *vars)
{
    if (x < 0 || x > vars->config.win_width || y < 0
        || y > vars->config.win_height)
        return ;
    if (x < vars->config.win_width / 2)
        vars->player.angle -= 0.05;
    else if (x > vars->config.win_width / 2)
        vars->player.angle += 0.05;
    mlx_mouse_move(vars->win_ptr, vars->config.win_width / 2,
        vars->config.win_height / 2);
}

int	action_mouse(int x, int y, t_mlx_vars *vars)
{
    if (x < 0 || x > vars->config.win_width || y < 0
        || y > vars->config.win_height)
        return (0);
    return (mouse_move(x, y, vars));
}
int	action_key(int keycode, t_mlx_vars *vars)
{
    if (keycode == XK_ESC)
    {
        mlx_destroy_window(vars->mlx_ptr, vars->win_ptr);
        exit(0);
    }
    else if (keycode == KEY_W)
        move_player(vars, MOVE_FORWARD);
    else if (keycode == KEY_S)
        move_player(vars, MOVE_BACKWARD);
    else if (keycode == KEY_A)
        move_player(vars, STRAFE_LEFT);
    else if (keycode == KEY_D)
        move_player(vars, STRAFE_RIGHT);
    else if (keycode == KEY_LEFT)
        rotate_player(vars, ROTATE_LEFT);
    else if (keycode == KEY_RIGHT)
        rotate_player(vars, ROTATE_RIGHT);
    return (0);
}