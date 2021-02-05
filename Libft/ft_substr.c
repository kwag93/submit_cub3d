/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunyoo <hyunyoo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/06 21:53:07 by hyunyoo           #+#    #+#             */
/*   Updated: 2020/07/11 10:30:51 by hyunyoo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*newstr;
	size_t	i;
	size_t	j;
	size_t	size;

	i = 0;
	j = 0;
	size = ft_strlen(s);
	if (start >= size)
		return (ft_strdup(""));
	if (!(newstr = (char *)malloc(sizeof(char) * (len + 1))))
	{
		return (NULL);
	}
	while (s[start + i] && i < len)
	{
		newstr[j++] = s[start + i];
		i++;
	}
	newstr[j] = 0;
	return (newstr);
}
