/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lethomas <lethomas@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 17:09:27 by lethomas          #+#    #+#             */
/*   Updated: 2024/08/01 15:21:22 by lethomas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include <mlx.h>
# include <fcntl.h>

# include "../libft/includes/libft.h"

# define CONTINUE_SUCCESS 0
# define STOP_FAILURE 1

# define WIN_SIZE_X 1000
# define WIN_SIZE_Y 1000

# define FOV_X 1.57
# define FOV_Y 1.57

# define PLAYER_HEIGHT 1.0
# define WALL_HEIGHT 2.0

# define ROTATE_STEP 0.2
# define TRANSLATION_STEP 0.1

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
# define ON_DESTROY 17

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
void		fill_with_texture(int pixel_nb[2], t_img tex, double corner_dist,
				t_img *img);

int			on_destroy_routine(void *data);
int			key_routine(int key_code, void *void_dt);
void		free_tab(int **tab);

t_vector	vec_assignation(double x, double y);
t_vector	vec_normalization(t_vector vec_to_norm);
t_vector	vec_rotate(t_vector vec_to_rot, double rot_step);

int			init_textures(t_data *dt, int fd);
char		*get_next_true_line(int fd, t_bool trim);
void		ft_free_split(char **split);
int			init_colors_floor_ceiling(t_data *dt, int fd);
int			init_map_and_player(t_data *dt, int fd);
void		*ft_realloc(void *ptr, size_t size, int free_ptr);
int			get_map_x(t_list *map);
int			ft_normalize_map(t_list *map, int map_len);
void		ft_skip_whitespaces(int fd, char **line);
void		set_img_to_null(t_data *dt);
int			get_rgb_from_line(char *line);
int			line_is_cringe(char *line);
int			ft_is_map_playable(t_data *dt, int map_x, int map_y);

#endif
