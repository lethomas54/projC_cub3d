/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_wall_col_with_texture_bonus.c                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lethomas <lethomas@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 14:28:49 by lethomas          #+#    #+#             */
/*   Updated: 2024/04/26 15:31:51 by lethomas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/cub3d_bonus.h"

static double	get_texture_step(int *wall_pix_above, t_img tex,
	double player_height)
{
	double	tex_step;
	double	tex_ratio;

	tex_ratio = (WIN_SIZE_Y * 0.5 / *wall_pix_above);
	if (tex_ratio > 1.0)
		tex_ratio = 1.0;
	if (*wall_pix_above > WIN_SIZE_Y * 0.5)
		*wall_pix_above = WIN_SIZE_Y * 0.5;
	tex_step = tex_ratio * (tex.def_y - 1)
		* (1.0 - player_height / WALL_HEIGHT) / *wall_pix_above;
	return (tex_step);
}

static double	get_texture_offset(int wall_pix_above, t_img tex,
	double player_height)
{
	double	tex_offset;

	tex_offset = (1.0 - player_height / WALL_HEIGHT
			- (WIN_SIZE_Y * 0.5 / wall_pix_above)
			* (1.0 - player_height / WALL_HEIGHT)) * (tex.def_y - 1);
	if (tex_offset < 0.0)
		tex_offset = 0.0;
	return (tex_offset);
}

void	fill_wall_col_with_texture(int pixel_nb[2], t_img tex, double corner_dist,
	t_data *dt)
{
	int		tex_col;
	double	tex_step;
	double	tex_offset;
	int		i;
	int		pixel_nb_tot;

	i = 0;
	tex_col = (int)(tex.def_x
			* (-floor(corner_dist * tex.def_x / (WALL_HEIGHT * tex.def_y))
				+ corner_dist * tex.def_x / (WALL_HEIGHT * tex.def_y)));
	tex_offset = get_texture_offset(pixel_nb[1], tex, dt->pl.height);
	tex_step = get_texture_step(pixel_nb + 1, tex, dt->pl.height);
	pixel_nb_tot = pixel_nb[0] + pixel_nb[1];
	while (i < pixel_nb_tot)
	{
		*(unsigned int *)dt->mlx.img.addr = *(unsigned int *)(tex.addr
				+ tex_col * tex.bit_per_pix / 8
				+ tex.line_len * (int)(tex_offset + i++ * tex_step));
		dt->mlx.img.addr += dt->mlx.img.line_len;
	}
}
