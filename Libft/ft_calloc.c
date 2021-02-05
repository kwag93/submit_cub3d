/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunyoo <hyunyoo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/02 13:57:02 by hyunyoo           #+#    #+#             */
/*   Updated: 2020/07/11 11:14:24 by hyunyoo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	char			*arr;
	unsigned long	i;

	i = 0;
	if (!(arr = malloc(size * count)))
	{
		return (NULL);
	}
	while (i < count * size)
	{
		arr[i++] = 0;
	}
	return ((void *)arr);
}
