/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_colors.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npremont <npremont@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 14:06:46 by npremont          #+#    #+#             */
/*   Updated: 2024/04/24 14:06:56 by npremont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int	get_rgb_from_line(char *line)
{
	char	**tmp_tab;
	int		r;
	int		g;
	int		b;

	tmp_tab = ft_split(line + 2, ',');
	if (!tmp_tab)
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

int	init_colors_floor_ceiling(t_data *dt, int fd)
{
	char	*line;

	line = get_next_true_line(fd, true);
	if (line)
	{
		dt->tex.floor = get_rgb_from_line(line);
		free(line);
		if (dt->tex.floor == -1)
			return (STOP_FAILURE);
	}
	else
		return (STOP_FAILURE);
	line = get_next_true_line(fd, true);
	if (line)
	{
		dt->tex.ceiling = get_rgb_from_line(line);
		free(line);
		if (dt->tex.ceiling == -1)
			return (STOP_FAILURE);
	}
	else
		return (STOP_FAILURE);
	return (CONTINUE_SUCCESS);
}
