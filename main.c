/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkwag <bkwag@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/07 16:01:22 by hyunyoo           #+#    #+#             */
/*   Updated: 2021/02/05 16:07:46 by bkwag            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"
#include <stdio.h>
#define WIN_WIDTH 800
#define WIN_HEIGHT 600
#define IMG_WIDTH 800
#define IMG_HEIGHT 600

void		set_window_size(t_window *win, int x, int y)
{
	int max_size_x;
	int max_size_y;

	if (!win || !win->mlx || x < 0 || y < 0)
		print_error("Window Size Error");
	mlx_get_screen_size(win->mlx, &max_size_x, &max_size_y);
	win->map->sizex = x > max_size_x ? max_size_x : x;
	win->map->sizey = y > max_size_y ? max_size_y : y;
}

int			rotate_character(int key, t_window *win)
{
	if (key == KEY_LEFT_ARROW)
	{
		win->charac->degree -= win->charac->rotation_speed;
	}
	else if (key == KEY_RIGHT_ARROW)
	{
		win->charac->degree += win->charac->rotation_speed;
	}
	win->charac->degree = normalize_angle(win->charac->degree);
	return (0);
}

int			key_press(int key, t_window *win)
{
	if (key == KEY_W || key == KEY_A || key == KEY_S || key == KEY_D)
		move_character(key, win);
	else if (key == KEY_LEFT_ARROW || key == KEY_RIGHT_ARROW)
		rotate_character(key, win);
	else if (key == KEY_ESC)
		exit(0);
	return (0);
}

int			main_loop(t_window *win)
{
	t_map	*map;
	t_ray	**rays;
	int		i;

	i = 0;
	map = win->map;
	map->minimap_img.img_ptr = img_init(win, map->m_size_x * TILE_SIZE,
	map->m_size_y * TILE_SIZE);
	map->minimap_img.data = (int *)mlx_get_data_addr(map->minimap_img.img_ptr,
	&map->minimap_img.bpp, &map->minimap_img.size_l, &map->minimap_img.endian);
	map->proj_img.img_ptr = img_init(win, map->sizex, map->sizey);
	map->proj_img.data = (int *)mlx_get_data_addr(map->proj_img.img_ptr,
	&map->proj_img.bpp, &map->proj_img.size_l, &map->proj_img.endian);
	draw_skyceil(win->map);
	rays = raycast(win->map, win->charac);
	draw(win);
	draw_sprite(win->charac, map);
	mlx_destroy_image(win->mlx, map->minimap_img.img_ptr);
	mlx_destroy_image(win->mlx, map->proj_img.img_ptr);
	i = 0;
	while (i < map->sizex)
		free(rays[i++]);
	free(rays);
	return (0);
}

int			main(int argc, char **argv)
{
	t_window win;

	if (argc == 2)
	{
		win.mlx = mlx_init();
		parse_cub_file(&win, argv[1]);
		set_window_size(&win, win.map->sizex, win.map->sizey);
		win.window = mlx_new_window(win.mlx, win.map->sizex, win.map->sizey,
		"mlx_project");
		mlx_hook(win.window, X_EVENT_KEY_PRESS, 1, key_press, &win);
		mlx_hook(win.window, X_EVENT_KEY_EXIT, 1L << 5, screen_exit, &win);
		mlx_loop_hook(win.mlx, main_loop, &win);
		mlx_loop(win.mlx);
	}
	else if (argc == 3 && ft_strncmp(argv[2], "--save", 6) == 0)
	{
		win.mlx = mlx_init();
		bmp_mode(&win, argv[1]);
	}
	else if (argc == 1)
		print_error("Not enough argv.");
	else
		print_error("Too many argv coming in.");
	return (0);
}
