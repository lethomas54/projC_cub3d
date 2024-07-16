/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_spritesheet_index_bonus.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npremont <npremont@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 14:47:30 by lethomas          #+#    #+#             */
/*   Updated: 2024/07/16 16:59:40 by npremont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/cub3d_bonus.h"

static int	update_weapon_spritesheet(t_sprite *wp, t_bool has_shot,
	time_t time)
{
	if (has_shot == true)
	{
		wp->index = 1;
		if (get_time(&wp->last_switch))
			return (STOP_FAILURE);
	}
	else if (wp->index != 0)
	{
		if (time - wp->last_switch >= wp->to_switch)
		{
			wp->index = (wp->index + 1) % wp->nb;
			if (get_time(&wp->last_switch))
				return (STOP_FAILURE);
		}
	}
	return (CONTINUE_SUCCESS);
}

int	update_spritesheet_index(t_data *dt, time_t time)
{
	if (update_weapon_spritesheet(&dt->spr.weapon, dt->pl.has_shot, time))
		return (STOP_FAILURE);
	return (CONTINUE_SUCCESS);
}
