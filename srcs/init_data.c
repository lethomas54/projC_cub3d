/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npremont <npremont@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 13:38:24 by npremont          #+#    #+#             */
/*   Updated: 2024/07/22 10:06:11 by npremont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int	get_texture_image(t_img *img, t_data *dt, char *path)
{
	char	*final_path;

	final_path = ft_strtrim(path, " \n\t\v\b");
	img->ptr = mlx_xpm_file_to_image(dt->mlx.ptr, final_path, &img->def_x,
			&img->def_y);
	free(final_path);
	if (img->ptr == NULL)
		return (STOP_FAILURE);
	return (CONTINUE_SUCCESS);
}

static int	fill_textures_ptr_and_colors(char *line, t_data *dt)
{
	if (ft_strncmp(line, "NO ", 3) == 0)
		if (get_texture_image(&dt->tex.north, dt, line + 3))
			return (STOP_FAILURE);
	if (ft_strncmp(line, "SO ", 3) == 0)
		if (get_texture_image(&dt->tex.south, dt, line + 3))
			return (STOP_FAILURE);
	if (ft_strncmp(line, "WE ", 3) == 0)
		if (get_texture_image(&dt->tex.west, dt, line + 3))
			return (STOP_FAILURE);
	if (ft_strncmp(line, "EA ", 3) == 0)
		if (get_texture_image(&dt->tex.east, dt, line + 3))
			return (STOP_FAILURE);
	if (ft_strncmp(line, "C ", 2) == 0)
		dt->tex.ceiling = get_rgb_from_line(line);
	if (ft_strncmp(line, "F ", 2) == 0)
		dt->tex.floor = get_rgb_from_line(line);
	return (CONTINUE_SUCCESS);
}

static int	is_valid_line(char *line)
{
	static int	prop_found;

	if (++prop_found > 6)
		return (STOP_FAILURE);
	if (ft_strncmp(line, "NO ", 3) == 0)
		return (CONTINUE_SUCCESS);
	if (ft_strncmp(line, "SO ", 3) == 0)
		return (CONTINUE_SUCCESS);
	if (ft_strncmp(line, "WE ", 3) == 0)
		return (CONTINUE_SUCCESS);
	if (ft_strncmp(line, "EA ", 3) == 0)
		return (CONTINUE_SUCCESS);
	if (ft_strncmp(line, "C ", 2) == 0)
		return (CONTINUE_SUCCESS);
	if (ft_strncmp(line, "F ", 2) == 0)
		return (CONTINUE_SUCCESS);
	return (STOP_FAILURE);
}

static int	init_textures_ptr(t_data *dt, int fd)
{
	char	*line;

	line = get_next_true_line(fd, true);
	if (line)
	{
		if (is_valid_line(line))
			return (STOP_FAILURE);
		if (fill_textures_ptr_and_colors(line, dt))
			return (STOP_FAILURE);
		free(line);
		if (!(dt->tex.north.ptr) || !(dt->tex.south.ptr)
			|| !(dt->tex.west.ptr) || !(dt->tex.east.ptr)
			|| dt->tex.floor == -2 || dt->tex.ceiling == -2)
			init_textures_ptr(dt, fd);
	}
	if (!(dt->tex.north.ptr) || !(dt->tex.south.ptr)
		|| !(dt->tex.west.ptr) || !(dt->tex.east.ptr)
		|| dt->tex.floor == -2 || dt->tex.ceiling == -2)
		return (STOP_FAILURE);
	if (dt->tex.ceiling == -1 || dt->tex.floor == -1)
		return (STOP_FAILURE);
	return (CONTINUE_SUCCESS);
}

int	init_textures(t_data *dt, int fd)
{
	if (init_textures_ptr(dt, fd))
		return (STOP_FAILURE);
	dt->tex.north.addr = mlx_get_data_addr(dt->tex.north.ptr,
			&dt->tex.north.bit_per_pix, &dt->tex.north.line_len,
			&dt->tex.north.endian);
	if (dt->tex.north.addr == NULL)
		return (STOP_FAILURE);
	dt->tex.east.addr = mlx_get_data_addr(dt->tex.east.ptr,
			&dt->tex.east.bit_per_pix, &dt->tex.east.line_len,
			&dt->tex.east.endian);
	if (dt->tex.east.addr == NULL)
		return (STOP_FAILURE);
	dt->tex.south.addr = mlx_get_data_addr(dt->tex.south.ptr,
			&dt->tex.south.bit_per_pix, &dt->tex.south.line_len,
			&dt->tex.south.endian);
	if (dt->tex.south.addr == NULL)
		return (STOP_FAILURE);
	dt->tex.west.addr = mlx_get_data_addr(dt->tex.west.ptr,
			&dt->tex.west.bit_per_pix, &dt->tex.west.line_len,
			&dt->tex.west.endian);
	if (dt->tex.west.addr == NULL)
		return (STOP_FAILURE);
	return (CONTINUE_SUCCESS);
}
