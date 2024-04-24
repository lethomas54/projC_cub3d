/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npremont <npremont@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 14:07:17 by npremont          #+#    #+#             */
/*   Updated: 2024/04/24 18:56:59 by npremont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

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

static int	get_map_x(t_list *map)
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

static int	ft_normalize_map(t_list *map, int map_len)
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

static t_list	*ft_get_map_in_list(int fd)
{
	char	*line;
	t_list	*map;
	t_list	*new;

	while (1)
	{
		line = get_next_true_line(fd, false);
		if (line && line[0] != '\n')
			break ;
		if (!line)
			return (NULL);
		free(line);
	}
	map = ft_lstnew(line);
	if (!map)
		return (free(line), NULL);
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		new = ft_lstnew(line);
		if (!new)
			return (ft_lstclear(&map, free), free(line), NULL);
		ft_lstadd_back(&map, new);
	}
	return (map);
}

int	ft_replace_player(char *c, double x, double y, t_data *dt)
{
	static int	found;

	++found;
	if (found != 1)
		return (STOP_FAILURE);
	dt->pl.pos = vec_assignation(x + 0.5, y + 0.5);
	if ((*c) == 'N')
		dt->pl.dir = vec_assignation(-1, 0);
	if ((*c) == 'S')
		dt->pl.dir = vec_assignation(1, 0);
	if ((*c) == 'W')
		dt->pl.dir = vec_assignation(0, 1);
	if ((*c) == 'E')
		dt->pl.dir = vec_assignation(0, -1);
	(*c) = '0';
	return (CONTINUE_SUCCESS);
}

int	ft_init_player(t_list *map, t_data *dt)
{
	char	*str;
	int		i;
	int		y;

	y = 0;
	while (map)
	{
		str = (char *)map->content;
		i = -1;
		while (str[++i])
			if (str[i] == 'N' || str[i] == 'S' || str[i] == 'E'
				|| str[i] == 'W')
				if (ft_replace_player(&str[i], i, y, dt))
					return (STOP_FAILURE);
		++y;
		map = map->next;
	}
	return (CONTINUE_SUCCESS);
}

int	**ft_list_to_matrix(t_list *map, int map_x, int map_y)
{
	int		**res;
	int		i;
	int		j;
	char	*str;

	res = (int **)ft_calloc(map_y + 1, sizeof(int *));
	if (!res)
		return (ft_lstclear(&map, free), NULL);
	i = -1;
	while (map)
	{
		res[++i] = (int *)malloc((map_x - 1) * sizeof(int));
		if (res[i] == NULL)
			return (ft_lstclear(&map, free), free(res), NULL);
		str = (char *)map->content;
		j = -1;
		while (str[++j])
			res[i][j] = str[j] - '0';
		map = map->next;
	}
	i = -1;
	while (res[++i])
	{
		j = -1;
		while (++j < map_x - 1)
			printf("%d", res[i][j]);
		printf("\n");
	}
	return (res);
}

int	init_map_and_player(t_data *dt, int fd)
{
	t_list	*map;
	int		map_x;
	int		map_y;

	map = ft_get_map_in_list(fd);
	if (!map)
		return (STOP_FAILURE);
	map_x = get_map_x(map);
	map_y = ft_lstsize(map);
	if (ft_normalize_map(map, map_x))
		return (ft_lstclear(&map, free), STOP_FAILURE);
	if (ft_init_player(map, dt))
		return (ft_lstclear(&map, free), STOP_FAILURE);
	dt->map = ft_list_to_matrix(map, map_x, map_y);
	if (!dt->map)
		return (STOP_FAILURE);
	return (CONTINUE_SUCCESS);
}
