/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_queue_util.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunyoo <hyunyoo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 16:20:33 by hyunyoo           #+#    #+#             */
/*   Updated: 2021/02/05 19:20:07 by hyunyoo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int			isempty(t_queue *q)
{
	if (q->rear == -1)
		return (1);
	else
		return (0);
}

t_queue		*create_queue(t_map *map)
{
	t_queue *q;

	q = malloc(sizeof(t_queue));
	q->front = -1;
	q->rear = -1;
	if (!(q->vst = (int *)malloc(sizeof(int) *
	(map->m_size_x * map->m_size_y))))
		print_error("Cannot malloc vst\n");
	ft_memset(q->vst, 0, sizeof(int) * map->m_size_x * map->m_size_y);
	return (q);
}

void		enqueue(t_queue *q, t_vector *pos)
{
	t_vector *new;

	new = NULL;
	if (q->rear == Q_SIZE - 1)
		printf("Queue is Full!!\n");
	else
	{
		if (q->front == -1)
			q->front = 0;
		q->rear++;
		ini_vec2(&new, pos->x_pos, pos->y_pos);
		q->items[q->rear] = new;
	}
}

t_vector	*dequeue(t_queue *q)
{
	t_vector	*item;

	if (isempty(q))
	{
		printf("Queue is empty\n");
		item = NULL;
	}
	else
	{
		item = q->items[q->front];
		q->front++;
		if (q->front > q->rear)
		{
			q->front = -1;
			q->rear = -1;
		}
	}
	return (item);
}

void		ini_vec2(t_vector **vector, double x, double y)
{
	if (!*vector)
	{
		if (!(*vector = (t_vector *)malloc(sizeof(t_vector))))
			print_error("Cannot init vector");
	}
	(*vector)->x_pos = x;
	(*vector)->y_pos = y;
}
