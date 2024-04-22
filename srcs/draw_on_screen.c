/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_on_screen.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lethomas <lethomas@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 09:51:47 by lethomas          #+#    #+#             */
/*   Updated: 2024/04/21 17:09:54 by lethomas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	my_mlx_pixel_put(t_img img, int x, int y, int color)
{
	char	*dst;

	dst = img.addr + (y * img.line_len + x * (img.bit_per_pix / 8));
	*(unsigned int *)dst = color;
}

static void	get_corner_dist(t_vector pos, t_vector ray, double wall_dist,
	int wall_dir)
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

static void	fill_img(t_data dt, double wall_dist,
	int wall_dir, double corner_dist)
{
	int	floor_pix;
	int	wall_pix;
	int	ceiling_pix;
	int	wall_color;

	(void)corner_dist;
	floor_pix = WIN_SIZE_Y * 0.5
		* (1 - PLAYER_HEIGHT / (wall_dist * tan(FOV_Y * 0.5)));
	if (floor_pix < 0)
		floor_pix = 0;
	wall_pix = WIN_SIZE_Y * 0.5 * WALL_HEIGHT / (wall_dist * tan(FOV_Y * 0.5)); //pixelsize has no impact since we dont use texture yet
	ceiling_pix = WIN_SIZE_Y - floor_pix - wall_pix;
	if (ceiling_pix < 0)
		ceiling_pix = 0;
	else if (wall_dir == NORTH)
		wall_color = dt.tex.north;
	else if (wall_dir == EAST)
		wall_color = dt.tex.east;
	else if (wall_dir == SOUTH)
		wall_color = dt.tex.south;
	else
		wall_color = dt.tex.west;
	while (ceiling_pix--)
	{
		*(unsigned int *)dt.mlx.img.addr = dt.tex.ceiling;
		dt.mlx.img.addr += dt.mlx.img.bit_per_pix / 8;
	}
	while (wall_pix--)
	{
		*(unsigned int *)dt.mlx.img.addr = wall_color;
		dt.mlx.img.addr += dt.mlx.img.bit_per_pix / 8;
	}
	while (floor_pix--)
	{
		*(unsigned int *)dt.mlx.img.addr = dt.tex.floor;
		dt.mlx.img.addr += dt.mlx.img.bit_per_pix / 8;
	}
	//COPIER LA LIGNE SUUR les pixelsize suivantes
}

static void set_vertical_line(t_data dt, t_vector ray, int vertical_line_nb)
{
	double	wall_dist;
	double	corner_dist;
	int		wall_dir;

	wall_dist = get_wall_distance(dt, ray, &wall_dir);
	corner_dist = get_corner_distance(dt.pl.pos, ray, wall_dist, wall_dir);
	//avoid_fisheye(&wall_dist);
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
		ray = vec_assignation(dt.pl.dir.x + cam.x, dt.pl.dir.y + cam.y);    //normalisation
		cam = vec_assignation(cam.x - cam_step.x, cam.y - cam_step.y);
		set_vertical_line(dt, ray , i);
		i += PIXEL_SIZE;
	}
	img_swap_line_col(dt.mlx.img.tab); //a de l importance ??
	mlx_put_image_to_window(dt.mlx.ptr, dt.mlx.win, dt.mlx.img.tab, 0, 0); //syscall failure checking
	return (CONTINUE_SUCCESS);
}
