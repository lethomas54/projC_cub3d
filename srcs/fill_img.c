/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_img.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lethomas <lethomas@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 11:37:41 by lethomas          #+#    #+#             */
/*   Updated: 2024/04/22 16:07:39 by lethomas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	set_pixel_nb(double wall_dist, int *floor_pix, int *wall_pix,
	int *ceiling_pix)
{
	*floor_pix = WIN_SIZE_Y * 0.5
		* (1.0 - PLAYER_HEIGHT / (wall_dist * tan(FOV_Y * 0.5)));
	if (*floor_pix < 0)
		*floor_pix = 0;
	*wall_pix = WIN_SIZE_Y * 0.5 * WALL_HEIGHT / (wall_dist * tan(FOV_Y * 0.5)); //pixelsize has no impact since we dont use texture yet
	*ceiling_pix = WIN_SIZE_Y - *floor_pix - *wall_pix;
	if (*ceiling_pix < 0)
		*ceiling_pix = 0;
}

static void	set_wall_img(t_texture tex, int wall_dir, t_img *wall_img)
{
	if (wall_dir == NORTH)
		*wall_img = tex.north;
	else if (wall_dir == EAST)
		*wall_img = tex.east;
	else if (wall_dir == SOUTH)
		*wall_img = tex.south;
	else
		*wall_img = tex.west;
}

static void	fill_with_color(int pixel_nb, int color, t_img *img)
{
	while (pixel_nb--)
	{
		*(unsigned int *)img->addr = color;
		img->addr += img->bit_per_pix / 8;
	}
}

static void	fill_with_texture(int pixel_nb, t_img tex, double corner_dist,
	t_img *img)
{
	while (pixel_nb--)
	{
		*(unsigned int *)img->addr = color;
		img->addr += img->bit_per_pix / 8;
	}
}

void	fill_img(t_data dt, double wall_dist, int wall_dir, double corner_dist)
{
	int		i;
	int		floor_pix;
	int		wall_pix;
	int		ceiling_pix;
	t_img	wall_img;
	

	i = 0;
	set_pixel_nb(wall_dist, &floor_pix, &wall_pix, &ceiling_pix);
	set_wall_img(dt.tex, wall_dir, &wall_img);
	while (i++ < PIXEL_SIZE)
	{
		fill_with_color(ceiling_pix, dt.tex.ceiling, &dt.mlx.img);
		fill_with_texture(wall_pix, wall_img, &dt.mlx.img);
		fill_with_color(floor_pix, dt.tex.floor, &dt.mlx.img);
	}
}
