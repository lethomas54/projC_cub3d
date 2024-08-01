/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npremont <npremont@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 17:09:27 by lethomas          #+#    #+#             */
/*   Updated: 2024/08/01 14:35:23 by npremont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_BONUS_H
# define CUB3D_BONUS_H

# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include "../mlx/mlx.h"
# include <pthread.h>
# include <sys/time.h>
# include <dirent.h>
# include <errno.h>
# include <fcntl.h>

# include "../libft/includes/libft.h"

# define CONTINUE_SUCCESS 0
# define STOP_FAILURE 1

# define WIN_SIZE_X 1000
# define WIN_SIZE_Y 1000

# define PLAYER_POS_X 1.5
# define PLAYER_POS_Y 1.5
# define PLAYER_DIR_X 0
# define PLAYER_DIR_Y 1

# define FOV_X 2
# define FOV_Y 2

# define PLAYER_HEIGHT 1.0
# define WALL_HEIGHT 2.0

# define ROTATE_STEP 0.04
# define TRANSLATION_STEP 0.05

# define HIT_BOX 0.1

# define NORTH 0
# define SOUTH 1
# define WEST 2
# define EAST 3

# define ESCAPE 53
# define ARROW_LEFT 123
# define ARROW_RIGHT 124
# define LETTER_A 0
# define LETTER_S 1
# define LETTER_D 2
# define LETTER_W 13
# define SPACE_BAR 49

# define ON_KEY_DOWN 2
# define ON_KEY_UP 3
# define ON_DESTROY 17

# define NB_THREAD 8

# define WEAPON_PCT_X 0.4
# define WEAPON_OFFSET_PCT_X 0.04
# define WEAPON_SIGHT_PCT_X 0.005
# define WEAPON_SIGHT_COLOR_OFF 0x00ff0000
# define WEAPON_SIGHT_COLOR_ON 0x00ffff00

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
	double		height;
	t_bool		has_shot;
}	t_player;

typedef struct s_sprite
{
	t_img		*sheet;
	int			nb;
	int			index;
	time_t		to_switch;
	time_t		last_switch;
}	t_sprite;

typedef struct s_lsprite
{
	t_sprite	weapon;
}	t_lsprite;

typedef struct s_texture
{
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
	t_lsprite	spr;
	int			**map;
	t_move		move;
	time_t		last_draw;
}	t_data;

typedef struct s_thread_arg
{
	t_data	data;
	int		index;
}	t_thread_arg;

int			set_sprite(t_data *dt);

int			draw_on_screen(t_data dt);
void		draw_floor_ceiling(t_data dt, int start_line, int end_line);
void		draw_wall(t_data dt, int start_col, int end_col);
double		get_wall_distance(t_data dt, t_vector ray, int *wall_dir);
void		fill_wall_col_with_texture(int pixel_nb[2], t_img tex,
				double corner_dist, t_data *dt);
void		draw_weapon(t_data dt);

int			on_destroy_routine(void *data);
int			key_down_routine(int key_code, void *void_dt);
int			key_up_routine(int key_code, void *void_dt);
int			loop_routine(void *void_dt);

int			update_spritesheet_index(t_data *dt, time_t time);
void		update_player_data(t_data *dt);

int			get_time(time_t *time_int);
void		free_tab(int **tab);
void		free_exit(int exit_code, t_data dt);

t_vector	vec_assignation(double x, double y);
t_vector	vec_normalization(t_vector vec_to_norm);
t_vector	vec_rotate(t_vector vec_to_rot, double rot_step);

int			init_textures_floor_and_ceiling(t_data *dt);
int			init_textures(t_data *dt, int fd);
void		ft_free_split(char **split);
char		*get_next_true_line(int fd, t_bool trim);
int			init_map_and_player(t_data *dt, int fd);

void		*ft_realloc(void *ptr, size_t size, int free_ptr);
int			get_map_x(t_list *map);
int			ft_normalize_map(t_list *map, int map_len);
void		ft_skip_whitespaces(int fd, char **line);
int			get_texture_image(t_img *img, t_data *dt, char *path);
void		set_img_to_null(t_data *dt);
int			line_is_cringe(char *line);
int			ft_is_map_playable(t_data *dt, int map_x, int map_y);

#endif
