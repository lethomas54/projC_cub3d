/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lethomas <lethomas@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 17:34:11 by lethomas          #+#    #+#             */
/*   Updated: 2024/08/06 13:08:01 by lethomas         ###   ########.fr       */
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

static int	init_data(t_data *dt, char *file_path)
{
	int	fd;

	set_img_to_null(dt);
	fd = open(file_path, O_RDONLY);
	dt->pl.height = PLAYER_HEIGHT;
	if (-1 == fd)
		return (ft_putendl_fd("Error", 2), ft_putendl_fd("File not found.", 2),
			STOP_FAILURE);
	if (init_textures(dt, fd))
		return (ft_putendl_fd("Error", 2),
			ft_putendl_fd("Textures or colors corrupted.", 2), STOP_FAILURE);
	if (init_map_and_player(dt, fd))
		return (ft_putendl_fd("Error", 2),
			ft_putendl_fd("Map corrupted.", 2), STOP_FAILURE);
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
		(ft_putendl_fd("mlx initiation failure", 2),  exit(EXIT_FAILURE));
	if (set_event_hook(&dt))
		(ft_putendl_fd("hook setting failure", 2),  exit(EXIT_FAILURE));
	if (init_data(&dt, argv[1]))
		(system("Leaks cub3D_bonus"), exit(EXIT_FAILURE));
	if (set_sprite(&dt))
		exit(EXIT_FAILURE);
	mlx_loop(dt.mlx.ptr);
	return (EXIT_SUCCESS);
}
