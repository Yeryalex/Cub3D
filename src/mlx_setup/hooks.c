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

#include "../../inc/cub3d.h"

int mouse_move(int x, int y, t_mlx_vars *vars)
{
    if (!vars)
        return (1);
    if (x < 0 || x > vars->config.win_width || y < 0 || y > vars->config.win_height)
        return (1);
    if (x < vars->config.win_width / 2)
        vars->config.player.plane_x -= 0.05;
    else if (x > vars->config.win_width / 2)
        vars->config.player.plane_y += 0.05;
        /* Puedo centrar el raton al medio de la ventana, o cuando pulsemos, lanzar los eventos como ejemplo:*/
        //mlx_mouse_move(vars->mlx_ptr, vars->win_ptr, (vars->config.win_width / 2), (vars->config.win_height / 2));
    return (0);
}

int	action_mouse(int x, int y, t_mlx_vars *vars)
{
    if (!vars)
        return (0);
    if (x < 0 || x > vars->config.win_width || y < 0
        || y > vars->config.win_height)
        return (0);
    else
        return (mouse_move(x, y, vars));
}

int	action_key(int keycode, t_mlx_vars *vars)
{
    if (!vars || !keycode)
        exit_error("Failed to initialize window or keys controls", NULL, vars);
    if (keycode == XK_Escape)
        quit_cub3d(vars);
	else if (keycode == XK_Left)
		vars->config.player.plane_x -= 1;
	else if (keycode == XK_Right)
        vars->config.player.plane_x += 1;
	else if (keycode == XK_w || XK_Up)
        vars->config.player.pos_y = 1;
	else if (keycode == XK_s || XK_Down)
        vars->config.player.pos_x = -1;
	else if (keycode == XK_s)
        vars->config.player.pos_y = -1;
	else if (keycode == XK_d)
        vars->config.player.pos_x = 1;
	return (0);
}

int	key_release(int key, t_mlx_vars *vars)
{
	if (key == XK_Escape)
		quit_cub3d(vars);
	if (key == XK_w && vars->config.player.pos_y == 1)
        vars->config.player.pos_y = 0;
	if (key == XK_s && vars->config.player.pos_y == -1)
        vars->config.player.pos_y = 0;
	if (key == XK_a && vars->config.player.pos_x == -1)
        vars->config.player.pos_x += 1;
	if (key == XK_d && vars->config.player.pos_x == 1)
        vars->config.player.pos_x -= 1;
	if (key == XK_Left && vars->config.player.plane_x <= 1)
        vars->config.player.plane_x = 0;
	if (key == XK_Right && vars->config.player.plane_x >= -1)
        vars->config.player.plane_x = 0;
	return (0);
}