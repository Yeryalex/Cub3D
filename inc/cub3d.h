/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrodrigu <yrodrigu@student.42barcelo>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 17:08:28 by yrodrigu          #+#    #+#             */
/*   Updated: 2025/05/13 18:12:21 by yrodrigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_h
# define CUB3D_h

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "minilibx-linux/mlx.h"
#include <stdbool.h>

#define WIDTH 1000
#define HEIGHT 800

typedef struct s_mlx_vars
{
	void        *mlx_ptr;
	void        *win_ptr;
	void        *img_ptr;
	char        *addr;
	int         bpp;
	int         line_length;
	int         endian;
} t_mlx_vars;

#endif
