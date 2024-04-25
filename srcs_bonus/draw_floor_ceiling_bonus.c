/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_floor_ceiling_bonus.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lethomas <lethomas@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 13:22:24 by lethomas          #+#    #+#             */
/*   Updated: 2024/04/25 11:54:46 by lethomas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/cub3d_bonus.h"

static void	add_pixel(char *img_addr, t_img tex_img, double tex_col_pct,
	double tex_line_pct)
{
	*(unsigned int *)img_addr = *(unsigned int *)(tex_img.addr
			+ (int)(tex_col_pct * tex_img.def_x) * tex_img.bit_per_pix / 8
			+ (int)(tex_line_pct * tex_img.def_y) * tex_img.line_len);
}

static void	fill_img_line_for_floor_ceil(t_data dt, t_vector floor_vec,
	t_vector floor_step, int horizontal_line_nb)
{
	int		j;
	double	tex_line_pct;
	double	tex_col_pct;
	char	*img_addr_floor;

	j = 0;
	dt.mlx.img.addr += dt.mlx.img.line_len * horizontal_line_nb;
	img_addr_floor = dt.mlx.img.addr
		+ (WIN_SIZE_Y - 1 - 2 * horizontal_line_nb) * dt.mlx.img.line_len;
	while (j < WIN_SIZE_X)
	{
		tex_line_pct = (floor_vec.y - floor(floor_vec.y));
		tex_col_pct = (floor_vec.x - floor(floor_vec.x));
		add_pixel(dt.mlx.img.addr, dt.tex.ceiling, tex_col_pct, tex_line_pct);
		add_pixel(img_addr_floor, dt.tex.floor, tex_col_pct, tex_line_pct);
		dt.mlx.img.addr += dt.mlx.img.bit_per_pix / 8;
		img_addr_floor += dt.mlx.img.bit_per_pix / 8;
		floor_vec = vec_assignation(floor_vec.x - floor_step.x,
				floor_vec.y - floor_step.y);
		j += 1;
	}
}

void	draw_floor_ceiling(t_data dt, int start_line, int end_line)
{
	double		floor_dist;
	t_vector	floor_vec;
	t_vector	floor_step;
	t_vector	cam_step;
	t_vector	ray;

	ray = vec_assignation(dt.pl.dir.x + -dt.pl.dir.y * tan(FOV_X * 0.5),
			dt.pl.dir.y + dt.pl.dir.x * tan(FOV_X * 0.5));
	cam_step = vec_assignation(-dt.pl.dir.y * tan(FOV_X * 0.5)
			* 2.0 / (WIN_SIZE_X - 1),
			dt.pl.dir.x * tan(FOV_X * 0.5) * 2.0 / (WIN_SIZE_X - 1));
	while (start_line < end_line)
	{
		floor_dist = PLAYER_HEIGHT * (WIN_SIZE_Y - 1) * 0.5
			/ (tan(FOV_Y * 0.5) * fabs((WIN_SIZE_Y - 1) * 0.5 - start_line));
		floor_vec = vec_assignation(dt.pl.pos.x + ray.x * floor_dist,
				dt.pl.pos.y + ray.y * floor_dist);
		floor_step = vec_assignation(cam_step.x * floor_dist,
				cam_step.y * floor_dist);
		fill_img_line_for_floor_ceil(dt, floor_vec, floor_step, start_line);
		start_line++;
	}
}
