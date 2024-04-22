/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lethomas <lethomas@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 17:34:11 by lethomas          #+#    #+#             */
/*   Updated: 2024/04/21 09:56:06 by lethomas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int world_map[24][24] =
{
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,1,1,1,1,1,0,0,0,0,1,0,1,0,1,0,0,0,1},
  {1,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,1,0,0,0,1,0,0,0,0,1,0,0,0,1,0,0,0,1},
  {1,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,1,1,0,1,1,0,0,0,0,1,0,1,0,1,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,1,0,1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,1,0,0,0,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,1,0,1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,1,0,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

static int	init_mlx(t_mlx *mlx)
{
	mlx->ptr = mlx_init();
	if (mlx->ptr == NULL)
		return (STOP_FAILURE);
	mlx->win = mlx_new_window(mlx->ptr, WIN_SIZE_X, WIN_SIZE_Y, "cub_3d");
	if (mlx->win == NULL)
		return (STOP_FAILURE);
	mlx->img.tab = mlx_new_img(mlx->ptr, WIN_SIZE_X, WIN_SIZE_Y);
	if (mlx->img.tab == NULL)
		return (STOP_FAILURE);
	mlx->img.addr = mlx_get_data_addr(mlx->img.tab, &mlx->img.bit_per_pix,
			&mlx->img.line_len, &mlx->img.endian);
	if (mlx->img.addr == NULL) //verifier la necessite de cette condition
		return (STOP_FAILURE);
	return (CONTINUE_SUCCESS);
}

static int	set_event_hook(t_data *dt)
{
	mlx_hook(dt->mlx.win, ON_DESTROY, 0, &on_destroy_hook, dt);
	return (CONTINUE_SUCCESS);
}

static int	init_pl_tex_map(t_player *pl, t_texture *tex, int ***map,
	char *file_path)
{
	(void)file_path;
	pl->pos = vec_assignation(PLAYER_POS_X, PLAYER_POS_Y);
	pl->dir = vec_assignation(PLAYER_DIR_X, PLAYER_DIR_Y);
	tex->floor = 0x00ffffff;
	tex->ceiling = 0x00000000;
	tex->north = 0x00ff0000;
	tex->east = 0x0000ff00;
	tex->south = 0x000000ff;
	tex->west = 0x00ffff00;
	*map = world_map;
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
	if (init_pl_tex_map(&dt.pl, &dt.tex, &dt.map, argv[1]))
		return (EXIT_FAILURE);
	mlx_loop();
	return (EXIT_SUCCESS);
}
