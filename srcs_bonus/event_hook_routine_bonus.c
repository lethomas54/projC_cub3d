/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_hook_routine_bonus.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lethomas <lethomas@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 11:11:49 by lethomas          #+#    #+#             */
/*   Updated: 2024/04/26 16:41:07 by lethomas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/cub3d_bonus.h"

int	on_destroy_routine(void *dt)
{
	free_exit(EXIT_SUCCESS, *(t_data *)dt);
	return (CONTINUE_SUCCESS);
}

int	key_down_routine(int key_code, void *void_dt)
{
	t_data	*dt;
	int		sign;

	dt = (t_data *)void_dt;
	if (key_code == ARROW_LEFT || key_code == ARROW_RIGHT)
	{
		sign = 1 - 2 * (key_code == ARROW_RIGHT);
		dt->move.rot = sign;
	}
	else if (key_code == LETTER_W || key_code == LETTER_S)
	{
		sign = 1 - 2 * (key_code == LETTER_S);
		dt->move.paral = sign;
	}
	else if (key_code == LETTER_A || key_code == LETTER_D)
	{
		sign = 1 - 2 * (key_code == LETTER_D);
		dt->move.perp = sign;
	}
	else if (key_code == SPACE_BAR && dt->spr.weapon.index == 0)
		dt->pl.has_shot = true;
	return (CONTINUE_SUCCESS);
}

int	key_up_routine(int key_code, void *void_dt)
{
	t_data	*dt;

	dt = (t_data *)void_dt;
	if (key_code == ESCAPE)
		free_exit(EXIT_SUCCESS, *dt);
	if (key_code == ARROW_LEFT || key_code == ARROW_RIGHT)
		dt->move.rot = 0;
	else if (key_code == LETTER_W || key_code == LETTER_S)
		dt->move.paral = 0;
	else if (key_code == LETTER_A || key_code == LETTER_D)
		dt->move.perp = 0;
	return (CONTINUE_SUCCESS);
}

int	loop_routine(void *void_dt)
{
	t_data			*dt;
	time_t			time;
	static t_bool	has_draw;;

	dt = (t_data *)void_dt;
	if (get_time(&time))
		free_exit(STOP_FAILURE, *dt);
	if (has_draw == false)
	{
		if (update_spritesheet_index(dt, time))
			free_exit(STOP_FAILURE, *dt);
		update_player_data(dt);
		if (draw_on_screen(*dt))
			free_exit(STOP_FAILURE, *dt);
		has_draw = true;
	}
	if ((time - dt->last_draw) * 6.0 >= 100.0)
	{
		if (get_time(&dt->last_draw))
			free_exit(STOP_FAILURE, *dt);
		mlx_put_image_to_window(dt->mlx.ptr, dt->mlx.win, dt->mlx.img.ptr, 0, 0);
		has_draw = false;
	}
	return (EXIT_SUCCESS);
}
