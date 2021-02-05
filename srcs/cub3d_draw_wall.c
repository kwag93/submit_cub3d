/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_draw_wall.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunyoo <hyunyoo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 15:39:14 by hyunyoo           #+#    #+#             */
/*   Updated: 2021/02/05 17:52:22 by hyunyoo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void		draw_tex(t_map *map, double x1, double tex_x, t_ray *ray)
{
	double	pos_y;
	double	target_y;
	double	origin_y;
	int		data_pos;
	int		tex_pos;

	pos_y = (map->sizey - ray->wallst) / 2;
	origin_y = pos_y;
	target_y = ((map->sizey + ray->wallst) / 2);
	while (fabs(pos_y - target_y) >= 1)
	{
		data_pos = ((int)floor(pos_y) * map->proj_img.size_l / 4) +
		(int)floor(x1);
		tex_pos = ray->texture->tex_width * (int)((pos_y - origin_y) *
		(ray->texture->tex_height / ray->wallst))
		+ (int)(tex_x * ray->texture->tex_width);
		if ((pos_y > 0 && pos_y < map->sizey))
			map->proj_img.data[data_pos] = ray->texture->data[tex_pos];
		pos_y += 1;
	}
	if ((pos_y > 0 && pos_y < map->sizey))
		map->proj_img.data[data_pos] = ray->texture->data[tex_pos];
}

void		render_texture(t_map *map, t_character *cha, t_ray *ray, int rayidx)
{
	double	texture_x;
	int		dir;

	ray->wallst = (TILE_SIZE / (ray->distance * cos(ray->rayangle -
	cha->degree))) * ((map->sizex / 2) / tan(FOV_ANGLE / 2));
	ray->wallst = ray->wallst > 4000 ? 4000 : ray->wallst;
	dir = getcolldir(map, ray, &ray->texture);
	texture_x = 0;
	if (dir == 0)
		texture_x = 1 - (ray->wallhit_y / TILE_SIZE -
		(int)(ray->wallhit_y / TILE_SIZE));
	else if (dir == 1)
		texture_x = (ray->wallhit_x / TILE_SIZE -
		(int)(ray->wallhit_x / TILE_SIZE));
	else if (dir == 2)
		texture_x = (ray->wallhit_y / TILE_SIZE -
		(int)(ray->wallhit_y / TILE_SIZE));
	else if (dir == 3)
		texture_x = 1 - ((ray->wallhit_x / TILE_SIZE) -
		(int)(ray->wallhit_x / TILE_SIZE));
	else
		print_error("Wrong direction");
	draw_tex(map, rayidx, texture_x, ray);
}

void		draw_skyceil(t_map *map)
{
	int	x;
	int	y;

	y = 0;
	while (y < map->sizey)
	{
		x = 0;
		while (x < map->sizex)
		{
			map->proj_img.data[(y * map->proj_img.size_l / 4) + x] =
			(y < map->sizey / 2 ? map->ceiling_color : map->floor_color);
			x++;
		}
		y++;
	}
}
