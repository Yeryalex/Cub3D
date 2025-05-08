/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbuitrag <rbuitrag@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 09:48:56 by rbuitrag          #+#    #+#             */
/*   Updated: 2025/05/08 14:06:20 by rbuitrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	exit_error(char *message, char *details, t_mlx_vars *vars)
{
	char	*details_copy;
	printf("Error\n");
	if (message)
		printf("%s ", message);
	if (details)
	{
		details_copy = ft_strdup(details);
		if (!details_copy)
			printf("Memory error strdup failed\n");
		printf ("%s ", details);
		free(details_copy);
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
static void	print_controls(void)
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
    printf(" | || ||___ \\  | __ )  __ _ _ __ ___ ___| | ___  _ __   __ _ "); 
    printf(" | || |_ __) |   |  _ \\ / _` | '__/ __/ _ | |/ _ \\| '_ \\ / _` | \n");
    printf(" |__   _/ __/  | |_) | (_| | | | (_|  __| | (_) | | | | (_| | \n");
    printf("   |_||_____|  |____/ \\__,_|_|  \\___\\___|_|\\___/|_| |_|\\__,_| \n");
    printf(RESET "\n");
    printf("\n");
}

int	main(int ac, char **av)
{
    t_mlx_vars	vars;

    if (ac != 2)
        exit_error("Usage: ./cub3d <path/to/map_file.cub>", NULL, NULL);
    ft_memset(&vars, 0, sizeof(t_mlx_vars));
    if (parser_scene(av, &vars) != 0)
        exit_error("Error parsing scene file", NULL, &vars);
    vars.mlx_ptr = mlx_init();
    if (!vars.mlx_ptr)
        exit_error("MLX init failed", NULL, &vars);
    vars.win_ptr = mlx_new_window(vars.mlx_ptr, vars.config.win_width,
            vars.config.win_height, WIN_TITLE);
    if (!vars.win_ptr)
        exit_error("Window creation failed", NULL, &vars);
    print_controls();
    mlx_loop(vars.mlx_ptr);
    free_config(&vars.config);
    free(vars.mlx_ptr);
    return (0);
}
