/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbuitrag <rbuitrag@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 09:48:56 by rbuitrag          #+#    #+#             */
/*   Updated: 2025/07/09 20:34:03 by rbuitrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static void	free_mlx_images(t_mlx_vars *vars)
{
	if (vars->config.north_tex.img_ptr)
		mlx_destroy_image(vars->mlx_ptr, vars->config.north_tex.img_ptr);
	if (vars->config.south_tex.img_ptr)
		mlx_destroy_image(vars->mlx_ptr, vars->config.south_tex.img_ptr);
	if (vars->config.east_tex.img_ptr)
		mlx_destroy_image(vars->mlx_ptr, vars->config.east_tex.img_ptr);
	if (vars->config.west_tex.img_ptr)
		mlx_destroy_image(vars->mlx_ptr, vars->config.west_tex.img_ptr);
	if (vars->img_ptr)
		mlx_destroy_image(vars->mlx_ptr, vars->img_ptr);
}

void	exit_error(char *message, char *details, t_mlx_vars *vars)
{
	printf("Error\n");
	if (message)
		printf("%s ", message);
	if (details)
		printf("%s\n", details);
	gnl_cleanup();
	if (vars && vars->mlx_ptr)
	{
		free_mlx_images(vars);
		if (vars->win_ptr)
			mlx_destroy_window(vars->mlx_ptr, vars->win_ptr);
		mlx_destroy_display(vars->mlx_ptr);
		free(vars->mlx_ptr);
		vars->mlx_ptr = NULL;
	}
	if (vars)
		free_config(&vars->config);
	exit(EXIT_FAILURE);
}

void	exit_error_parsing(char *message, char *details, t_config *config)
{
	printf("Error\n");
	if (message)
		printf("%s ", message);
	if (details)
		printf("%s\n", details);
	gnl_cleanup();
	if (config)
		free_config(config);
	exit(EXIT_FAILURE);
}

int	main(int ac, char **av)
{
	t_mlx_vars	vars;

	if (ac != 2)
		exit_error("Usage: ./cub3d <path/to/map_file.cub>\n", NULL, NULL);
	force_cleanup_all_state();
	ft_memset(&vars, 0, sizeof(t_mlx_vars));
	if (parser_scene(av, &vars) != 0)
		exit_error("Error parsing scene file", NULL, &vars);
	if (validate_texture_files(&vars.config) != SUCCESS)
		exit_error_parsing("Error validating texture files",
			NULL, &vars.config);
	print_controls();
	if (init_window_and_image(&vars))
		exit_error("Failed to initialize window and image", NULL, &vars);
	if (load_textures(&vars) != 0)
		exit_error("Failed to load textures", NULL, &vars);
	listen_mlx_input(&vars);
	mlx_loop(vars.mlx_ptr);
	return (0);
}
