/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npremont <npremont@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 17:34:11 by lethomas          #+#    #+#             */
/*   Updated: 2024/07/16 17:02:41 by npremont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/cub3d_bonus.h"

static int	init_mlx(t_mlx *mlx)
{
	mlx->ptr = mlx_init();
	if (mlx->ptr == NULL)
		return (STOP_FAILURE);
	mlx->win = mlx_new_window(mlx->ptr, WIN_SIZE_X, WIN_SIZE_Y, "cub_3d");
	if (mlx->win == NULL)
		return (STOP_FAILURE);
	mlx->img.ptr = mlx_new_image(mlx->ptr, WIN_SIZE_X, WIN_SIZE_Y);
	if (mlx->img.ptr == NULL)
		return (STOP_FAILURE);
	mlx->img.addr = mlx_get_data_addr(mlx->img.ptr, &mlx->img.bit_per_pix,
			&mlx->img.line_len, &mlx->img.endian);
	if (mlx->img.addr == NULL)
		return (STOP_FAILURE);
	return (CONTINUE_SUCCESS);
}

static int	set_event_hook(t_data *dt)
{
	mlx_do_key_autorepeatoff(dt->mlx.ptr);
	mlx_hook(dt->mlx.win, ON_DESTROY, 0, &on_destroy_routine, dt);
	mlx_hook(dt->mlx.win, ON_KEY_DOWN, 0, &key_down_routine, dt);
	mlx_hook(dt->mlx.win, ON_KEY_UP, 0, &key_up_routine, dt);
	mlx_loop_hook(dt->mlx.ptr, &loop_routine, dt);
	return (CONTINUE_SUCCESS);
}
//check failure auto_repeat_on

static int	init_data(t_data *dt, char *file_path)
{
	int	fd;

	fd = open(file_path, O_RDONLY);
	dt->pl.height = PLAYER_HEIGHT;
	if (-1 == fd)
		return (ft_putendl_fd("Error", 2), STOP_FAILURE);
	if (init_textures(dt, fd))
		return (ft_putendl_fd("Error", 2), STOP_FAILURE);
	if (init_textures_floor_ceiling(dt, fd))
		return (ft_putendl_fd("Error", 2), STOP_FAILURE);
	if (init_map_and_player(dt, fd))
		return (ft_putendl_fd("Error", 2), STOP_FAILURE);
	close(fd);
	return (CONTINUE_SUCCESS);
}

int	main(int argc, char **argv)
{
	t_data	dt;

	ft_bzero(&dt, sizeof(t_data));
	if (argc != 2)
		return (ft_putendl_fd("wrong number of argument", 2), EXIT_FAILURE);
	if (init_mlx(&dt.mlx))
		return (ft_putendl_fd("mlx initiation failure", 2), EXIT_FAILURE);
	if (set_event_hook(&dt))
		return (ft_putendl_fd("hook setting failure", 2), EXIT_FAILURE);
	if (init_data(&dt, argv[1]))
		return (ft_putendl_fd("data initialisation failure", 2), EXIT_FAILURE);
	if (set_sprite(&dt))
		return (STOP_FAILURE);
	mlx_loop(dt.mlx.ptr);
	return (EXIT_SUCCESS);
}
//verifier le retour mlx_loop
