/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunyoo <hyunyoo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/07 16:01:25 by hyunyoo           #+#    #+#             */
/*   Updated: 2021/02/05 19:20:35 by hyunyoo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <math.h>
# include "../mlx/mlx.h"
# include "get_next_line/get_next_line.h"
# include "../Libft/libft.h"
# define TRUE 1
# define FALSE 0
# define FOV_ANGLE 1.047197551
# define TILE_SIZE 12

# define X_EVENT_KEY_PRESS		2
# define X_EVENT_KEY_RELEASE	3
# define X_EVENT_KEY_EXIT		17

# define KEY_ESC		53
# define KEY_Q			12
# define KEY_W			13
# define KEY_E			14
# define KEY_R			15
# define KEY_A			0
# define KEY_S			1
# define KEY_D			2
# define KEY_LEFT_ARROW 123
# define KEY_RIGHT_ARROW 124
# define Q_SIZE 10000

typedef int		t_bool;

typedef struct	s_img
{
	void		*img_ptr;
	int			*data;
	int			size_l;
	int			bpp;
	int			endian;
}				t_img;

typedef struct	s_sprite
{
	double	x_sp;
	double	y_sp;
	double	dist;
	double	angle;
}				t_sprite;

typedef struct	s_texture
{
	int		*data;
	int		tex_width;
	int		tex_height;
}				t_texture;

typedef	struct	s_map
{
	int				sizex;
	int				sizey;
	char			**map;
	int				m_size_x;
	int				m_size_y;
	t_texture		*no_texture;
	t_texture		*so_texture;
	t_texture		*ea_texture;
	t_texture		*we_texture;
	t_texture		*sprite_texture;
	int				floor_color;
	int				ceiling_color;
	int				sp_cnt;
	t_sprite		*sprites;
	t_img			minimap_img;
	t_img			proj_img;
}				t_map;

typedef struct	s_character
{
	double	pos_x;
	double	pos_y;
	double	pos_z;
	double	degree;
	double	rotation_speed;
	double	moving_speed;
}				t_character;

typedef	struct	s_window
{
	void		*mlx;
	void		*window;
	t_map		*map;
	t_character *charac;
}				t_window;

typedef	struct	s_ray
{
	double		rayangle;
	double		wallhit_x;
	double		wallhit_y;
	double		distance;
	double		wallst;

	t_bool		washitvert;
	t_bool		israyfacingdown;
	t_bool		israyfacingup;

	t_bool		israyfacingright;
	t_bool		israyfacingleft;
	t_texture	*texture;
}				t_ray;

typedef struct	s_cast
{
	double	x_inter;
	double	y_inter;
	double	x_step;
	double	y_step;

	double	distance;
	double	horzhit_x;
	double	horzhit_y;
	double	verthit_x;
	double	verthit_y;

	t_bool	checkhitvert;
	t_bool	checkhithorz;
}				t_cast;

typedef struct	s_vector
{
	double	x_pos;
	double	y_pos;
}				t_vector;

typedef struct	s_queue {
	t_vector	*items[Q_SIZE];
	int			front;
	int			rear;
	int			*vst;
}				t_queue;

int				get_screen_size(void *mlx, int *sizex, int *sizey);
char			*read_file(const char *path);
void			parse_cub_file(t_window *window, char *file_path);
void			check_resolution(t_map **map, char *str, int idx);
void			str_free(char **str_arr);
char			**convert_to_hexstr(char **rgb);
void			get_array_size(t_map **mapinfo, char **map, int str_idx);
void			parse_map(char **m, int str_idx, t_map *map);
t_character		*inst_character(int i, int j, char temp);
t_character		*parse_character(char **map, int str_idx);
t_ray			**raycast(t_map *map, t_character *charac);
void			draw(t_window *window);
void			draw_line(t_img *img, t_vector st_vec, t_vector en_vec);
void			*img_init(t_window *window, int width, int height);
double			normalize_angle(double rayangle);
t_bool			render_walls(t_map *map, t_character *chrac, t_ray **rays);
void			load_image(t_window *win, t_texture **texture,
char *path, t_img *img);
void			draw_tex(t_map *map, double x1, double tex_x, t_ray *ray);
void			init_map(t_window *window);
char			**init_worldmap(int size_x, int size_y);
char			*read_file(const char *path);
t_cast			*init_cast_info();
double			normalize_angle(double rayangle);
double			getdist(const t_character *charac, double pos_x, double pos_y);
t_bool			check_wall(t_map *map, double pos_x, double pos_y);
void			render_texture(t_map *map, t_character *cha,
t_ray *ray, int rayidx);
t_ray			*init_ray(double rayangle);
int				getcolldir(t_map *map, t_ray *ray, t_texture **data);
void			bmp_mode(t_window *window, char *path);
void			print_error(char *msg);
void			check_parse_f(t_map *map, char **color);
void			check_parse_c(t_map *map, char **color);
void			draw_skyceil(t_map *map);
void			parse_sprites(char **m, int str_idx, t_map *map);
void			getangle(t_character *charac, t_sprite *sprite);
void			draw_sprite(t_character *cha, t_map *map);
void			cast(t_map *map, t_character *charac, t_ray *ray);
void			bfs(t_map *map, char **graph, t_vector *vec);
void			init_vector(t_vector *vector, double x, double y);
void			ini_vec2(t_vector **vector, double x, double y);
int				isempty(t_queue *q);
t_queue			*create_queue(t_map *map);
void			enqueue(t_queue *q, t_vector *pos);
t_vector		*dequeue(t_queue *q);
void			bfs(t_map *map, char **graph, t_vector *vec);
double			getbetweenangle(double first, double second);
void			parse_info(t_window *window, char **split_str, int *str_idx);
void			check_cub_file(t_window *win, t_map **map, char *str, int idx);
void			sort_sprites(t_map *map);
void			draw_spr(t_map *map, int x1, double spr_x, double tex_size_h);
void			parse_sprites(char **m, int str_idx, t_map *map);
void			disable_sprite(t_map *map, int grid_y, int grid_x);
t_bool			check_movable(t_map *map, t_character *cha, double next_x,
double next_y);
int				move_character(int key, t_window *win);
t_bool			key_ws(int key, t_window *win);
t_bool			key_ad(int key, t_window *win);
int				screen_exit(void);
void			draw_ray(t_img *img, t_character *cha, double x2,
double y2);
#endif
