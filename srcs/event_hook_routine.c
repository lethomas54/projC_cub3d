/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_hook_routine.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lethomas <lethomas@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 11:11:49 by lethomas          #+#    #+#             */
/*   Updated: 2024/08/06 12:47:52 by lethomas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

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

void	destroy_texture(void *mlx_ptr, t_texture texture)
{
	mlx_destroy_image(mlx_ptr, texture.north.ptr);
	mlx_destroy_image(mlx_ptr, texture.east.ptr);
	mlx_destroy_image(mlx_ptr, texture.south.ptr);
	mlx_destroy_image(mlx_ptr, texture.west.ptr);
}

int	on_destroy_routine(void *dt)
{
	mlx_destroy_image(((t_data *)dt)->mlx.ptr, ((t_data *)dt)->mlx.img.ptr);
	destroy_texture(((t_data *)dt)->mlx.ptr, ((t_data *)dt)->tex);
	free_tab(((t_data *)dt)->map);
	exit(EXIT_SUCCESS);
	return (EXIT_SUCCESS);
}

static void	set_new_pos(t_data *dt, t_bool move_along_dir, int dir_sign)
{
	t_vector	m_vec;
	double		wall_dist;
	double		m_dist;
	int			wall_dir;
	double		hit_box_along;

	if (move_along_dir == true)
		m_vec = vec_assignation(dir_sign * dt->pl.dir.x,
				dir_sign * dt->pl.dir.y);
	else
		m_vec = vec_assignation(dir_sign * dt->pl.dir.y,
				-dir_sign * dt->pl.dir.x);
	wall_dist = get_wall_distance(*dt, m_vec, &wall_dir);
	hit_box_along
		= HIT_BOX / (m_vec.x * ((wall_dir == NORTH) - (wall_dir == SOUTH))
			+ m_vec.y * ((wall_dir == WEST) - (wall_dir == EAST)));
	if (wall_dist > TRANSLATION_STEP + hit_box_along)
		m_dist = TRANSLATION_STEP;
	else
		m_dist = wall_dist - hit_box_along;
	dt->pl.pos.x += m_dist * m_vec.x;
	dt->pl.pos.y += m_dist * m_vec.y;
}

int	key_routine(int key_code, void *void_dt)
{
	t_data	*dt;
	int		sign;

	dt = (t_data *)void_dt;
	if (key_code == ESCAPE)
	{
		free_tab(dt->map);
		exit(EXIT_SUCCESS);
	}
	if (key_code == ARROW_LEFT || key_code == ARROW_RIGHT)
	{
		sign = 1 - 2 * (key_code == ARROW_RIGHT);
		dt->pl.dir = vec_rotate(dt->pl.dir, sign * ROTATE_STEP);
		draw_on_screen(*dt);
	}
	else if (key_code == W || key_code == S || key_code == A || key_code == D)
	{
		sign = 1 - 2 * (key_code == S) - 2 * (key_code == D);
		set_new_pos(dt, key_code == W || key_code == S, sign);
		draw_on_screen(*dt);
	}
	return (EXIT_SUCCESS);
}
