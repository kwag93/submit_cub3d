/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_raycast_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunyoo <hyunyoo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 10:50:29 by hyunyoo           #+#    #+#             */
/*   Updated: 2021/02/05 19:06:37 by hyunyoo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

double		normalize_angle(double rayangle)
{
	rayangle = fmod(rayangle, 2 * M_PI);
	if (rayangle < 0)
		rayangle = 2 * M_PI + rayangle;
	return (rayangle);
}

double		getdist(const t_character *charac, double pos_x, double pos_y)
{
	return (sqrt(pow(fabs(charac->pos_x - pos_x), 2)
	+ pow(fabs(charac->pos_y - pos_y), 2)));
}

t_ray		*init_ray(double rayangle)
{
	t_ray	*ray;

	if (!(ray = (t_ray *)malloc(sizeof(t_ray))))
		return (NULL);
	ray->rayangle = normalize_angle(rayangle);
	ray->wallhit_x = 0;
	ray->wallhit_y = 0;
	ray->distance = 0;
	ray->washitvert = FALSE;
	ray->israyfacingdown = ray->rayangle > 0 && ray->rayangle < M_PI;
	ray->israyfacingup = !ray->israyfacingdown;
	ray->israyfacingright = ray->rayangle < 0.5 * M_PI ||
	ray->rayangle > 1.5 * M_PI;
	ray->israyfacingleft = !ray->israyfacingright;
	return (ray);
}

void		disable_sprite(t_map *map, int grid_y, int grid_x)
{
	int i;

	i = 0;
	while (i < map->sp_cnt)
	{
		if (((int)((map->sprites[i].y_sp / TILE_SIZE) - 0.5) == grid_y)
		&& (int)((map->sprites[i].x_sp / TILE_SIZE) - 0.5) == grid_x)
		{
			map->sprites[i].x_sp = -1;
			map->sprites[i].y_sp = -1;
		}
		i++;
	}
}

t_bool		check_wall(t_map *map, double pos_x, double pos_y)
{
	int grid_x;
	int grid_y;

	if (pos_x < 0 || pos_x > map->m_size_x * TILE_SIZE ||
	pos_y < 0 || pos_y > map->m_size_y * TILE_SIZE)
	{
		return (TRUE);
	}
	grid_x = floor(pos_x / TILE_SIZE);
	grid_y = floor(pos_y / TILE_SIZE);
	return (map->map[grid_y][grid_x] != '0' && map->map[grid_y][grid_x] != '2');
}
