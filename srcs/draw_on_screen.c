/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_on_screen.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lethomas <lethomas@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 09:51:47 by lethomas          #+#    #+#             */
/*   Updated: 2024/04/22 14:38:38 by lethomas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	img_swap_line_col(t_img img)
{
	int	temp;
	int	col_start;	
	int	i;
	int	j;

	col_start = 1;
	i = 0;
	while (i < WIN_SIZE_X)
	{
		j = col_start;
		while (j < WIN_SIZE_Y)
		{
			temp = *(int *)(img.addr + i * img.bit_per_pix / 8 + j * img.line_len); 
			*(int *)(img.addr + i * img.bit_per_pix / 8 + j * img.line_len) = 
				*(int *)(img.addr + j * img.bit_per_pix / 8 + i * img.line_len);
			*(int *)(img.addr + j * img.bit_per_pix / 8 + i * img.line_len) = temp;
			j++;
		}
			i++;
		col_start++;
	}
}

static double	get_corner_distance(t_vector pos, t_vector ray,
	double wall_dist, int wall_dir)
{
	t_vector	hit_pos;

	hit_pos = (t_vector){pos.x + wall_dist * ray.x, pos.y + wall_dist * ray.y};
	if (wall_dir == NORTH)
		return (1 - hit_pos.x + (int)hit_pos.x);
	else if (wall_dir == EAST)
		return (hit_pos.y - (int)hit_pos.y);
	else if (wall_dir == SOUTH)
		return (hit_pos.x - (int)hit_pos.x);
	else
		return (1 - hit_pos.y + (int)hit_pos.y);
}

static void fill_vertical_line(t_data dt, t_vector ray, int vertical_line_nb)
{
	double	wall_dist;
	double	corner_dist;
	int		wall_dir;

	wall_dist = get_wall_distance(dt, ray, &wall_dir);
	corner_dist = get_corner_distance(dt.pl.pos, ray, wall_dist, wall_dir);
	wall_dist = wall_dist * (dt.pl.dir.x * ray.x + dt.pl.dir.y * ray.y);
	dt.mlx.img.addr += vertical_line_nb * dt.mlx.img.line_len;
	fill_img(dt, wall_dist, wall_dir, corner_dist);
}

void	draw_on_screen(t_data dt)
{
	int			i;
	t_vector	cam;
	t_vector	cam_step;
	t_vector	ray;

	i = 0;
	cam = vec_assignation(-dt.pl.dir.y * tan(FOV_X * 0.5),
			dt.pl.dir.x * tan(FOV_X * 0.5));
	cam_step = vec_assignation(cam.x * 2.0 / (WIN_SIZE_X - 1),
			cam.y * 2.0 / (WIN_SIZE_X - 1));
	while (i < WIN_SIZE_X)
	{
		ray = vec_assignation(dt.pl.dir.x + cam.x, dt.pl.dir.y + cam.y);
		ray = vec_normalization(ray);
		cam = vec_assignation(cam.x - cam_step.x, cam.y - cam_step.y);
		fill_vertical_line(dt, ray , i);
		i += PIXEL_SIZE;
	}
	img_swap_line_col(dt.mlx.img); //a de l importance ??
	mlx_put_image_to_window(dt.mlx.ptr, dt.mlx.win, dt.mlx.img.tab, 0, 0); //syscall failure checking
}
