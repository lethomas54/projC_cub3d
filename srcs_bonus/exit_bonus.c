/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npremont <npremont@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 17:56:42 by lethomas          #+#    #+#             */
/*   Updated: 2024/07/17 11:19:55 by npremont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/cub3d_bonus.h"

void	free_tab(int **tab)
{
	int	i;

	i = 0;
	if (tab == NULL)
		return ;
	while (tab[i])
		free(tab[i++]);
	free(tab);
}

static void	destroy_sprite(void *mlx_ptr, t_lsprite sprite)
{
	int	i;

	i = 0;
	while (i < sprite.weapon.nb)
		mlx_destroy_image(mlx_ptr, sprite.weapon.sheet[i++].ptr);
	free(sprite.weapon.sheet);
}

static void	destroy_texture(void *mlx_ptr, t_texture texture)
{
	mlx_destroy_image(mlx_ptr, texture.floor.ptr);
	mlx_destroy_image(mlx_ptr, texture.ceiling.ptr);
	mlx_destroy_image(mlx_ptr, texture.north.ptr);
	mlx_destroy_image(mlx_ptr, texture.east.ptr);
	mlx_destroy_image(mlx_ptr, texture.south.ptr);
	mlx_destroy_image(mlx_ptr, texture.west.ptr);
}

void	free_exit(int exit_code, t_data dt)
{
	mlx_destroy_image(dt.mlx.ptr, dt.mlx.img.ptr);
	destroy_sprite(dt.mlx.ptr, dt.spr);
	destroy_texture(dt.mlx.ptr, dt.tex);
	mlx_destroy_window(dt.mlx.ptr, dt.mlx.win);
	free_tab(dt.map);
	system("leaks cub3d_bonus");
	exit(exit_code);
}
