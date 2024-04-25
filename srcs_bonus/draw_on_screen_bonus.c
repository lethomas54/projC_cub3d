/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_on_screen_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lethomas <lethomas@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 09:51:47 by lethomas          #+#    #+#             */
/*   Updated: 2024/04/25 12:39:09 by lethomas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/cub3d_bonus.h"

static void	*start_draw_floor_ceiling(void *arg)
{
	t_thread_arg	*thread_arg;
	int				start_line;
	int				end_line;

	thread_arg = (t_thread_arg *)arg;
	start_line = (WIN_SIZE_Y - 1) / 2 * thread_arg->index / NB_THREAD;
	end_line = (WIN_SIZE_Y - 1) / 2 * (thread_arg->index + 1) / NB_THREAD;
	if (thread_arg->index == NB_THREAD - 1)
		end_line++;
	draw_floor_ceiling(thread_arg->data, start_line, end_line);
	return (NULL);
}

static void	*start_draw_wall(void *arg)
{
	t_thread_arg	*thread_arg;
	int				start_col;
	int				end_col;

	thread_arg = (t_thread_arg *)arg;
	start_col = (WIN_SIZE_X - 1) * thread_arg->index / NB_THREAD;
	end_col = (WIN_SIZE_X - 1) * (thread_arg->index + 1) / NB_THREAD;
	if (thread_arg->index == NB_THREAD - 1)
		end_col++;
	draw_wall(thread_arg->data, start_col, end_col);
	return (NULL);
}

static int	create_thread_data(pthread_t **pthread,
	t_thread_arg **thread_arg)
{
	*pthread = (pthread_t *)ft_calloc(NB_THREAD, sizeof(pthread_t));
	if (*pthread == NULL)
		return (STOP_FAILURE);
	*thread_arg = (t_thread_arg *)malloc(NB_THREAD * sizeof(t_thread_arg));
	if (*thread_arg == NULL)
	{
		free(*pthread);
		return (STOP_FAILURE);
	}
	return (CONTINUE_SUCCESS);
}

static int	create_thread(t_data dt,
	void *(*thread_routine)(void *))
{
	int				i;
	int				return_value;
	pthread_t		*pthread;
	t_thread_arg	*thread_arg;

	i = 0;
	return_value = CONTINUE_SUCCESS;
	if (create_thread_data(&pthread, &thread_arg))
		return (STOP_FAILURE);
	while (i < NB_THREAD && return_value == CONTINUE_SUCCESS)
	{
		thread_arg[i].data = dt;
		thread_arg[i].index = i;
		return_value = pthread_create(pthread + i, NULL, thread_routine,
				thread_arg + i);
		i++;
	}
	i = 0;
	while (i < NB_THREAD && pthread[i])
		if (pthread_join(pthread[i++], NULL))
			return_value = STOP_FAILURE;
	free(pthread);
	free(thread_arg);
	return (return_value);
}

int	draw_on_screen(t_data dt)
{
	if (create_thread(dt, &start_draw_floor_ceiling))
		return (STOP_FAILURE);
	if (create_thread(dt, &start_draw_wall))
		return (STOP_FAILURE);
	return (CONTINUE_SUCCESS);
}
//check failure mlx_put
