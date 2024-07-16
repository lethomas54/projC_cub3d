/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_colors_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npremont <npremont@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 14:06:46 by npremont          #+#    #+#             */
/*   Updated: 2024/07/16 15:28:08 by npremont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/cub3d_bonus.h"

static int	init_ptr_floor_ceiling(t_data *dt, int fd)
{
	char	*line;

	line = get_next_true_line(fd, true);
	if (line)
		if (get_texture_image(&dt->tex.floor, dt, line + 2))
			return (STOP_FAILURE);
	free(line);
	line = get_next_true_line(fd, true);
	if (line)
		if (get_texture_image(&dt->tex.ceiling, dt, line + 2))
			return (STOP_FAILURE);
	free(line);
	return (CONTINUE_SUCCESS);
}

int	init_textures_floor_ceiling(t_data *dt, int fd)
{
	if (init_ptr_floor_ceiling(dt, fd))
		return (STOP_FAILURE);
	dt->tex.floor.addr = mlx_get_data_addr(dt->tex.floor.ptr,
			&dt->tex.floor.bit_per_pix, &dt->tex.floor.line_len,
			&dt->tex.floor.endian);
	if (dt->tex.floor.addr == NULL)
		return (STOP_FAILURE);
	dt->tex.ceiling.addr = mlx_get_data_addr(dt->tex.ceiling.ptr,
			&dt->tex.ceiling.bit_per_pix, &dt->tex.ceiling.line_len,
			&dt->tex.ceiling.endian);
	if (dt->tex.ceiling.addr == NULL)
		return (STOP_FAILURE);
	return (CONTINUE_SUCCESS);
}
