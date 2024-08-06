/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_colors_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lethomas <lethomas@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 14:06:46 by npremont          #+#    #+#             */
/*   Updated: 2024/08/06 12:32:00 by lethomas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/cub3d_bonus.h"

int	get_rgb_from_line(char *line)
{
	char	**tmp_tab;
	int		r;
	int		g;
	int		b;
	char	*final_line;

	final_line = ft_strtrim(line, " \n\t\v\b");
	tmp_tab = ft_split(final_line + 2, ',');
	free(final_line);
	if (!tmp_tab)
		return (-1);
	if (!tmp_tab[0] || !tmp_tab[1] || !tmp_tab[2] || tmp_tab[3])
		return (-1);
	r = ft_atoi(tmp_tab[0], 0);
	g = ft_atoi(tmp_tab[1], 0);
	b = ft_atoi(tmp_tab[2], 0);
	ft_free_split(tmp_tab);
	if ((r < 0 || r > 255)
		|| (g < 0 || g > 255)
		|| (b < 0 || b > 255))
		return (-1);
	return (65536 * r + 256 * g + b);
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

char	*get_next_true_line(int fd, t_bool trim)
{
	char	*line;
	char	*line_trimmed;
	char	*new_line;

	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			return (NULL);
		if (line && line[0] != '\n')
		{
			if (trim)
			{
				line_trimmed = ft_strtrim(line, " \t\v");
				free(line);
				new_line = ft_strrchr(line, '\n');
				if (new_line)
					*new_line = '\0';
				return (line_trimmed);
			}
			return (line);
		}
		free(line);
	}
	return (NULL);
}

int	line_is_cringe(char *line)
{
	int	i;

	i = -1;
	while (line[++i])
	{
		if (line[i] != '0' && line[i] != '1' && line[i] != '\0'
			&& line[i] != 'N' && line[i] != 'S' && line[i] != 'E'
			&& line[i] != 'W' && line[i] != ' ' && line[i] != '\n')
			return (STOP_FAILURE);
	}
	return (CONTINUE_SUCCESS);
}

int	init_textures_floor_and_ceiling(t_data *dt)
{
	dt->tex.ceiling.addr = mlx_get_data_addr(dt->tex.ceiling.ptr,
			&dt->tex.ceiling.bit_per_pix, &dt->tex.ceiling.line_len,
			&dt->tex.ceiling.endian);
	if (dt->tex.ceiling.addr == NULL)
		return (STOP_FAILURE);
	dt->tex.floor.addr = mlx_get_data_addr(dt->tex.floor.ptr,
			&dt->tex.floor.bit_per_pix, &dt->tex.floor.line_len,
			&dt->tex.floor.endian);
	if (dt->tex.floor.addr == NULL)
		return (STOP_FAILURE);
	return (CONTINUE_SUCCESS);
}
