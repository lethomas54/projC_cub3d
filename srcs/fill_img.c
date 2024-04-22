/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_img.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lethomas <lethomas@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 11:37:41 by lethomas          #+#    #+#             */
/*   Updated: 2024/04/22 18:55:54 by lethomas         ###   ########.fr       */
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
	wall_pix[0] = WIN_SIZE_Y * 0.5 - *floor_pix;
	wall_pix[1] = WIN_SIZE_Y * 0.5
		* (WALL_HEIGHT - PLAYER_HEIGHT) / (wall_dist * tan(FOV_Y * 0.5));
	*ceiling_pix = WIN_SIZE_Y * 0.5 - wall_pix[1];
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

static void	fill_with_texture(int pixel_nb[2], t_img tex, double corner_dist,
	t_img *img)
{
	int		texture_col;
	double	texture_step;
	double	percent_texture_visible;
	int		i;

	i = 0;
	texture_col = (int)((corner_dist * TEXTURE_SIZE_X / (WALL_HEIGHT * TEXTURE_SIZE_Y)
		- (int)(corner_dist * TEXTURE_SIZE_X / (WALL_HEIGHT * TEXTURE_SIZE_Y))) * TEXTURE_SIZE_X);
	percent_texture_visible = WIN_SIZE_Y * 0.5 / pixel_nb[1]; //null case
	if (percent_texture_visible > 1.0)
		percent_texture_visible = 1.0;
	if (pixel_nb[1] > WIN_SIZE_Y * 0.5)
		pixel_nb[1] = WIN_SIZE_Y * 0.5;
	texture_step = percent_texture_visible * TEXTURE_SIZE_Y * (1 - PLAYER_HEIGHT / WALL_HEIGHT) / pixel_nb[1];  //null case
	while (i < pixel_nb[1] + pixel_nb[0])
	{
		*(unsigned int *)img->addr = *(unsigned int *)(tex.addr + tex.line_len * (int)((TEXTURE_SIZE_Y - 1) - (1 - percent_texture_visible) * TEXTURE_SIZE_Y * (1 - PLAYER_HEIGHT / WALL_HEIGHT) - i++ * texture_step) + texture_col * tex.bit_per_pix / 8);
		img->addr += img->bit_per_pix / 8;
	}
}

void	fill_img(t_data dt, double wall_dist, int wall_dir, double corner_dist)
{
	int		i;
	int		floor_pix;
	int		wall_pix[2];
	int		ceiling_pix;
	t_img	wall_tex;


	i = 0;
	set_pixel_nb(wall_dist, &floor_pix, &wall_pix, &ceiling_pix);
	set_wall_img(dt.tex, wall_dir, &wall_tex);
	while (i++ < PIXEL_SIZE)
	{
		fill_with_color(ceiling_pix, dt.tex.ceiling, &dt.mlx.img);
		fill_with_texture(wall_pix, wall_tex, corner_dist, &dt.mlx.img);
		fill_with_color(floor_pix, dt.tex.floor, &dt.mlx.img);
	}
}
