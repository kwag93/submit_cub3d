/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunyoo <hyunyoo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/06 22:03:56 by hyunyoo           #+#    #+#             */
/*   Updated: 2020/07/10 00:23:45 by hyunyoo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

int		check_set(char c, char *set)
{
	size_t i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*newstr;
	int		st;
	int		en;
	int		idx;

	st = 0;
	en = (int)ft_strlen(s1) - 1;
	while (s1[st] && check_set(s1[st], (char *)set))
		st++;
	while (en >= st && check_set(s1[en], (char *)set))
		en--;
	if (st >= en)
		return (ft_strdup(""));
	if (!(newstr = (char *)malloc(sizeof(char) * (en - st + 2))))
	{
		return (NULL);
	}
	idx = 0;
	while (st <= en)
	{
		newstr[idx++] = s1[st++];
	}
	newstr[idx] = 0;
	return (newstr);
}
