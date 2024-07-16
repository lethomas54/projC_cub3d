/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_on_screen.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npremont <npremont@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 09:51:47 by lethomas          #+#    #+#             */
/*   Updated: 2024/07/16 14:37:56 by npremont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static double	get_corner_distance(t_vector pos, t_vector ray,
	double wall_dist, int wall_dir)
{
	t_vector	hit_pos;

	hit_pos = (t_vector){pos.x + wall_dist * ray.x, pos.y + wall_dist * ray.y};
	if (wall_dir == NORTH)
		return (1 - hit_pos.y + (int)hit_pos.y);
	else if (wall_dir == EAST)
		return (1 - hit_pos.x + (int)hit_pos.x);
	else if (wall_dir == SOUTH)
		return (hit_pos.y - (int)hit_pos.y);
	else
		return (hit_pos.x - (int)hit_pos.x);
}

static void	fill_vertical_line(t_data dt, t_vector ray, int vertical_line_nb)
{
	double	wall_dist;
	double	corner_dist;
	int		wall_dir;

	wall_dist = get_wall_distance(dt, ray, &wall_dir);
	corner_dist = get_corner_distance(dt.pl.pos, ray, wall_dist, wall_dir);
	wall_dist = wall_dist * (dt.pl.dir.x * ray.x + dt.pl.dir.y * ray.y);
	dt.mlx.img.addr += vertical_line_nb * dt.mlx.img.bit_per_pix / 8;
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
		fill_vertical_line(dt, ray, i);
		i += PIXEL_SIZE;
	}
	mlx_put_image_to_window(dt.mlx.ptr, dt.mlx.win, dt.mlx.img.ptr, 0, 0);
}
