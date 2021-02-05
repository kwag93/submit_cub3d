/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunyoo <hyunyoo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/02 12:29:24 by hyunyoo           #+#    #+#             */
/*   Updated: 2020/07/08 17:57:11 by hyunyoo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	unsigned int	i;
	unsigned int	srclen;

	i = 0;
	srclen = 0;
	while (src[srclen])
	{
		srclen++;
	}
	if (size > 0)
	{
		while (*(src + i) && i < size - 1)
		{
			dst[i] = *(src + i);
			i++;
		}
		dst[i] = '\0';
	}
	return (srclen);
}
