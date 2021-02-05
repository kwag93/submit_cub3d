/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_character_util.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunyoo <hyunyoo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 17:39:08 by hyunyoo           #+#    #+#             */
/*   Updated: 2021/02/05 17:51:11 by hyunyoo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

t_bool		move_character(int key, t_window *win)
{
	if (key == KEY_W || key == KEY_S)
		return (key_ws(key, win));
	else if (key == KEY_A || key == KEY_D)
		return (key_ad(key, win));
	else
		return (FALSE);
}

t_bool		key_ws(int key, t_window *win)
{
	double nextidx_x;
	double nextidx_y;

	nextidx_x = 0;
	nextidx_y = 0;
	if (key == KEY_W)
	{
		nextidx_x = win->charac->pos_x + cos(win->charac->degree)
		* win->charac->moving_speed;
		nextidx_y = win->charac->pos_y + sin(win->charac->degree)
		* win->charac->moving_speed;
	}
	else if (key == KEY_S)
	{
		nextidx_x = win->charac->pos_x - cos(win->charac->degree)
		* win->charac->moving_speed;
		nextidx_y = win->charac->pos_y - sin(win->charac->degree)
		* win->charac->moving_speed;
	}
	return (check_movable(win->map, win->charac, nextidx_x, nextidx_y));
}

t_bool		key_ad(int key, t_window *win)
{
	double nextidx_x;
	double nextidx_y;

	nextidx_x = 0;
	nextidx_y = 0;
	if (key == KEY_A)
	{
		nextidx_x = win->charac->pos_x + cos(win->charac->degree - M_PI / 2)
		* win->charac->moving_speed;
		nextidx_y = win->charac->pos_y + sin(win->charac->degree - M_PI / 2)
		* win->charac->moving_speed;
	}
	else if (key == KEY_D)
	{
		nextidx_x = win->charac->pos_x + cos(win->charac->degree + M_PI / 2)
		* win->charac->moving_speed;
		nextidx_y = win->charac->pos_y + sin(win->charac->degree + M_PI / 2)
		* win->charac->moving_speed;
	}
	return (check_movable(win->map, win->charac, nextidx_x, nextidx_y));
}
