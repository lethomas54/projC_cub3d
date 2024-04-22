/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lethomas <lethomas@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 17:09:27 by lethomas          #+#    #+#             */
/*   Updated: 2024/04/22 16:01:19 by lethomas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include <mlx.h>

# include "../libft/includes/libft.h"

# define CONTINUE_SUCCESS 0
# define STOP_FAILURE 1

# define WIN_SIZE_X 1000
# define WIN_SIZE_Y 1000
# define PIXEL_SIZE 1
# define PLAYER_POS_X 1.5
# define PLAYER_POS_Y 1.5
# define PLAYER_DIR_X -1
# define PLAYER_DIR_Y 0
# define FOV_X 1.57
# define FOV_Y 1.57
# define PLAYER_HEIGHT 1.0
# define WALL_HEIGHT 2.0

# define ROTATE_STEP 0.2
# define TRANSLATION_STEP 0.1

# define NORTH 0
# define SOUTH 1
# define WEST 2
# define EAST 3

# define ESCAPE 53
# define ARROW_LEFT 123
# define ARROW_RIGHT 124
# define ARROW_DOWN 125
# define ARROW_UP 126

# define ON_KEY_DOWN 2
# define ON_DESTROY 17

typedef struct s_img
{
	void		*tab;
	char		*addr;
	int			bit_per_pix;
	int			line_len;
	int			endian;
	int			def;
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
	t_img		north;
	t_img		east;
	t_img		south;
	t_img		west;
}	t_texture;

typedef struct s_data
{
	t_mlx		mlx;
	t_player	pl;
	t_texture	tex;
	int			**map;
}	t_data;

void		draw_on_screen(t_data dt);
double		get_wall_distance(t_data dt, t_vector ray, int *wall_dir);
void		fill_img(t_data dt, double wall_dist, int wall_dir,
				double corner_dist);

int			on_destroy_routine(void *data);
int			key_routine(int key_code, void *void_dt);

t_vector	vec_assignation(double x, double y);
t_vector	vec_normalization(t_vector vec_to_norm);
t_vector	vec_rotate(t_vector vec_to_rot, double rot_step);

#endif
