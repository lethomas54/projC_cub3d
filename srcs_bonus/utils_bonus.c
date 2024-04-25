/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lethomas <lethomas@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 17:56:42 by lethomas          #+#    #+#             */
/*   Updated: 2024/04/25 12:32:54 by lethomas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/cub3d_bonus.h"

int	get_time(time_t *time_int)
{
	struct timeval	time_struct;

	if (gettimeofday(&time_struct, NULL))
		return (EXIT_FAILURE);
	*time_int = 1000 * time_struct.tv_sec + time_struct.tv_usec / 1000;
	return (EXIT_SUCCESS);
}

void	free_tab(int **tab)
{
	int	i;

	i = 0;
	if (tab == NULL)
		return ;
	while (tab[i])
		free(tab[i++]);
	free(tab);
}

t_vector	vec_assignation(double x, double y)
{
	t_vector	vec;

	vec.x = x;
	vec.y = y;
	return (vec);
}

t_vector	vec_normalization(t_vector vec_to_norm)
{
	t_vector	norm_vec;
	double		norm;

	norm = sqrt(vec_to_norm.x * vec_to_norm.x + vec_to_norm.y * vec_to_norm.y);
	norm_vec = vec_assignation(vec_to_norm.x / norm, vec_to_norm.y / norm);
	return (norm_vec);
}

t_vector	vec_rotate(t_vector vec_to_rot, double rot_step)
{
	t_vector	rot_vec;

	rot_vec.x = vec_to_rot.x * cos(rot_step) - vec_to_rot.y * sin(rot_step);
	rot_vec.y = vec_to_rot.x * sin(rot_step) + vec_to_rot.y * cos(rot_step);
	return (rot_vec);
}
