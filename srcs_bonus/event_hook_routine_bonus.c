/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_hook_routine_bonus.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lethomas <lethomas@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 11:11:49 by lethomas          #+#    #+#             */
/*   Updated: 2024/04/25 22:01:00 by lethomas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/cub3d_bonus.h"

static void	free_exit(int exit_code, t_data dt)
{
	free_tab(dt.map);
	exit(exit_code);
}

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
	else if (key_code == W || key_code == S)
	{
		sign = 1 - 2 * (key_code == S);
		dt->move.paral = sign;
	}
	else if (key_code == A || key_code == D)
	{
		sign = 1 - 2 * (key_code == D);
		dt->move.perp = sign;
	}
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
	else if (key_code == W || key_code == S)
		dt->move.paral = 0;
	else if (key_code == A || key_code == D)
		dt->move.perp = 0;
	return (CONTINUE_SUCCESS);
}

int	loop_routine(void *void_dt)
{
	t_data			*dt;
	time_t			time;
	static t_bool	has_draw;;
	static int a;
	static time_t b;
	static time_t c;

	dt = (t_data *)void_dt;
	if (has_draw == false)
	{
		set_new_dir(dt);
		set_new_pos(dt);
		if (draw_on_screen(*dt))
			free_exit(STOP_FAILURE, *dt);
		has_draw = true;
	}
	if (get_time(&time))
		free_exit(STOP_FAILURE, *dt);
	if ((time - dt->last_draw) * 60.0 >= 1000.0)
	{
		a++;
		if (get_time(&dt->last_draw))
			free_exit(STOP_FAILURE, *dt);
		mlx_put_image_to_window(dt->mlx.ptr, dt->mlx.win, dt->mlx.img.ptr, 0, 0);
		mlx_put_image_to_window(dt->mlx.ptr, dt->mlx.win, dt->tex.gun.sprite[dt->tex.gun.index].ptr, 0, 0);
		has_draw = false;
	}
	if (a == 60)
	{
		a = 0;
		printf("time : %f\n", 60.0 / ((b - c) * 0.001));
		fflush(stdout);
		c = b;
		get_time(&b);

	}
	return (EXIT_SUCCESS);
}
