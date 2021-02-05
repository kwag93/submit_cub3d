/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunyoo <hyunyoo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/07 11:58:07 by hyunyoo           #+#    #+#             */
/*   Updated: 2020/07/11 11:54:33 by hyunyoo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *l, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_head;
	t_list	*new_next;
	t_list	*curr;

	if (l == NULL || f == NULL)
		return (NULL);
	if ((new_head = ft_lstnew(f(l->content))) == NULL)
		return (NULL);
	curr = new_head;
	l = l->next;
	while (l)
	{
		if ((new_next = ft_lstnew(f(l->content))) == NULL)
		{
			ft_lstclear(&new_head, del);
			return (NULL);
		}
		curr->next = new_next;
		curr = new_next;
		l = l->next;
	}
	return (new_head);
}
