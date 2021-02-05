/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunyoo <hyunyoo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/21 13:48:08 by hyunyoo           #+#    #+#             */
/*   Updated: 2021/01/09 14:59:35 by hyunyoo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int		ft_strlen_gnl(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		i++;
	}
	return (i);
}

char	*ft_strdup_gnl(char *s1)
{
	int		len;
	char	*newstr;

	len = 0;
	while (s1[len])
		len++;
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

char	*ft_strjoin_gnl(char *s1, char *s2)
{
	char	*newstr;
	int		len1;
	int		len2;
	int		idx;
	int		i;

	if (!(s1) && !(s2))
		return (NULL);
	else if (!(s1) || !(s2))
		return ((s1 == NULL) ? ft_strdup_gnl(s2) : ft_strdup_gnl(s1));
	len1 = ft_strlen_gnl(s1);
	len2 = ft_strlen_gnl(s2);
	if (!(newstr = (char *)malloc(sizeof(char) * (len1 + len2 + 1))))
		return (NULL);
	i = 0;
	idx = 0;
	while (s1[i])
		newstr[idx++] = s1[i++];
	i = 0;
	while (s2[i])
		newstr[idx++] = s2[i++];
	newstr[idx] = 0;
	free(s1);
	return (newstr);
}
