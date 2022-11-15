/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjupy <gjupy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/10 22:22:01 by gjupy             #+#    #+#             */
/*   Updated: 2022/04/10 22:22:01 by gjupy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// lst: The address of a pointer to a node.
// f: The address of the function used to iterate on
// the list.
// del: The address of the function used to delete
// the content of a node if needed.

// Iterates the list ’lst’ and applies the function
// ’f’ on the content of each node. Creates a new_lst
// list resulting of the successive applications of
// the function ’f’. The ’del’ function is used to
// delete the content of a node if needed.

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_lst;
	t_list	*new_elem;
	t_list	*p;

	if (lst == NULL || f == NULL)
		return (NULL);
	p = lst;
	new_lst = NULL;
	while (p)
	{
		new_elem = ft_lstnew(f(p->content));
		if (!new_elem)
		{
			ft_lstclear(&new_lst, del);
			return (NULL);
		}
		ft_lstadd_back(&new_lst, new_elem);
		p = p->next;
	}
	return (new_lst);
}
