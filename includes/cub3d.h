/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lethomas <lethomas@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 17:09:27 by lethomas          #+#    #+#             */
/*   Updated: 2024/04/21 16:47:59 by lethomas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_STRUCT.H
# define CUB3D_STRUCT.H

#include <stdlib.h>
#include <math.h>

#include "../libft/includes/libft.h"

# define CONTINUE_SUCCESS 0
# define STOP_FAILURE 1

# define WIN_SIZE_X 1000
# define WIN_SIZE_Y 1000
# define PIXEL_SIZE 1
# define PLAYER_POS_X 1
# define PLAYER_POS_Y 1
# define PLAYER_DIR_X 1
# define PLAYER_DIR_Y 0
# define FOV_X 90
# define FOV_Y 90
# define PLAYER_HEIGHT 1
# define WALL_HEIGHT 2

# define NORTH 0
# define SOUTH 1
# define WEST 2
# define EAST 3

typedef struct s_img
{
	void		*tab;
	char		*addr;
	int			bit_per_pix;
	int			line_len;
	int			endian;
}	t_img;

typedef struct s_mlx
{
	void		*ptr;
	void		*win;
	t_img		img;
}	t_mlx;

typedef struct s_vector
{
	double		x;
	double		y;
}	t_vector;

typedef struct s_player
{
	t_vector	pos;
	t_vector	dir;
}	t_player;

typedef struct s_texture
{
	int			floor;
	int			ceiling;
	int			north;
	int			east;
	int			south;
	int			west;
}	t_texture;

typedef struct s_data
{
	t_mlx		mlx;
	t_player	pl;
	t_texture	tex;
	int			**map;
}	t_data;

t_vector	vec_assignation(double x, double y);

void		draw_on_screen(t_data dt);
double		get_wall_distance(t_data dt, t_vector ray, int *wall_dir);

#endif

