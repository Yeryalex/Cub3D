/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbuitrag <rbuitrag@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 18:50:11 by rbuitrag          #+#    #+#             */
/*   Updated: 2025/06/12 18:51:42 by rbuitrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

static int	init_mlx_window(t_mlx_vars *vars)
{
	vars->mlx_ptr = mlx_init();
	if (!vars->mlx_ptr)
	{
		exit_error("MLX init failed", NULL, vars);
		return (-1);
	}
	vars->win_ptr = mlx_new_window(vars->mlx_ptr,
			vars->config.win_width, vars->config.win_height, WIN_TITLE);
	return (vars->win_ptr ? 0 : -1);
}

static int	create_mlx_image(t_mlx_vars *vars)
{
	vars->img_ptr = mlx_new_image(vars->mlx_ptr,
			vars->config.win_width, vars->config.win_height);
	if (!vars->img_ptr)
	{
		exit_error("Image creation failed", NULL, vars);
		return (-1);
	}
	vars->addr = mlx_get_data_addr(vars->img_ptr,
			&vars->bits_per_pixel, &vars->line_length, &vars->endian);
	return (vars->addr ? 0 : -1);
}

int	init_window_and_image(t_mlx_vars *vars)
{
	ft_init_player(&vars->config.player);
	if (!vars)
		return (-1);
	if (init_mlx_window(vars) == -1)
		return (-1);
	if (create_mlx_image(vars) == -1)
	{
		mlx_destroy_window(vars->mlx_ptr, vars->win_ptr);
		return (-1);
	}
	mlx_put_image_to_window(vars->mlx_ptr, vars->win_ptr, vars->img_ptr, 0, 0);
	load_textures(vars);
	return (0);
}
