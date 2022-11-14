/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkoop <rkoop@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 12:29:08 by rkoop             #+#    #+#             */
/*   Updated: 2022/04/17 20:10:27 by rkoop            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*capnode;
	t_list	*rtr_lst;
	t_list	*conv_elem;

	if (lst == NULL || f == 0)
		return (NULL);
	capnode = lst;
	rtr_lst = NULL;
	while (capnode != NULL)
	{
		conv_elem = ft_lstnew(f(capnode->content));
		if (conv_elem == NULL)
		{
			ft_lstclear(&rtr_lst, del);
			return (NULL);
		}
		ft_lstadd_back(&rtr_lst, conv_elem);
		capnode = capnode->next;
	}
	return (rtr_lst);
}
