/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_init_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunyoo <hyunyoo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/23 19:36:03 by hyunyoo           #+#    #+#             */
/*   Updated: 2021/02/05 19:28:48 by hyunyoo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void		init_vector(t_vector *vector, double x, double y)
{
	vector->x_pos = x;
	vector->y_pos = y;
}

void		*img_init(t_window *window, int width, int height)
{
	return (mlx_new_image(window->mlx, width, height));
}

void		init_map(t_window *window)
{
	t_map	*new_map;

	if (!(new_map = (t_map *)malloc(sizeof(t_map))))
		print_error("Cannot malloc data");
	new_map->sizex = 0;
	new_map->sizey = 0;
	new_map->m_size_x = 0;
	new_map->m_size_y = 0;
	new_map->no_texture = 0;
	new_map->so_texture = 0;
	new_map->we_texture = 0;
	new_map->ea_texture = 0;
	new_map->sprite_texture = 0;
	new_map->floor_color = 0;
	new_map->ceiling_color = 0;
	new_map->map = NULL;
	new_map->sp_cnt = 0;
	window->map = new_map;
	new_map->minimap_img.img_ptr = NULL;
	new_map->proj_img.img_ptr = NULL;
}

char		**init_worldmap(int size_x, int size_y)
{
	char	**worldmap;
	int		idx;

	if (!(worldmap = (char **)malloc(sizeof(char *) * size_y)))
		print_error("Cannot malloc data");
	idx = 0;
	while (idx < size_y)
	{
		if (!(worldmap[idx] = (char *)malloc(sizeof(char) * size_x)))
			print_error("Cannot malloc data");
		ft_memset(worldmap[idx], '0', sizeof(char) * size_x);
		idx++;
	}
	return (worldmap);
}

t_cast		*init_cast_info(void)
{
	t_cast *result;

	if (!(result = (t_cast *)malloc(sizeof(t_cast))))
		return (NULL);
	result->distance = 0;
	result->x_inter = 0;
	result->y_inter = 0;
	result->x_step = 0;
	result->y_step = 0;
	result->distance = 0;
	result->horzhit_x = 0;
	result->horzhit_y = 0;
	result->verthit_x = 0;
	result->verthit_y = 0;
	result->checkhithorz = FALSE;
	result->checkhitvert = FALSE;
	return (result);
}
