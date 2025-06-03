/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   windows.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbuitrag <rbuitrag@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 12:16:02 by rbuitrag          #+#    #+#             */
/*   Updated: 2025/06/03 18:49:03 by rbuitrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"


void	free_textures(t_mlx_vars *vars)
{
    if (vars->config.north_tex.img_ptr)
        mlx_destroy_image(vars->mlx_ptr, vars->config.north_tex.img_ptr);
    if (vars->config.south_tex.img_ptr)
        mlx_destroy_image(vars->mlx_ptr, vars->config.south_tex.img_ptr);
    if (vars->config.east_tex.img_ptr)
        mlx_destroy_image(vars->mlx_ptr, vars->config.east_tex.img_ptr);
    if (vars->config.west_tex.img_ptr)
        mlx_destroy_image(vars->mlx_ptr, vars->config.west_tex.img_ptr);
    vars->config.north_tex.img_ptr = NULL;
    vars->config.south_tex.img_ptr = NULL;
    vars->config.east_tex.img_ptr = NULL;
    vars->config.west_tex.img_ptr = NULL;
}

void clean_exit(t_mlx_vars *vars, int code)
{
	if (!vars || !vars->mlx_ptr || !vars->win_ptr)
		exit_error("Error pointers maps mlx", NULL, vars);
    if (vars->mlx_ptr)
    {
		free_textures(vars);
		if (vars->img_ptr)
			mlx_destroy_image(vars->mlx_ptr, vars->img_ptr);
        vars->img_ptr = NULL;
        if (vars->win_ptr)
			mlx_destroy_window(vars->mlx_ptr, vars->win_ptr);
		mlx_destroy_display(vars->mlx_ptr);
		free(vars->mlx_ptr);
    }
    vars->mlx_ptr = NULL;
	vars->win_ptr = NULL;
    free_config(&vars->config);
	exit(code);
}

int	quit_cub3d(t_mlx_vars *vars)
{
	if (vars)
		clean_exit(vars, 0);
	return (ERROR);
}

void listen_mlx_input(t_mlx_vars *vars)
{
	mlx_hook(vars->win_ptr, KeyPress, KeyPressMask, ft_key_press, vars);
	mlx_hook(vars->win_ptr, KeyRelease, KeyReleaseMask, ft_key_release, vars);
	mlx_hook(vars->win_ptr, DestroyNotify, 0, ft_x_close, vars);
	mlx_loop_hook(vars->mlx_ptr, drawing_loop, vars);
	return (SUCCESS);
}