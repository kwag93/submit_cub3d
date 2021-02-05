/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunyoo <hyunyoo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/02 13:40:05 by hyunyoo           #+#    #+#             */
/*   Updated: 2020/07/09 20:35:33 by hyunyoo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *hay, const char *needle, size_t len)
{
	size_t i;
	size_t j;
	size_t temp;

	i = 0;
	if (!*needle)
		return ((char *)hay);
	while (i < len && hay[i])
	{
		j = 0;
		if (hay[i] == needle[j])
		{
			temp = i;
			while (needle[j] && (hay[temp] == needle[j]))
			{
				temp++;
				j++;
			}
			if (!needle[j] && (i + j - 1) < len)
				return (&((char *)hay)[i]);
		}
		i++;
	}
	return (NULL);
}
