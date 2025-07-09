/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbuitrag <rbuitrag@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 20:43:04 by rbuitrag          #+#    #+#             */
/*   Updated: 2025/07/09 20:43:04 by rbuitrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	gnl_cleanup(void)
{
	get_next_line(-2);
}

void	force_cleanup_all_state(void)
{
	gnl_cleanup();
	get_next_line(-2);
}
