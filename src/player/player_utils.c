/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrodrigu <yrodrigu@student.42barcelo>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 16:18:11 by yrodrigu          #+#    #+#             */
/*   Updated: 2025/06/12 16:22:34 by yrodrigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	ft_init_player(t_player *player)
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
	player->key_up = false;
	player->key_down = false;
	player->key_right = false;
	player->key_left = false;
	player->left_rotate = false;
	player->right_rotate = false;
}

int	ft_key_press(int key_code, t_mlx_vars *vars)
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

int	ft_key_release(int key_code, t_mlx_vars *vars)
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

int	ft_x_close(t_mlx_vars *vars)
{
	ft_destroy_and_free(vars);
	return (0);
}
