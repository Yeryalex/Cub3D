/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbuitrag <rbuitrag@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 10:12:16 by yrodrigu          #+#    #+#             */
/*   Updated: 2025/06/12 16:22:15 by yrodrigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	ft_avoid_colision(t_player *player, float *new_x,
		float *new_y, t_mlx_vars *vars)
{
	int	map_x;
	int	map_y;
	int	current_map_x;
	int	current_map_y;
	int	flag;

	if (*new_x > player->pos_x)
		flag = 1;
	else
		flag = -1;
	map_x = (int)((*new_x + 10 * flag) / 64);
	if (*new_y > player->pos_y)
		flag = 1;
	else
		flag = -1;
	map_y = (int)((*new_y + 10 * flag) / 64);
	current_map_x = (int)(player->pos_x / 64);
	current_map_y = (int)(player->pos_y / 64);
	if (vars->config.map.grid[current_map_y][map_x] != '1')
		player->pos_x = *new_x;
	if (vars->config.map.grid[map_y][current_map_x] != '1')
		player->pos_y = *new_y;
}

void	ft_rotation_move(t_player *player)
{
	float	angle_speed;

	angle_speed = 0.03;
	if (player->left_rotate)
		player->angle -= angle_speed;
	if (player->right_rotate)
		player->angle += angle_speed;
	if (player->angle > 2 * PI)
		player->angle -= 2 * PI;
	if (player->angle < 0)
		player->angle += 2 * PI;
}

void	ft_action_move(t_player *player, float *new_x, float *new_y)
{
	float	cos_angle;
	float	sin_angle;

	cos_angle = cos(player->angle);
	sin_angle = sin(player->angle);
	if (player->key_up)
	{
		*new_x += cos_angle * MOVE_SPEED;
		*new_y += sin_angle * MOVE_SPEED;
	}
	if (player->key_down)
	{
		*new_x -= cos_angle * MOVE_SPEED;
		*new_y -= sin_angle * MOVE_SPEED;
	}
	if (player->key_left)
	{
		*new_x += sin_angle * MOVE_SPEED;
		*new_y -= cos_angle * MOVE_SPEED;
	}
	if (player->key_right)
	{
		*new_x -= sin_angle * MOVE_SPEED;
		*new_y += cos_angle * MOVE_SPEED;
	}
}

void	ft_move_player(t_player *player, t_mlx_vars *vars)
{
	float	new_x;
	float	new_y;

	new_x = player->pos_x;
	new_y = player->pos_y;
	ft_rotation_move(player);
	ft_action_move(player, &new_x, &new_y);
	ft_avoid_colision(player, &new_x, &new_y, vars);
}
