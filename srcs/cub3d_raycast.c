/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_raycast.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunyoo <hyunyoo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 10:54:43 by bkwag             #+#    #+#             */
/*   Updated: 2021/02/05 19:06:33 by hyunyoo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void		cast_horz(t_map *map, t_ray *ray, t_cast *info)
{
	double	next_x;
	double	next_y;

	info->y_step = TILE_SIZE * (ray->israyfacingup ? -1 : 1);
	info->x_step = TILE_SIZE / tan(ray->rayangle);
	info->x_step *= (ray->israyfacingleft && info->x_step > 0) ? -1 : 1;
	info->x_step *= (ray->israyfacingright && info->x_step < 0) ? -1 : 1;
	next_x = info->x_inter - (ray->rayangle == 45 * M_PI / 180 ? 1 : 0);
	next_y = info->y_inter;
	while (next_x >= 0 && next_x < (map->m_size_x * TILE_SIZE) &&
	next_y >= 0 && next_y < (map->m_size_y * TILE_SIZE))
	{
		if (check_wall(map, next_x, next_y - (ray->israyfacingup ? 1 : 0)))
		{
			info->checkhithorz = TRUE;
			info->horzhit_x = next_x;
			info->horzhit_y = next_y;
			break ;
		}
		else
		{
			next_x += info->x_step;
			next_y += info->y_step;
		}
	}
}

void		cast_vert(t_map *map, t_ray *ray, t_cast *info)
{
	double	next_x;
	double	next_y;

	info->x_step = TILE_SIZE * (ray->israyfacingleft ? -1 : 1);
	info->y_step = TILE_SIZE * tan(ray->rayangle);
	info->y_step *= (ray->israyfacingup && info->y_step > 0) ? -1 : 1;
	info->y_step *= (ray->israyfacingdown && info->y_step < 0) ? -1 : 1;
	next_x = info->x_inter;
	next_y = info->y_inter;
	while (next_y >= 0 && next_x < (map->m_size_x * TILE_SIZE) &&
	next_y >= 0 && next_y < (map->m_size_y * TILE_SIZE))
	{
		if (check_wall(map, next_x - (ray->israyfacingleft ? 1 : 0), next_y))
		{
			info->checkhitvert = TRUE;
			info->verthit_x = next_x;
			info->verthit_y = next_y;
			break ;
		}
		else
		{
			next_x += info->x_step;
			next_y += info->y_step;
		}
	}
}

void		cast(t_map *map, t_character *charac, t_ray *ray)
{
	t_cast	*info;
	double	horzdist;
	double	vertdist;

	info = init_cast_info();
	info->y_inter = floor(charac->pos_y / TILE_SIZE) * TILE_SIZE;
	info->y_inter += ray->israyfacingdown ? TILE_SIZE : 0;
	info->x_inter = charac->pos_x + (info->y_inter - charac->pos_y) /
	tan(ray->rayangle);
	cast_horz(map, ray, info);
	info->x_inter = floor(charac->pos_x / TILE_SIZE) * TILE_SIZE;
	info->x_inter += ray->israyfacingleft ? 0 : TILE_SIZE;
	info->y_inter = charac->pos_y + (info->x_inter - charac->pos_x) *
	tan(ray->rayangle);
	cast_vert(map, ray, info);
	horzdist = (info->checkhithorz)
			? getdist(charac, info->horzhit_x, info->horzhit_y) : 100000;
	vertdist = (info->checkhitvert)
			? getdist(charac, info->verthit_x, info->verthit_y) : 100000;
	ray->wallhit_x = (horzdist < vertdist) ? info->horzhit_x : info->verthit_x;
	ray->wallhit_y = (horzdist < vertdist) ? info->horzhit_y : info->verthit_y;
	ray->distance = (horzdist < vertdist) ? horzdist : vertdist;
	ray->washitvert = (vertdist < horzdist);
	free(info);
}

int			getcolldir(t_map *map, t_ray *ray, t_texture **tex)
{
	if (ray->washitvert)
	{
		*tex = ray->israyfacingleft ? map->ea_texture : map->we_texture;
		if (ray->israyfacingleft)
			return (0);
		else if (ray->israyfacingright)
			return (2);
	}
	else
	{
		*tex = ray->israyfacingup ? map->so_texture : map->no_texture;
		if (ray->israyfacingup)
			return (1);
		else
			return (3);
	}
	return (-1);
}

t_ray		**raycast(t_map *map, t_character *charac)
{
	t_ray		**rays;
	double		rayangle;
	int			i;

	i = 0;
	rayangle = charac->degree - (FOV_ANGLE / 2);
	if (!(rays = (t_ray **)malloc(sizeof(t_ray *) * (map->sizex))))
		print_error("Cannot malloc data");
	while (i < map->sizex)
	{
		rays[i] = init_ray(rayangle);
		cast(map, charac, rays[i]);
		if (map->minimap_img.img_ptr != NULL && i % 50 == 0)
			draw_ray(&map->minimap_img, charac,
			rays[i]->wallhit_x, rays[i]->wallhit_y);
		rayangle += FOV_ANGLE / (map->sizex);
		render_texture(map, charac, rays[i], i);
		i++;
	}
	return (rays);
}
