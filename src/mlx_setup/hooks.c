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

static void	apply_rotation(t_mlx_vars *vars, int delta_x, float rotation_speed)
{
	if (delta_x > 0)
		vars->config.player.angle += delta_x * rotation_speed;
	else if (delta_x < 0)
		vars->config.player.angle -= (-delta_x) * rotation_speed;
	if (vars->config.player.angle > 2 * PI)
		vars->config.player.angle -= 2 * PI;
	if (vars->config.player.angle < 0)
		vars->config.player.angle += 2 * PI;
	ft_axis_player(&vars->config.player);
}

int	mouse_move(int x, int y, t_mlx_vars *vars)
{
	static int	last_x = -1;
	int			delta_x;
	float		rotation_speed;

	if (!vars)
		return (1);
	if (x < 0 || x > vars->config.win_width
		|| y < 0 || y > vars->config.win_height)
		return (1);
	if (last_x == -1)
	{
		last_x = x;
		return (0);
	}
	delta_x = x - last_x;
	rotation_speed = 0.003;
	if (abs(delta_x) > 1)
		apply_rotation(vars, delta_x, rotation_speed);
	last_x = x;
	return (0);
}

int	action_mouse(int x, int y, t_mlx_vars *vars)
{
	if (!vars)
		return (0);
	if (x < 0 || x > vars->config.win_width || y < 0
		|| y > vars->config.win_height)
		return (0);
	return (mouse_move(x, y, vars));
}

int	action_key(int keycode, t_mlx_vars *vars)
{
	if (!vars || !keycode)
		exit_error("Failed window or keys controls", NULL, vars);
	if (keycode == XK_Escape)
		quit_cub3d(vars);
	return (0);
}
