/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map_utils_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npremont <npremont@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 13:28:50 by npremont          #+#    #+#             */
/*   Updated: 2024/07/22 10:09:28 by npremont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/cub3d_bonus.h"

void	*ft_realloc(void *ptr, size_t size, int free_ptr)
{
	void	*new;

	if (!ptr)
	{
		new = malloc(size);
		if (!new)
			return (NULL);
	}
	else
	{
		if (sizeof(ptr) < size)
		{
			new = malloc(size);
			if (!new)
				return (NULL);
			ft_memcpy(new, ptr, ft_strlen((char *)ptr));
			if (free_ptr)
				free(ptr);
		}
		else
		{
			new = ptr;
		}
	}
	return (new);
}

int	get_map_x(t_list *map)
{
	int	len;
	int	line_len;

	len = 0;
	while (map)
	{
		line_len = ft_strlen((char *)map->content);
		if (line_len > len)
			len = line_len;
		map = map->next;
	}
	return (len);
}

int	ft_normalize_map(t_list *map, int map_len)
{
	int		i;
	int		y;
	char	*line;

	y = 0;
	while (map)
	{
		map->content = ft_realloc(map->content, map_len, 1);
		if (!map->content)
			return (STOP_FAILURE);
		line = (char *)map->content;
		i = -1;
		while (++i < map_len - 1)
		{
			if (line[i] != '0' && line[i] != '1' && line[i] != '\0'
				&& line[i] != 'N' && line[i] != 'S' && line[i] != 'E'
				&& line[i] != 'W')
				line[i] = '2';
		}
		line[i] = '\0';
		++y;
		map = map->next;
	}
	return (CONTINUE_SUCCESS);
}

void	ft_skip_whitespaces(int fd, char **line)
{
	while (1)
	{
		(*line) = get_next_true_line(fd, false);
		if ((*line) && (*line)[0] != '\n')
			break ;
		if (!(*line))
			return ;
		free((*line));
	}
}

void	set_img_to_null(t_data *dt)
{
	dt->tex.north.ptr = NULL;
	dt->tex.south.ptr = NULL;
	dt->tex.west.ptr = NULL;
	dt->tex.east.ptr = NULL;
	dt->tex.floor.ptr = NULL;
	dt->tex.ceiling.ptr = NULL;
}
