/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunyoo <hyunyoo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 14:10:54 by hyunyoo           #+#    #+#             */
/*   Updated: 2021/02/05 19:20:30 by hyunyoo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int			g_i;
int			g_j;
t_bool		g_search_cha;
char		g_tp;

void		str_free(char **str_arr)
{
	int		idx;

	idx = 0;
	while (str_arr[idx])
	{
		free(str_arr[idx++]);
	}
	free(str_arr);
}

char		**convert_to_hexstr(char **rgb)
{
	int		idx;
	int		tmp;
	char	**new_str;

	idx = 0;
	if (!(new_str = (char **)malloc(sizeof(char *) * 3)))
		return (NULL);
	while (idx < 3)
	{
		tmp = ft_atoi(rgb[idx]);
		new_str[idx] = ft_itoa_base(tmp, 16);
		idx++;
	}
	str_free(rgb);
	return (new_str);
}

void		get_array_size(t_map **mapinfo, char **map, int str_idx)
{
	int		*result;
	int		idx;
	int		width;

	idx = 0;
	if (!(result = (int *)malloc(sizeof(int) * 2)))
		return ;
	ft_memset(result, 0, sizeof(int) * 2);
	while (map[str_idx + (idx++)])
		result[0]++;
	idx = 0;
	while (map[str_idx + idx])
	{
		width = ft_strlen(map[str_idx + idx]);
		result[1] = result[1] > width ? result[1] : width;
		idx++;
	}
	(*mapinfo)->m_size_x = result[1];
	(*mapinfo)->m_size_y = result[0];
	free(result);
}

void		parse_map2_arr(char **m, int str_idx, t_map *map, t_vector **player)
{
	g_i = -1;
	while (m[str_idx + (++g_i)])
	{
		g_j = 0;
		while (m[str_idx + g_i][g_j])
		{
			g_tp = m[str_idx + g_i][g_j];
			if (g_tp == '1' || g_tp == '2')
			{
				map->sp_cnt = map->sp_cnt + (g_tp == '2' ? 1 : 0);
				(map->map)[g_i][g_j++] = g_tp;
			}
			else if (g_tp == 'N' || g_tp == 'S' || g_tp == 'W' || g_tp == 'E')
			{
				if (g_search_cha)
					print_error("More than one character\n");
				ini_vec2(player, g_j, g_i);
				(map->map)[g_i][g_j++] = '0';
				g_search_cha = TRUE;
			}
			else
				(map->map)[g_i][g_j++] = '0';
		}
	}
}

void		parse_map(char **m, int str_idx, t_map *map)
{
	t_vector	*player;

	player = NULL;
	parse_map2_arr(m, str_idx, map, &player);
	bfs(map, map->map, player);
	free(player);
}
