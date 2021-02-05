/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunyoo <hyunyoo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/02 14:00:32 by hyunyoo           #+#    #+#             */
/*   Updated: 2020/07/11 10:26:57 by hyunyoo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	int		len;
	char	*newstr;

	len = 0;
	while (s1[len])
	{
		len++;
	}
	if (!(newstr = (char *)malloc(sizeof(char) * len + 1)))
		return (NULL);
	len = 0;
	while (s1[len])
	{
		newstr[len] = s1[len];
		len++;
	}
	newstr[len] = '\0';
	return (newstr);
}
