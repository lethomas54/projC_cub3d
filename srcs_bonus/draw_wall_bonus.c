/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_wall_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lethomas <lethomas@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 11:37:41 by lethomas          #+#    #+#             */
/*   Updated: 2024/04/26 15:32:19 by lethomas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/cub3d_bonus.h"

static int	set_pixel_nb(double wall_dist, int *wall_pix, int *ceiling_pix,
	double player_height)
{
	int		floor_pix;
	
	floor_pix = WIN_SIZE_Y * 0.5
		* (1.0 - player_height / (wall_dist * tan(FOV_Y * 0.5)));
	if (floor_pix < 0)
		floor_pix = 0;
	wall_pix[0] = WIN_SIZE_Y * 0.5 - floor_pix;
	wall_pix[1] = WIN_SIZE_Y * 0.5
		* (WALL_HEIGHT - player_height) / (wall_dist * tan(FOV_Y * 0.5));
	*ceiling_pix = WIN_SIZE_Y * 0.5 - wall_pix[1];
	if (*ceiling_pix < 0)
		*ceiling_pix = 0;
	return (floor_pix);
}

static void	fill_img(t_data dt, double wall_dist, int wall_dir,
	double corner_dist)
{
	int		floor_pix;
	int		wall_pix[2];
	int		ceiling_pix;
	t_img	wall_tex;

	floor_pix = set_pixel_nb(wall_dist, wall_pix, &ceiling_pix, dt.pl.height);
	if (wall_dir == NORTH)
		wall_tex = dt.tex.north;
	else if (wall_dir == EAST)
		wall_tex = dt.tex.east;
	else if (wall_dir == SOUTH)
		wall_tex = dt.tex.south;
	else
		wall_tex = dt.tex.west;
	dt.mlx.img.addr += ceiling_pix * dt.mlx.img.line_len;
	fill_wall_col_with_texture(wall_pix, wall_tex, corner_dist,
		&dt);
	dt.mlx.img.addr += floor_pix * dt.mlx.img.line_len;
}

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

void	fill_img_col_for_wall(t_data dt, t_vector ray, int vertical_line_nb)
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

void	draw_wall(t_data dt, int start_col, int end_col)
{
	int			i;
	t_vector	cam;
	t_vector	cam_step;
	t_vector	ray;

	i = start_col;
	cam = vec_assignation(-dt.pl.dir.y * tan(FOV_X * 0.5),
			dt.pl.dir.x * tan(FOV_X * 0.5));
	cam_step = vec_assignation(cam.x * 2.0 / (WIN_SIZE_X - 1),
			cam.y * 2.0 / (WIN_SIZE_X - 1));
	ray = vec_assignation(dt.pl.dir.x + cam.x - i * cam_step.x,
			dt.pl.dir.y + cam.y - i * cam_step.y);
	while (i < end_col)
	{
		fill_img_col_for_wall(dt, vec_normalization(ray), i);
		ray = vec_assignation(ray.x - cam_step.x, ray.y - cam_step.y);
		i++;
	}
}
