/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_sprite.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunyoo <hyunyoo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 16:23:04 by hyunyoo           #+#    #+#             */
/*   Updated: 2021/02/05 19:06:10 by hyunyoo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	ray_left(t_map *map, t_character *cha, t_sprite sprite, int middle_x)
{
	int		i;
	t_ray	*ray;
	double	rayangle;
	double	tex_size;
	double	spr_x;

	tex_size = (8 / (sprite.dist * cos(sprite.angle - cha->degree))
	* ((map->sizex / 2) / tan(FOV_ANGLE / 2)));
	i = middle_x;
	tex_size = tex_size > 1000 ? 1000 : tex_size;
	rayangle = sprite.angle;
	while (i > middle_x - tex_size / 2)
	{
		ray = init_ray(rayangle);
		cast(map, cha, ray);
		spr_x = ((i - (middle_x - tex_size / 2)) / tex_size);
		if (i > 0 && i < map->sizex)
		{
			if (ray->distance > (sprite.dist / cos(sprite.angle - rayangle)))
				draw_spr(map, i, spr_x, tex_size);
		}
		rayangle -= FOV_ANGLE / (map->sizex);
		i--;
		free(ray);
	}
}

void	ray_right(t_map *map, t_character *cha, t_sprite sprite, int middle_x)
{
	int		i;
	t_ray	*ray;
	double	rayangle;
	double	tex_size;
	double	spr_x;

	tex_size = (8 / (sprite.dist * cos(sprite.angle - cha->degree))
	* ((map->sizex / 2) / tan(FOV_ANGLE / 2)));
	i = middle_x;
	rayangle = sprite.angle;
	tex_size = tex_size > 1000 ? 1000 : tex_size;
	while (i < middle_x + tex_size / 2)
	{
		ray = init_ray(rayangle);
		cast(map, cha, ray);
		spr_x = ((i - (middle_x - tex_size / 2)) / tex_size);
		if (i > 0 && i < map->sizex)
		{
			if (ray->distance > (sprite.dist / cos(rayangle - sprite.angle)))
				draw_spr(map, i, spr_x, tex_size);
		}
		rayangle += FOV_ANGLE / (map->sizex);
		i++;
		free(ray);
	}
}

void	init_ray_sprite(t_map *map, t_character *cha, t_sprite sprite)
{
	int		middle_x;

	middle_x = map->sizex * (getbetweenangle(sprite.angle,
	normalize_angle(cha->degree - (FOV_ANGLE) / 2)) / (FOV_ANGLE));
	ray_left(map, cha, sprite, middle_x);
	ray_right(map, cha, sprite, middle_x);
}

void	draw_sprite(t_character *cha, t_map *map)
{
	int i;

	i = 0;
	while (i < map->sp_cnt)
		getangle(cha, &map->sprites[i++]);
	sort_sprites(map);
	i = 0;
	while (i < map->sp_cnt)
	{
		if (map->sprites[i].x_sp >= 0 && map->sprites[i].y_sp >= 0)
			init_ray_sprite(map, cha, map->sprites[i]);
		i++;
	}
}

void	parse_sprites(char **m, int str_idx, t_map *map)
{
	int		sp_idx;
	int		i;
	int		j;
	char	temp;

	i = 0;
	sp_idx = 0;
	while (m[str_idx + i])
	{
		j = 0;
		while (m[str_idx + i][j])
		{
			temp = m[str_idx + i][j];
			if (temp == '2')
			{
				map->sprites[sp_idx].x_sp = (j + 0.5) * TILE_SIZE;
				map->sprites[sp_idx++].y_sp = (i + 0.5) * TILE_SIZE;
			}
			j++;
		}
		i++;
	}
}
