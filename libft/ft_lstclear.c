/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkoop <rkoop@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 11:32:11 by rkoop             #+#    #+#             */
/*   Updated: 2022/04/12 12:12:38 by rkoop            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*hold;

	while (*lst != NULL)
	{
		hold = (*lst)->next;
		ft_lstdelone(*lst, del);
		*lst = hold;
	}
	lst = NULL;
}
