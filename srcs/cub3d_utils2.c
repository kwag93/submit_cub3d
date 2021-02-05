/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunyoo <hyunyoo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/23 19:36:03 by hyunyoo           #+#    #+#             */
/*   Updated: 2021/02/05 19:05:32 by hyunyoo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

double		getbetweenangle(double first, double second)
{
	double result;

	result = first - second;
	result = result < -M_PI ? result + 2 * M_PI : result;
	result = result > M_PI ? result - 2 * M_PI : result;
	return (result);
}

void		getangle(t_character *charac, t_sprite *sprite)
{
	sprite->dist = getdist(charac, sprite->x_sp, sprite->y_sp);
	sprite->angle = normalize_angle(atan2f((sprite->y_sp - charac->pos_y),
	sprite->x_sp - charac->pos_x));
}

void		parse_info(t_window *window, char **split_str, int *str_idx)
{
	int i;

	i = 0;
	while (i < 8)
	{
		if (ft_strlen(split_str[*str_idx]) == 0)
		{
			*str_idx += 1;
			continue;
		}
		check_cub_file(window, &(window->map), split_str[(*str_idx)++], i);
		i++;
	}
	get_array_size(&window->map, split_str, *str_idx);
}

void		sort_sprites(t_map *map)
{
	int				i;
	int				j;
	int				max;
	t_sprite		temp;

	i = 0;
	max = 0;
	while (i < map->sp_cnt - 1)
	{
		max = i;
		j = i + 1;
		while (j < map->sp_cnt)
		{
			if (map->sprites[j].dist > map->sprites[i].dist)
				max = j;
			j++;
		}
		if (i != max)
		{
			temp = map->sprites[i];
			map->sprites[i] = map->sprites[max];
			map->sprites[max] = temp;
		}
		i++;
	}
}

void		draw_spr(t_map *map, int x1, double spr_x, double tex_size_h)
{
	double	pos_y;
	double	target_y;
	double	origin_y;
	int		data_pos;
	int		tex_pos;

	pos_y = (map->sizey - tex_size_h) / 2;
	origin_y = pos_y;
	target_y = ((map->sizey + tex_size_h) / 2);
	while (fabs(pos_y - target_y) >= 1)
	{
		data_pos = ((int)floor(pos_y) * map->proj_img.size_l / 4) + x1;
		tex_pos = map->sprite_texture->tex_width * (int)((pos_y - origin_y) *
		(map->sprite_texture->tex_height / tex_size_h)) +
		(int)(spr_x * map->sprite_texture->tex_width);
		if ((pos_y > 0 && pos_y < map->sizey))
			map->proj_img.data[data_pos] = map->sprite_texture->data[tex_pos];
		pos_y += 1;
	}
	if ((pos_y > 0 && pos_y < map->sizey))
		map->proj_img.data[data_pos] = map->sprite_texture->data[tex_pos];
}
