/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   windows.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbuitrag <rbuitrag@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 12:16:02 by rbuitrag          #+#    #+#             */
/*   Updated: 2025/05/15 10:02:59 by rbuitrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void clean_exit(t_mlx_vars *vars, int code)
{
	if (!vars || !vars->mlx_ptr || !vars->win_ptr)
		exit_error("Error pointers maps mlx", NULL, vars);
    if (vars->mlx_ptr)
    {
        if (vars->win_ptr)
			mlx_destroy_window(vars->mlx_ptr, vars->win_ptr);
		mlx_destroy_display(vars->mlx_ptr);
    }
    vars->mlx_ptr = NULL;
	vars->win_ptr = NULL;
    free_config(&vars->config);
	(void)vars;
    exit(code);
}

int	quit_cub3d(t_mlx_vars *vars)
{
	if (vars)
		clean_exit(vars, 0);
	return (ERROR);
}

int listen_mlx_input(t_mlx_vars *vars)
{
	mlx_hook(vars->win_ptr, ClientMessage, NoEventMask, quit_cub3d, vars);
	mlx_hook(vars->win_ptr, KeyPress, KeyPressMask, action_key, vars);
	mlx_hook(vars->win_ptr, KeyRelease, KeyReleaseMask, key_release, vars);
	mlx_hook(vars->win_ptr, 6, (1L << 6), action_mouse, vars);
	mlx_hook(vars->win_ptr, MotionNotify, PointerMotionMask, mouse_move, vars);
	//mlx_hook(vars->win_ptr, 17, 0, quit_cub3d, vars); Para probar en otros SO, en Win sin esto no me funciona bien
	return (SUCCESS);
}