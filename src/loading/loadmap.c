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

void load_texture(t_texture *tex, void *mlx, char *path)
{
    tex->img_ptr = mlx_xpm_file_to_image(mlx, path, &tex->width, &tex->height);
    if (!tex->img_ptr)
    {
        ft_putstr_fd("Error loading texture: ", 2);
        ft_putstr_fd(path, 2);
        ft_putstr_fd("\n", 2);
        exit(1);
    }
    tex->addr = mlx_get_data_addr(tex->img_ptr,
                                  &tex->bits_per_pixel,
                                  &tex->line_length,
                                  &tex->endian);
    tex->path = path;
}


int	load_textures(t_mlx_vars *vars)
{
	load_texture(&vars->config.north_tex, vars->mlx_ptr, vars->config.north_tex.path);
	load_texture(&vars->config.south_tex, vars->mlx_ptr, vars->config.south_tex.path);
	load_texture(&vars->config.east_tex, vars->mlx_ptr, vars->config.east_tex.path);
	load_texture(&vars->config.west_tex, vars->mlx_ptr, vars->config.west_tex.path);
	return 0;
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