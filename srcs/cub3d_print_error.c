/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_print_error.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunyoo <hyunyoo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/29 11:43:51 by hyunyoo           #+#    #+#             */
/*   Updated: 2021/02/05 19:07:14 by hyunyoo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int		screen_exit(void)
{
	exit(0);
}

void	print_error(char *msg)
{
	int	message_length;

	message_length = ft_strlen(msg);
	write(1, &*msg, message_length);
	exit(1);
}
