/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_character.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunyoo <hyunyoo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/10 16:15:08 by hyunyoo           #+#    #+#             */
/*   Updated: 2021/02/05 17:51:30 by hyunyoo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

t_character	*inst_character(int i, int j, char temp)
{
	t_character *charac;

	if (!(charac = (t_character *)malloc(sizeof(t_character))))
		return (NULL);
	charac->pos_x = (j + 0.5) * TILE_SIZE;
	charac->pos_y = (i + 0.5) * TILE_SIZE;
	charac->pos_z = 0.5;
	charac->moving_speed = 0.7;
	charac->rotation_speed = 5 * (M_PI / 180);
	if (temp == 'N')
		charac->degree = M_PI * 3 / 2;
	else if (temp == 'S')
		charac->degree = M_PI / 2;
	else if (temp == 'W')
		charac->degree = M_PI;
	else if (temp == 'E')
		charac->degree = 0;
	else
	{
		free(charac);
		return (NULL);
	}
	return (charac);
}

t_character	*parse_character(char **map, int str_idx)
{
	int		i;
	int		j;
	char	temp;

	i = 0;
	while (map[str_idx + i])
	{
		j = 0;
		while (map[str_idx + i][j])
		{
			temp = map[str_idx + i][j];
			if (temp == 'N' || temp == 'S' || temp == 'W' || temp == 'E')
				return (inst_character(i, j, temp));
			j++;
		}
		i++;
	}
	return (NULL);
}

t_bool		check_movable(t_map *map, t_character *cha, double n_x, double n_y)
{
	int	grid_y;
	int	grid_x;

	grid_x = floor(n_x / TILE_SIZE);
	grid_y = floor(n_y / TILE_SIZE);
	if (map->map[grid_y][grid_x] == '1')
		return (FALSE);
	if (map->map[grid_y][grid_x] == '2')
	{
		map->map[grid_y][grid_x] = '0';
		disable_sprite(map, grid_y, grid_x);
	}
	cha->pos_x = n_x;
	cha->pos_y = n_y;
	return (TRUE);
}
