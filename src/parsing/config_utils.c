/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbuitrag <rbuitrag@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 09:16:17 by rbuitrag          #+#    #+#             */
/*   Updated: 2025/06/01 12:28:08 by rbuitrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void init_config(t_config *config)
{
    ft_bzero(config, sizeof(t_config));
    config->win_width = RES_WINWIDHT;
    config->win_height = RES_WINHEIGHT;
    config->res_set = 1;
    config->map.grid = ft_calloc(MAX_MAP_HEIGHT + 1, sizeof(char *));
    if (!config->map.grid)
    	exit_error("Memory error ", "Failed to allocate memory for map grid", NULL);
    config->map.width = 0;
    config->map.height = 0;
}

void	transfer_config_to_vars(t_config *config, t_mlx_vars *vars)
{
	int i;
	
	if (!config || !vars)
		return ;
	ft_bzero(&vars->config, sizeof(t_config));
	vars->config.win_width = config->win_width;
	vars->config.win_height = config->win_height;
	vars->config.res_set = config->res_set;
	vars->config.north_tex.path = ft_strdup(config->north_tex.path);
	vars->config.south_tex.path = ft_strdup(config->south_tex.path);
	vars->config.east_tex.path = ft_strdup(config->east_tex.path);
	vars->config.west_tex.path = ft_strdup(config->west_tex.path);
	if (!vars->config.north_tex.path || !vars->config.south_tex.path
		|| !vars->config.east_tex.path || !vars->config.west_tex.path)
		{
			free_config(config);
			exit_error("Memory allocation error", "transfer_config_to_vars", vars);
		}
	vars->config.floor_color = config->floor_color;
	vars->config.ceiling_color = config->ceiling_color;
	vars->config.map.width = config->map.width;
	vars->config.map.height = config->map.height;
	vars->config.player.start_direction = config->player.start_direction;
	vars->config.player.pos_x = config->player.pos_x * 64 + 32;;
	vars->config.player.pos_y = config->player.pos_y * 64 + 32;;

	vars->config.map.grid = NULL;
	if (config->map.grid)
	{
		vars->config.map.grid = malloc(sizeof(char *) * (config->map.height + 1));
		if (!vars->config.map.grid)
		{
			free_config(config);
			exit_error("Memory allocation error", "map grid", vars);
		}
		i = 0;
		while (i < config->map.height)
		{
			vars->config.map.grid[i] = ft_strdup(config->map.grid[i]);
			if (!vars->config.map.grid[i])
			{
				free_config(config);	
				exit_error("Memory allocation error", "map grid line", vars);
			}
			i++;
		}
		vars->config.map.grid[i] = NULL;
	}
	free_config(config);
}

void	free_config(t_config *config)
{
	int	i;
    
    if (!config)
       return ;
    free(config->north_tex.path);
    free(config->south_tex.path);
    free(config->east_tex.path);
    free(config->west_tex.path);
    config->north_tex.path = NULL;
    config->south_tex.path = NULL;
    config->east_tex.path = NULL;
    config->west_tex.path = NULL;
	/* Si hay mapa do it */
	if (config->map.grid)
    {
		i = 0;
        while (config->map.grid[i])
		{
            free(config->map.grid[i]);
			i++;
		}
		free(config->map.grid);
        config->map.grid = NULL;
    }
}
int	init_window_and_image(t_mlx_vars *vars)
{
	
	if (!vars)
		return (-1);
	vars->mlx_ptr = mlx_init();
	if (!vars->mlx_ptr)
	{
		exit_error("MLX init failed", NULL, vars);
		return (-1);
	}
	vars->win_ptr = mlx_new_window(vars->mlx_ptr,
			vars->config.win_width, vars->config.win_height, WIN_TITLE);
	if (!vars->win_ptr)
	{
		exit_error("Window creation failed", NULL, vars);
		return (-1);
	}
	vars->img_ptr = mlx_new_image(vars->mlx_ptr,
			vars->config.win_width, vars->config.win_height);
	if (!vars->img_ptr)
	{
		exit_error("Image buffer creation failed", NULL, vars);
		return (-1);
	}
	vars->addr = mlx_get_data_addr(vars->img_ptr,
			&vars->bits_per_pixel, &vars->line_length, &vars->endian);
	if (!vars->addr)
	{
		exit_error("Image buffer address failed", NULL, vars);
		return (-1);
	}
	//draw_background(vars);
	//load_textures(vars);
	ft_init_player(&vars->config.player);
	mlx_put_image_to_window(vars->mlx_ptr, vars->win_ptr, vars->img_ptr, 0, 0);
	return (0);
}