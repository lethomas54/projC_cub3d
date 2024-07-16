/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_wall_distance_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npremont <npremont@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 16:02:22 by lethomas          #+#    #+#             */
/*   Updated: 2024/07/16 15:33:55 by npremont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/cub3d_bonus.h"

static void	init_side_dist(t_vector pos, t_vector ray, t_vector *next_side_dist,
	t_vector *delta_dist)
{
	if (ray.x != 0)
		delta_dist->x = fabs(1.0 / ray.x);
	else
		delta_dist->x = 1.0e50;
	if (ray.y != 0)
		delta_dist->y = fabs(1.0 / ray.y);
	else
		delta_dist->y = 1.0e50;
	if (ray.x < 0)
		next_side_dist->x = (pos.x - (int)pos.x) * delta_dist->x;
	else
		next_side_dist->x = (1 - pos.x + (int)pos.x) * delta_dist->x;
	if (ray.y < 0)
		next_side_dist->y = (pos.y - (int)pos.y) * delta_dist->y;
	else
		next_side_dist->y = (1 - pos.y + (int)pos.y) * delta_dist->y;
}

static double	set_wall_distance(t_vector next_side_dist, t_vector delta_dist,
	int wall_dir)
{
	if (wall_dir == WEST || wall_dir == EAST)
		return (next_side_dist.y - delta_dist.y);
	return (next_side_dist.x - delta_dist.x);
}

double	get_wall_distance(t_data dt, t_vector ray, int *wall_dir)
{
	int			*index_step;
	int			*wall_index;
	t_vector	next_side_dist;
	t_vector	delta_dist;

	wall_index = (int [2]){(int)dt.pl.pos.x, (int)dt.pl.pos.y};
	index_step = (int [2]){1 - 2 * (ray.x < 0), 1 - 2 * (ray.y < 0)};
	init_side_dist(dt.pl.pos, ray, &next_side_dist, &delta_dist);
	while (true)
	{
		if (next_side_dist.x < next_side_dist.y)
		{
			next_side_dist.x += delta_dist.x;
			wall_index[0] += index_step[0];
			*wall_dir = (index_step[0] == -1);
		}
		else
		{
			next_side_dist.y += delta_dist.y;
			wall_index[1] += index_step[1];
			*wall_dir = 2 + (index_step[1] == -1);
		}
		if (dt.map[wall_index[1]][wall_index[0]] == 1)
			return (set_wall_distance(next_side_dist, delta_dist, *wall_dir));
	}
}
