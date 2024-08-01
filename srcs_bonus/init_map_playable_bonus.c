/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map_playable_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npremont <npremont@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 14:34:51 by npremont          #+#    #+#             */
/*   Updated: 2024/08/01 14:35:04 by npremont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/cub3d_bonus.h"

int	ft_is_map_playable(t_data *dt, int map_x, int map_y)
{
	int	i;
	int	j;

	i = -1;
	while (++i < map_y)
	{
		j = -1;
		while (++j < map_x - 1)
		{
			if (dt->map[i][j] == 0)
			{
				if ((i < 1 || i >= map_y) || (j < 1 || j >= map_x))
					return (STOP_FAILURE);
				if (dt->map[i + 1][j] != 0 && dt->map[i + 1][j] != 1)
					return (STOP_FAILURE);
				if (dt->map[i - 1][j] != 0 && dt->map[i - 1][j] != 1)
					return (STOP_FAILURE);
				if (dt->map[i][j + 1] != 0 && dt->map[i][j + 1] != 1)
					return (STOP_FAILURE);
				if (dt->map[i][j - 1] != 0 && dt->map[i][j - 1] != 1)
					return (STOP_FAILURE);
			}
		}
	}
	return (CONTINUE_SUCCESS);
}
