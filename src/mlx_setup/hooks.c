/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbuitrag <rbuitrag@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 12:41:44 by rbuitrag          #+#    #+#             */
/*   Updated: 2025/06/14 12:32:41 by rbuitrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

/*
int mouse_move(int x, int y, t_mlx_vars *vars)
{
    if (!vars)
        return (1);
    if (x < 0 || x > vars->config.win_width
	|| y < 0 || y > vars->config.win_height)
        return (1);
    if (x < vars->config.win_width / 2)
        vars->config.player.plane_x -= 0.05;
    else if (x > vars->config.win_width / 2)
        vars->config.player.plane_y += 0.05;
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
*/

int	action_key(int keycode, t_mlx_vars *vars)
{
	if (!vars || !keycode)
		exit_error("Failed window or keys controls", NULL, vars);
	if (keycode == XK_Escape)
		quit_cub3d(vars);
	return (0);
}
