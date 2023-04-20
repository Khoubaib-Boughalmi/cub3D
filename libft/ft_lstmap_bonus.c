/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khoubaib <khoubaib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 20:52:28 by khoubaib          #+#    #+#             */
/*   Updated: 2022/10/07 20:52:28 by khoubaib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*head;
	t_list	*ptr;

	if (!f || !del)
		return (NULL);
	head = NULL;
	if (lst)
	{
		while (lst)
		{
			ptr = ft_lstnew((*f)(lst->content));
			if (!ptr)
			{
				ft_lstclear(&head, del);
				return (NULL);
			}
			ft_lstadd_back(&head, ptr);
			lst = lst->next;
		}
	}
	return (head);
}
