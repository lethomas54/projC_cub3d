/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lethomas <lethomas@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 17:34:11 by lethomas          #+#    #+#             */
/*   Updated: 2024/04/25 21:55:51 by lethomas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/cub3d_bonus.h"

#define MAP_SIZE_X 24
#define MAP_SIZE_Y 24

int world_map[MAP_SIZE_Y][MAP_SIZE_X] =
{
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,1,0,1,0,1,0,0,0,1},
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
  {1,0,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
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
	mlx_hook(dt->mlx.win, ON_DESTROY, 0, &on_destroy_routine, dt);
	mlx_hook(dt->mlx.win, ON_KEY_DOWN, 0, &key_down_routine, dt);
	mlx_hook(dt->mlx.win, ON_KEY_UP, 0, &key_up_routine, dt);
	mlx_loop_hook(dt->mlx.ptr, &loop_routine, dt);
	return (CONTINUE_SUCCESS);
}
//check failure auto_repeat_on

static int	get_sprite(void *mlx_ptr, t_sprite *sprite, char *path, int img_nb)
{
	t_img	full_sprite;
	int		i;
	int		j;
	int		sprite_index;

	sprite_index = 0;
	full_sprite.ptr = mlx_xpm_file_to_image(mlx_ptr, path, &full_sprite.def_x, &full_sprite.def_y);
	if (full_sprite.ptr == NULL)
		return (STOP_FAILURE);
	full_sprite.addr = mlx_get_data_addr(full_sprite.ptr, &full_sprite.bit_per_pix, &full_sprite.line_len, &full_sprite.endian);
	if (full_sprite.addr == NULL)
		return (STOP_FAILURE);
	sprite->index = 0;
	sprite->nb = img_nb;
	sprite->def_x = full_sprite.def_x / img_nb;
	sprite->def_y = full_sprite.def_y;
	sprite->sprite = (t_img *)malloc(img_nb * sizeof(t_img));
	while (sprite_index < img_nb)
	{
		sprite->sprite[sprite_index].ptr = mlx_new_image(mlx_ptr, sprite->def_x, sprite->def_y);
		if (sprite->sprite[sprite_index].ptr == NULL)
			return (STOP_FAILURE);
		sprite->sprite[sprite_index].addr = mlx_get_data_addr(sprite->sprite[sprite_index].ptr, &sprite->sprite[sprite_index].bit_per_pix, &sprite->sprite[sprite_index].line_len, &sprite->sprite[sprite_index].endian);
		if (sprite->sprite[sprite_index].addr == NULL)
			return (STOP_FAILURE);
		j = 0;
		while (j < sprite->def_y)
		{
			i = 0;
			while (i < sprite->def_x)
			{
				*(unsigned int *)(sprite->sprite[sprite_index].addr + i * sprite->sprite[sprite_index].bit_per_pix / 8 + j * sprite->sprite[sprite_index].line_len) = *(unsigned int *)(full_sprite.addr + i * full_sprite.bit_per_pix / 8 + j * full_sprite.line_len);
				i++;
			}
			j++;
		}
		full_sprite.addr += sprite->def_x * full_sprite.bit_per_pix / 8;
		sprite_index++;
	}
	mlx_destroy_image(mlx_ptr, full_sprite.ptr);
	return (CONTINUE_SUCCESS);
}

static int	init_data(t_data *dt, char *file_path)
{
	int	i;
	int	j;

	i = 0;
	(void)file_path;
	if (get_time(&dt->last_draw))
		return (STOP_FAILURE);
	dt->pl.pos = vec_assignation(PLAYER_POS_X, PLAYER_POS_Y);
	dt->pl.dir = vec_assignation(PLAYER_DIR_X, PLAYER_DIR_Y);
	if (get_sprite(dt->mlx.ptr, &dt->tex.gun,"texture/gun.xpm", 4))
		return (STOP_FAILURE);
	dt->tex.floor.ptr = mlx_xpm_file_to_image(dt->mlx.ptr, "texture/rect_tile.xpm", &dt->tex.floor.def_x, &dt->tex.floor.def_y);
	if (dt->tex.floor.ptr == NULL)
		return (STOP_FAILURE);
	dt->tex.ceiling.ptr = mlx_xpm_file_to_image(dt->mlx.ptr, "texture/rect_tile.xpm", &dt->tex.ceiling.def_x, &dt->tex.ceiling.def_y);
	if (dt->tex.ceiling.ptr == NULL)
		return (STOP_FAILURE);
	dt->tex.north.ptr = mlx_xpm_file_to_image(dt->mlx.ptr, "texture/bookshelf.xpm", &dt->tex.north.def_x, &dt->tex.north.def_y);
	if (dt->tex.north.ptr == NULL)
		return (STOP_FAILURE);
	dt->tex.east.ptr = mlx_xpm_file_to_image(dt->mlx.ptr, "texture/bluelined_tile.xpm", &dt->tex.east.def_x, &dt->tex.east.def_y);
	if (dt->tex.east.ptr == NULL)
		return (STOP_FAILURE);
	dt->tex.south.ptr = mlx_xpm_file_to_image(dt->mlx.ptr, "texture/hex_tile.xpm", &dt->tex.south.def_x, &dt->tex.south.def_y);
	if (dt->tex.south.ptr == NULL)
		return (STOP_FAILURE);
	dt->tex.west.ptr = mlx_xpm_file_to_image(dt->mlx.ptr, "texture/rect_tile.xpm", &dt->tex.west.def_x, &dt->tex.west.def_y);
	if (dt->tex.west.ptr == NULL)
		return (STOP_FAILURE);
	dt->tex.floor.addr = mlx_get_data_addr(dt->tex.floor.ptr, &dt->tex.floor.bit_per_pix, &dt->tex.floor.line_len, &dt->tex.floor.endian);
	if (dt->tex.floor.addr == NULL)
		return (STOP_FAILURE);
	dt->tex.ceiling.addr = mlx_get_data_addr(dt->tex.ceiling.ptr, &dt->tex.ceiling.bit_per_pix, &dt->tex.ceiling.line_len, &dt->tex.ceiling.endian);
	if (dt->tex.ceiling.addr == NULL)
		return (STOP_FAILURE);
	dt->tex.north.addr = mlx_get_data_addr(dt->tex.north.ptr, &dt->tex.north.bit_per_pix, &dt->tex.north.line_len, &dt->tex.north.endian);
	if (dt->tex.north.addr == NULL)
		return (STOP_FAILURE);
	dt->tex.east.addr = mlx_get_data_addr(dt->tex.east.ptr, &dt->tex.east.bit_per_pix, &dt->tex.east.line_len, &dt->tex.east.endian);
	if (dt->tex.east.addr == NULL)
		return (STOP_FAILURE);
	dt->tex.south.addr = mlx_get_data_addr(dt->tex.south.ptr, &dt->tex.south.bit_per_pix, &dt->tex.south.line_len, &dt->tex.south.endian);
	if (dt->tex.south.addr == NULL)
		return (STOP_FAILURE);
	dt->tex.west.addr = mlx_get_data_addr(dt->tex.west.ptr, &dt->tex.west.bit_per_pix, &dt->tex.west.line_len, &dt->tex.west.endian);
	if (dt->tex.west.addr == NULL)
		return (STOP_FAILURE);
	dt->map = (int **)ft_calloc(MAP_SIZE_X + 1, sizeof(int *));
	if (dt->map == NULL)
		return (STOP_FAILURE);
	while (i < MAP_SIZE_X)
	{
		j = -1;
		dt->map[i] = (int *)malloc(MAP_SIZE_Y * sizeof(int));
		if (dt->map[i] == NULL)
			return (free(dt->map), STOP_FAILURE);
		while (++j < MAP_SIZE_Y)
			dt->map[i][j] = world_map[i][j];
		i++;
	}
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
	mlx_loop(dt.mlx.ptr);
	return (EXIT_SUCCESS);
}
//verifier le retour mlx_loop
