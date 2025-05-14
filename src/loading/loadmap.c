/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loadmap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbuitrag <rbuitrag@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 09:00:08 by rbuitrag          #+#    #+#             */
/*   Updated: 2025/05/09 09:00:08 by rbuitrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

int	load_textures(t_mlx_vars *vars)
{
	vars->config.north_tex.img_ptr = mlx_xpm_file_to_image(vars->mlx_ptr,
		vars->config.north_tex.path, &vars->config.north_tex.width, &vars->config.north_tex.height);
	if (!vars->config.north_tex.img_ptr)
		exit_error("Texture error", "Failed to load north texture", vars);
	vars->config.south_tex.img_ptr = mlx_xpm_file_to_image(vars->mlx_ptr,
		vars->config.south_tex.path, &vars->config.south_tex.width, &vars->config.south_tex.height);
	if (!vars->config.south_tex.img_ptr)
		exit_error("Texture error", "Failed to load south texture", vars);
	vars->config.east_tex.img_ptr = mlx_xpm_file_to_image(vars->mlx_ptr,
		vars->config.east_tex.path, &vars->config.east_tex.width, &vars->config.east_tex.height);
	if (!vars->config.east_tex.img_ptr)
		exit_error("Texture error", "Failed to load east texture", vars);
	vars->config.west_tex.img_ptr = mlx_xpm_file_to_image(vars->mlx_ptr,
		vars->config.west_tex.path, &vars->config.west_tex.width, &vars->config.west_tex.height);
	if (!vars->config.west_tex.img_ptr)
		exit_error("Texture error", "Failed to load west texture", vars);
	return (SUCCESS);
}

void	draw_background(t_mlx_vars *vars)
{
	int		x;
	int		y;
	int		color;
	int		height;

	if (!vars || !vars->img_ptr || !vars->addr)
		return ;
	height = vars->config.win_height;
	y = 0;
	while (y < height)
	{
		x = 0;
		if (y < height / 2)
			color = vars->config.ceiling_color.combined;
		else
			color = vars->config.floor_color.combined;
		while (x < vars->config.win_width)
		{
			*(unsigned int *)(vars->addr + (y * vars->line_length + x * (vars->bits_per_pixel / 8))) = color;
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(vars->mlx_ptr, vars->win_ptr, vars->img_ptr, 0, 0);
}