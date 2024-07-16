/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_weapon_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lethomas <lethomas@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 12:20:20 by lethomas          #+#    #+#             */
/*   Updated: 2024/04/26 15:19:10 by lethomas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/cub3d_bonus.h"

static unsigned int	get_weapon_pixel_color(t_img wp, int i_wp, int j_b_wp)
{
	return (*(unsigned int *)(wp.addr + i_wp * wp.bit_per_pix / 8 + j_b_wp));
}

static void	add_weapon(t_data dt, t_img wp, int i_max, int j_max)
{
	int		i;
	int		j;
	int		pixel_color;
	double	wp_step_x;
	int		j_b_wp;

	j = 0;
	wp_step_x = (double)(wp.def_x - 1) / (i_max - 1);
	while (j < j_max)
	{
		i = 0;
		j_b_wp = j * (wp.def_y - 1) / (j_max - 1) * wp.line_len;
		while (i < i_max)
		{
			pixel_color
				= get_weapon_pixel_color(wp, (int)(i * wp_step_x), j_b_wp);
			if (!(pixel_color >> 24))
				*(unsigned int *)(dt.mlx.img.addr) = pixel_color;
			dt.mlx.img.addr += dt.mlx.img.bit_per_pix / 8;
			i++;
		}
		dt.mlx.img.addr
			+= dt.mlx.img.line_len - i_max * dt.mlx.img.bit_per_pix / 8;
		j++;
	}
}

static void	add_weapon_sight(t_data dt)
{
	int		i;
	int		j;
	int		max;
	int		color;

	if (dt.spr.weapon.index != 0)
		color = WEAPON_SIGHT_COLOR_ON;
	else
		color = WEAPON_SIGHT_COLOR_OFF;
	max = (int)(WEAPON_SIGHT_PCT_X * WIN_SIZE_X);
	j = max;
	dt.mlx.img.addr
		+= ((int)((WIN_SIZE_X - max) * 0.5)) * dt.mlx.img.bit_per_pix / 8;
	dt.mlx.img.addr += ((int)((WIN_SIZE_Y - max) * 0.5)) * dt.mlx.img.line_len;
	while (j-- != 0)
	{
		i = max;
		while (i-- != 0)
		{
			*(unsigned int *)(dt.mlx.img.addr) = color;
			dt.mlx.img.addr += dt.mlx.img.bit_per_pix / 8;
		}
		dt.mlx.img.addr
			+= dt.mlx.img.line_len - max * dt.mlx.img.bit_per_pix / 8;
	}
}

void	draw_weapon(t_data dt)
{
	int		i_max;
	int		j_max;
	t_img	wp;

	add_weapon_sight(dt);
	wp = dt.spr.weapon.sheet[dt.spr.weapon.index];
	i_max = (int)(WEAPON_PCT_X * WIN_SIZE_X);
	j_max = i_max * wp.def_y / wp.def_x;
	dt.mlx.img.addr
		+= ((int)((WIN_SIZE_X - i_max) * 0.5
				+ WIN_SIZE_X * WEAPON_OFFSET_PCT_X))
		* dt.mlx.img.bit_per_pix / 8;
	dt.mlx.img.addr += (WIN_SIZE_Y - j_max) * dt.mlx.img.line_len;
	add_weapon(dt, wp, i_max, j_max);
}
