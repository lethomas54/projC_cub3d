/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npremont <npremont@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 13:38:24 by npremont          #+#    #+#             */
/*   Updated: 2024/04/24 14:01:45 by npremont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

char	*get_next_true_line(int fd, t_bool trim)
{
	char	*line;
	char	*new_line;

	while (1)
	{
		line = get_next_line(fd);
		if (line && line[0] != '\n')
		{
			if (trim)
			{
				new_line = ft_strrchr(line, '\n');
				if (new_line)
					*new_line = '\0';
			}
			return (line);
		}
		free(line);
	}
	return (NULL);
}

static int	get_texture_image(t_img *img, t_data *dt, char *path)
{
	printf("tex path: %s\n", path);
	img->ptr = mlx_xpm_file_to_image(dt->mlx.ptr, path, &img->def_x,
			&img->def_y);
	if (img->ptr == NULL)
		return (STOP_FAILURE);
	return (CONTINUE_SUCCESS);
}

static int	init_textures_ptr(t_data *dt, int fd)
{
	char	*line;

	line = get_next_true_line(fd, true);
	if (line)
		if (get_texture_image(&dt->tex.north, dt, line + 3))
			return (STOP_FAILURE);
	free(line);
	line = get_next_true_line(fd, true);
	if (line)
		if (get_texture_image(&dt->tex.south, dt, line + 3))
			return (STOP_FAILURE);
	free(line);
	line = get_next_true_line(fd, true);
	if (line)
		if (get_texture_image(&dt->tex.west, dt, line + 3))
			return (STOP_FAILURE);
	free(line);
	line = get_next_true_line(fd, true);
	if (line)
		if (get_texture_image(&dt->tex.east, dt, line + 3))
			return (STOP_FAILURE);
	free(line);
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

void	ft_free_split(char **split)
{
	size_t	i;

	i = 0;
	if (!split)
		return ;
	while (split[i])
	{
		free(split[i]);
		++i;
	}
	free(split);
}
