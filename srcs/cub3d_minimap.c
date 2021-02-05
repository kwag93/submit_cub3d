/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_minimap.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunyoo <hyunyoo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 15:48:48 by hyunyoo           #+#    #+#             */
/*   Updated: 2021/02/05 17:53:17 by hyunyoo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	draw_line(t_img *img, t_vector st_vec, t_vector en_vec)
{
	double	delta_x;
	double	delta_y;
	double	step;

	delta_x = en_vec.x_pos - st_vec.x_pos;
	delta_y = en_vec.y_pos - st_vec.y_pos;
	step = (fabs(delta_x) > fabs(delta_y)) ? fabs(delta_x) : fabs(delta_y);
	delta_x /= step;
	delta_y /= step;
	while (fabs(en_vec.x_pos - st_vec.x_pos) >= fabs(delta_x + 0.00000001) ||
	fabs(en_vec.y_pos - st_vec.y_pos) >= fabs(delta_y + 0.00000001))
	{
		img->data[((int)floor(st_vec.y_pos) * img->size_l / 4) +
		(int)floor(st_vec.x_pos)] = 0xb3b3b3;
		st_vec.x_pos += delta_x;
		st_vec.y_pos += delta_y;
	}
	img->data[((int)floor(st_vec.y_pos) * img->size_l / 4) +
	(int)floor(st_vec.x_pos)] = 0xb3b3b3;
}

void	draw_lines(t_map *map)
{
	int			i;
	t_vector	st;
	t_vector	en;

	i = 0;
	while (i < map->m_size_x)
	{
		init_vector(&st, i * TILE_SIZE, 0);
		init_vector(&en, (i++) * TILE_SIZE, map->m_size_y * TILE_SIZE);
		draw_line(&map->minimap_img, st, en);
	}
	init_vector(&st, i * TILE_SIZE - 1, 0);
	init_vector(&en, i * TILE_SIZE - 1, map->m_size_y * TILE_SIZE);
	draw_line(&map->minimap_img, st, en);
	i = 0;
	while (i < map->m_size_y)
	{
		init_vector(&st, 0, i * TILE_SIZE);
		init_vector(&en, map->m_size_x * TILE_SIZE, (i++) * TILE_SIZE);
		draw_line(&map->minimap_img, st, en);
	}
	init_vector(&st, 0, i * TILE_SIZE - 1);
	init_vector(&en, map->m_size_x * TILE_SIZE, i * TILE_SIZE - 1);
	draw_line(&map->minimap_img, st, en);
}

void	draw_rectangle(t_map *map, int x, int y, int color)
{
	int i;
	int j;

	x *= TILE_SIZE;
	y *= TILE_SIZE;
	i = 0;
	while (i < TILE_SIZE)
	{
		j = 0;
		while (j < TILE_SIZE)
		{
			map->minimap_img.data[((y + i) * map->minimap_img.size_l / 4) +
			x + j] = color;
			j++;
		}
		i++;
	}
}

void	draw_rectangles(t_map *map)
{
	int		i;
	int		j;

	i = 0;
	while (i < map->m_size_y)
	{
		j = 0;
		while (j < map->m_size_x)
		{
			if (map->map[i][j] == '1')
				draw_rectangle(map, j, i, 16777215);
			else if (map->map[i][j] == '2')
				draw_rectangle(map, j, i, 16711680);
			j++;
		}
		i++;
	}
}

void	draw(t_window *win)
{
	draw_rectangles(win->map);
	draw_lines(win->map);
	mlx_put_image_to_window(win->mlx, win->window,
	win->map->proj_img.img_ptr, 0, 0);
	mlx_put_image_to_window(win->mlx, win->window,
	win->map->minimap_img.img_ptr, 0, 0);
}
