/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_queue.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunyoo <hyunyoo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 15:35:04 by hyunyoo           #+#    #+#             */
/*   Updated: 2021/02/05 19:06:40 by hyunyoo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int			*g_dx = (int[8]){-1, -1, -1, 0, 0, 1, 1, 1};
int			*g_dy = (int[8]){-1, 0, 1, -1, 1, -1, 0, 1};
int			g_tp;
t_queue		*g_q;

void		check_map(t_map *map, int *vst)
{
	int i;
	int j;

	i = 0;
	while (i < map->m_size_y)
	{
		if (i == 0 || i == map->m_size_y - 1)
		{
			j = 0;
			while (j < map->m_size_x)
			{
				if (vst[map->m_size_x * i + j] == 1)
					print_error("Map Error");
				j++;
			}
		}
		else
		{
			if (vst[map->m_size_x * i] == 1 ||
			vst[map->m_size_x * i + (map->m_size_x - 1)] == 1)
				print_error("Map Error");
		}
		i++;
	}
}

void		bfs(t_map *map, char **graph, t_vector *vec)
{
	t_vector	*c_v;

	g_q = create_queue(map);
	enqueue(g_q, vec);
	g_q->vst[(int)vec->y_pos * map->m_size_x + (int)vec->x_pos] = 1;
	while (!isempty(g_q))
	{
		c_v = dequeue(g_q);
		g_tp = -1;
		while (++g_tp < 8)
		{
			ini_vec2(&vec, c_v->x_pos + g_dx[g_tp], c_v->y_pos + g_dy[g_tp]);
			if ((vec->x_pos >= 0 && vec->x_pos < map->m_size_x &&
			vec->y_pos >= 0 && vec->y_pos < map->m_size_y) &&
			g_q->vst[(int)vec->y_pos * map->m_size_x + (int)vec->x_pos] == 0 &&
			graph[(int)vec->y_pos][(int)vec->x_pos] != '1')
			{
				g_q->vst[(int)vec->y_pos * map->m_size_x + (int)vec->x_pos] = 1;
				enqueue(g_q, vec);
			}
		}
		free(c_v);
	}
	check_map(map, g_q->vst);
	free(g_q);
}
