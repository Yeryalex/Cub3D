/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrodrigu <yrodrigu@student.42barcelo>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 13:47:14 by yrodrigu          #+#    #+#             */
/*   Updated: 2025/05/25 13:48:04 by yrodrigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	print_controls(void)
{
	printf(RED "\n");
	printf("░█▀▀░█░█░█▀▄░▀▀█░█▀▄░░░█▀▀░█▀█░█▀█░▀█▀░█▀▄░█▀█░█░░░█▀▀\n");
	printf("░█░░░█░█░█▀▄░░▀▄░█░█░░░█░░░█░█░█░█░░█░░█▀▄░█░█░█░░░▀▀█\n");
	printf("░▀▀▀░▀▀▀░▀▀░░▀▀░░▀▀░░░░▀▀▀░▀▀▀░▀░▀░░▀░░▀░▀░▀▀▀░▀▀▀░▀▀▀\n");
	printf(RESET "\n");
	printf(CYAN "\tW" RESET ": move forward\t");
	printf(CYAN "\tS" RESET ": move backward\n");
	printf(CYAN "\tA" RESET ": strafe left\t");
	printf(CYAN "\tD" RESET ": strafe right\n");
	printf(CYAN "\t<" RESET ": rotate left\t");
	printf(CYAN "\t>" RESET ": rotate right\n");
	printf(CYAN "\t FREE GAME NOW, yrodrigu & rbuitrag 2025\n");
	printf(GREEN "\n");
    printf(" _  _  ____    ____                    _ \n");
    printf(" | || ||___ \\  | __ )  __ _ _ __ ___ ___| | ___  _ __   __ _ \n");
    printf(" | || |_ __) |   |  _ \\ / _` | '__/ __/ _ | |/ _ \\| '_ \\ / _`| \n");
    printf(" |__   _/ __/  | |_) | (_| | | | (_|  __| | (_) | | | | (_| | \n");
    printf("   |_||_____|  |____/ \\__,_|_|  \\___\\___|_|\\___/|_| |_|\\__,_| \n");
    printf(RESET "\n");
    printf("\n");
}

void	exit_error(char *message, char *details, t_mlx_vars *vars)
{
	//char	*details_copy;
	printf("Error\n");
	if (message)
		printf("%s", message);
	if (details)
	{
		//details_copy = ft_strdup(details);
		//if (!details_copy)
		//	printf("Memory error strdup failed\n");
		printf ("%s", details);
		//free(details_copy);
	}
	if (vars && vars->mlx_ptr)
    {
        if (vars->config.north_tex.img_ptr)
            mlx_destroy_image(vars->mlx_ptr, vars->config.north_tex.img_ptr);
        if (vars->config.south_tex.img_ptr)
            mlx_destroy_image(vars->mlx_ptr, vars->config.south_tex.img_ptr);
        if (vars->config.east_tex.img_ptr)
            mlx_destroy_image(vars->mlx_ptr, vars->config.east_tex.img_ptr);
        if (vars->config.west_tex.img_ptr)
            mlx_destroy_image(vars->mlx_ptr, vars->config.west_tex.img_ptr);
        if (vars->win_ptr)
            mlx_destroy_window(vars->mlx_ptr, vars->win_ptr);
        mlx_destroy_display(vars->mlx_ptr);
        free(vars->mlx_ptr);
        vars->mlx_ptr = NULL;
    }
	if (vars)
		free_config(&vars->config);
    exit (EXIT_FAILURE);
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