/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lethomas <lethomas@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 17:09:27 by lethomas          #+#    #+#             */
/*   Updated: 2024/04/25 22:03:41 by lethomas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include "../mlx/mlx.h"
# include <pthread.h>
# include <sys/time.h>

# include "../libft/includes/libft.h"

# define CONTINUE_SUCCESS 0
# define STOP_FAILURE 1

# define WIN_SIZE_X 1000
# define WIN_SIZE_Y 1000

# define PLAYER_POS_X 1.5
# define PLAYER_POS_Y 1.5
# define PLAYER_DIR_X 0
# define PLAYER_DIR_Y 1

# define FOV_X 1.57
# define FOV_Y 1.57
//adater les FOV entre eux selon le rapport entre les cotes de la fenetre ?

# define PLAYER_HEIGHT 1.0
# define WALL_HEIGHT 2.0 //doit etre strictement superieur a la taille du joueur

# define ROTATE_STEP 0.02
# define TRANSLATION_STEP 0.05

# define HIT_BOX 0.1

# define NORTH 0
# define SOUTH 1
# define WEST 2
# define EAST 3

# define ESCAPE 53
# define ARROW_LEFT 123
# define ARROW_RIGHT 124
# define A 0
# define S 1
# define D 2
# define W 13

# define ON_KEY_DOWN 2
# define ON_KEY_UP 3
# define ON_DESTROY 17

# define NB_THREAD 8

# define WEAPON_PCT_X 0.2

typedef struct s_img
{
	void		*ptr;
	char		*addr;
	int			bit_per_pix;
	int			line_len;
	int			endian;
	int			def_x;
	int			def_y;
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

typedef struct s_sprite
{
	t_img		*sprite;
	int			nb;
	int			index;
	time_t		time;
	int			def_x;
	int			def_y;
}	t_sprite;

typedef struct s_texture
{
	t_sprite	gun;
	t_img		floor;
	t_img		ceiling;
	t_img		north;
	t_img		east;
	t_img		south;
	t_img		west;
}	t_texture;

typedef struct s_move
{
	int			paral;
	int			perp;
	int			rot;
}	t_move;

typedef struct s_data
{
	t_mlx		mlx;
	t_player	pl;
	t_texture	tex;
	int			**map;
	t_move		move;
	time_t		last_draw;
}	t_data;

typedef struct s_thread_arg
{
	t_data	data;
	int		index;
}	t_thread_arg;

int			draw_on_screen(t_data dt);
void		draw_floor_ceiling(t_data dt, int start_line, int end_line);
void		draw_wall(t_data dt, int start_col, int end_col);
double		get_wall_distance(t_data dt, t_vector ray, int *wall_dir);
void		fill_wall_col_with_texture(int pixel_nb[2], t_img tex,
				double corner_dist, t_img *img);

int			on_destroy_routine(void *data);
int			key_down_routine(int key_code, void *void_dt);
int			key_up_routine(int key_code, void *void_dt);
int			loop_routine(void *void_dt);

void		set_new_pos(t_data *dt);
void		set_new_dir(t_data *dt);

int			get_time(time_t *time_int);
void		free_tab(int **tab);
t_vector	vec_assignation(double x, double y);
t_vector	vec_normalization(t_vector vec_to_norm);
t_vector	vec_rotate(t_vector vec_to_rot, double rot_step);

#endif
