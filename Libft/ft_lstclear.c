/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunyoo <hyunyoo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/07 11:24:41 by hyunyoo           #+#    #+#             */
/*   Updated: 2020/07/07 11:48:51 by hyunyoo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list *idx;
	t_list *temp;

	if (lst == NULL)
		return ;
	idx = *lst;
	while (idx != NULL)
	{
		del(idx->content);
		temp = idx->next;
		free(idx);
		idx = temp;
	}
	*lst = NULL;
}
