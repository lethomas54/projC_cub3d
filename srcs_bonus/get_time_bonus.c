/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_time_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npremont <npremont@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 16:44:06 by lethomas          #+#    #+#             */
/*   Updated: 2024/07/16 16:57:32 by npremont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/cub3d_bonus.h"

int	get_time(time_t *time_int)
{
	struct timeval	time_struct;

	if (gettimeofday(&time_struct, NULL))
		return (EXIT_FAILURE);
	*time_int = 1000 * time_struct.tv_sec + time_struct.tv_usec / 1000;
	return (EXIT_SUCCESS);
}
