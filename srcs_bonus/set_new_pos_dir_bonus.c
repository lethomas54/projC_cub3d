/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_new_pos_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lethomas <lethomas@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 15:04:13 by lethomas          #+#    #+#             */
/*   Updated: 2024/04/25 15:14:02 by lethomas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/cub3d_bonus.h"

void	set_new_pos(t_data *dt)
{
	t_vector	m_vec;
	double		wall_dist;
	double		m_dist;
	int			wall_dir;
	double		hit_box_along;

	if (dt->move.paral == 0 && dt->move.perp == 0)
		return ;
	m_vec = vec_assignation(dt->move.paral * dt->pl.dir.x
			- dt->move.perp * dt->pl.dir.y,
		dt->move.paral * dt->pl.dir.y + dt->move.perp * dt->pl.dir.x);
	m_vec = vec_normalization(m_vec);
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

void	set_new_dir(t_data *dt)
{
	if (dt->move.rot != 0)
		dt->pl.dir = vec_rotate(dt->pl.dir, dt->move.rot * ROTATE_STEP);
}
