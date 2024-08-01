/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lethomas <lethomas@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 14:07:17 by npremont          #+#    #+#             */
/*   Updated: 2024/08/01 15:18:05 by lethomas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static t_list	*ft_get_map_in_list(int fd)
{
	char	*line;
	t_list	*map;
	t_list	*new;

	ft_skip_whitespaces(fd, &line);
	if (line_is_cringe(line))
		return (free(line), NULL);
	map = ft_lstnew(line);
	if (!map)
		return (free(line), NULL);
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (line_is_cringe(line))
			return (ft_lstclear(&map, free), free(line), NULL);
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
	t_list	*map_og;

	map_og = map;
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
	ft_lstclear(&map_og, free);
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
	if (ft_is_map_playable(dt, map_x, map_y))
		return (STOP_FAILURE);
	return (CONTINUE_SUCCESS);
}
