/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_hook_routine.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lethomas <lethomas@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 11:11:49 by lethomas          #+#    #+#             */
/*   Updated: 2024/04/22 14:38:02 by lethomas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	on_destroy_routine(void *dt)
{
	(void)dt; //free map
	exit(EXIT_SUCCESS);
	return (EXIT_SUCCESS);
}

int	key_routine(int key_code, void *void_dt)
{
	t_data *dt;
	int		sign;
	
	printf("%d\n", key_code);
	dt = (t_data *)void_dt;
	if (key_code == ESCAPE) //free map
		exit(EXIT_SUCCESS);
	if (key_code == ARROW_LEFT || key_code == ARROW_RIGHT)
	{
		sign = 1 - 2 * (key_code == ARROW_RIGHT);
		dt->pl.dir = vec_rotate(dt->pl.dir, sign * ROTATE_STEP);
		draw_on_screen(*dt);
	}
	else if (key_code == ARROW_UP || key_code == ARROW_DOWN)
	{
		sign = 1 - 2 * (key_code == ARROW_DOWN);
		dt->pl.pos.x += sign * dt->pl.dir.x * TRANSLATION_STEP;
		dt->pl.pos.y += sign * dt->pl.dir.y * TRANSLATION_STEP;
		draw_on_screen(*dt);
	}
	return (EXIT_SUCCESS);
}
