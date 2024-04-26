/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_sprite_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lethomas <lethomas@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 11:11:53 by lethomas          #+#    #+#             */
/*   Updated: 2024/04/26 15:19:19 by lethomas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/cub3d_bonus.h"

static int	get_spritesheet_nb(char *dir_path, int *sheet_nb)
{
	DIR	*directory;

	errno = 0;
	*sheet_nb = 0;
	directory = opendir(dir_path);
	if (directory == NULL)
	{
		ft_putendl_fd("Error spritesheet directory opening", 2);
		return (STOP_FAILURE);
	}
	while (readdir(directory) != NULL)
		(*sheet_nb)++;
	if (closedir(directory))
		return (STOP_FAILURE);
	(*sheet_nb) -= 2;
	if (*sheet_nb < 0)
		return (ft_putendl_fd("Error empty spritesheet", 2), STOP_FAILURE);
	return (errno != 0);
}
//verifier directement si commence par un . (pour eliminer les fichiers caches)

static int	open_xpm_file(void *mlx_ptr, t_img *img, char *path)
{
	img->ptr = mlx_xpm_file_to_image(mlx_ptr, path, &img->def_x, &img->def_y);
	if (img->ptr == NULL)
	{
		ft_putendl_fd("Error spritesheet file opening", 2);
		return (STOP_FAILURE);
	}
	img->addr = mlx_get_data_addr(img->ptr, &img->bit_per_pix, &img->line_len,
			&img->endian);
	if (img->addr == NULL)
		return (STOP_FAILURE);
	return (CONTINUE_SUCCESS);
}

static int	create_file_path(char *dir_path, int sheet_index, char **file_path)
{
	*file_path = ft_itoa(sheet_index);
	if (*file_path == NULL)
		return (STOP_FAILURE);
	*file_path = ft_strjoin(*file_path, ".xpm", true, false);
	if (*file_path == NULL)
		return (STOP_FAILURE);
	*file_path = ft_strjoin("/", *file_path, false, true);
	if (*file_path == NULL)
		return (STOP_FAILURE);
	*file_path = ft_strjoin(dir_path, *file_path, false, true);
	if (*file_path == NULL)
		return (STOP_FAILURE);
	return (CONTINUE_SUCCESS);
}

static int	open_sprite(void *mlx_ptr, char *dir_path, t_sprite *sprite,
	time_t time_to_switch)
{
	int		i;
	char	*file_path;

	i = 0;
	sprite->to_switch = time_to_switch;
	if (get_spritesheet_nb(dir_path, &sprite->nb))
		return (STOP_FAILURE);
	sprite->sheet = (t_img *)ft_calloc(sprite->nb, sizeof(t_img));
	if (sprite->sheet == NULL)
		return (STOP_FAILURE);
	while (i < sprite->nb)
	{
		if (create_file_path(dir_path, i + 1, &file_path))
			return (STOP_FAILURE);
		if (open_xpm_file(mlx_ptr, sprite->sheet + i++, file_path))
			return (STOP_FAILURE);
	}
	return (CONTINUE_SUCCESS);
}

int	set_sprite(t_data *dt)
{
	if (open_sprite(dt->mlx.ptr, "./sprite/gun", &dt->spr.weapon, 75))
		return (STOP_FAILURE);
	return (CONTINUE_SUCCESS);
}
