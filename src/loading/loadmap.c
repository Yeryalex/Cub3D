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

/* FUNCION PRUEBA PARA VER FUNCIONAMIENTO DE VER TEXTURAS CORRECTAS EN LA VENTANA*/
void	draw_textures_preview(t_mlx_vars *vars)
{
    // Dibuja la textura norte arriba a la izquierda
    if (vars->config.north_tex.img_ptr)
        mlx_put_image_to_window(vars->mlx_ptr, vars->win_ptr,
            vars->config.north_tex.img_ptr, 40, 40);
	// Dibuja la textura sur abajo a la izquierda
    if (vars->config.south_tex.img_ptr)
        mlx_put_image_to_window(vars->mlx_ptr, vars->win_ptr,
            vars->config.south_tex.img_ptr, 40,
            vars->config.win_height - vars->config.south_tex.height - 40);
	// Dibuja la textura este arriba a la derecha
    if (vars->config.east_tex.img_ptr)
        mlx_put_image_to_window(vars->mlx_ptr, vars->win_ptr,
            vars->config.east_tex.img_ptr,
            vars->config.win_width - vars->config.east_tex.width - 40, 40);
	// Dibuja la textura oeste abajo a la derecha
    if (vars->config.west_tex.img_ptr)
        mlx_put_image_to_window(vars->mlx_ptr, vars->win_ptr,
            vars->config.west_tex.img_ptr,
            vars->config.win_width - vars->config.west_tex.width - 40,
            vars->config.win_height - vars->config.west_tex.height - 40);
}

int	load_textures(t_mlx_vars *vars)
{
	int i;
	t_texture *texs[4] = {
        &vars->config.north_tex,
        &vars->config.south_tex,
        &vars->config.east_tex,
        &vars->config.west_tex
    };
    char *paths[4] = {
        vars->config.north_tex.path,
        vars->config.south_tex.path,
        vars->config.east_tex.path,
        vars->config.west_tex.path
    };
	i = 0;
    while (i < 4)
    {
        texs[i]->img_ptr = mlx_xpm_file_to_image(vars->mlx_ptr, paths[i],
            &texs[i]->width, &texs[i]->height);
        if (!texs[i]->img_ptr)
            exit_error("Texture error", "Failed to load texture", vars);
        texs[i]->addr = mlx_get_data_addr(texs[i]->img_ptr,
            &texs[i]->bits_per_pixel, &texs[i]->line_length, &texs[i]->endian);
        i++;
    }
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