/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_utils_rd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjupy <gjupy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 12:23:50 by gjupy             #+#    #+#             */
/*   Updated: 2023/01/23 16:27:06 by gjupy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell.h"

t_redir	*ft_lstlast_rd(t_redir *lst)
{
	t_redir	*p;

	if (lst == NULL)
		return (NULL);
	p = lst;
	while (p->next)
		p = p->next;
	return (p);
}

void	ft_lstadd_back_rd(t_redir **lst, t_redir *new)
{
	t_redir	*p;

	if (lst && new)
	{
		if (*lst == NULL)
		{
			*lst = new;
			(*lst)->head = new;
		}
		else
		{
			p = ft_lstlast_rd(*(lst));
			p->next = new;
			new->prev = p;
		}
	}
}

t_redir	*ft_lstnew_rd(void)
{
	t_redir	*node;

	node = malloc(sizeof(t_redir));
	if (node == NULL)
		exit(ENOMEM);
	node->file = NULL;
	node->next = NULL;
	node->prev = NULL;
	return (node);
}

t_redir	*ft_lstfirst_rd(t_redir **lst)
{
	if (lst == NULL)
		return (NULL);
	return (*lst);
}

void	ft_lstclear_rd(t_redir **lst)
{
	t_redir	*current;
	t_redir	*next;

	current = (*lst)->head;
	while (current != NULL)
	{
		next = current->next;
		if (current->file[0] != '\0')
			free(current->file);
		free(current);
		current = next;
	}
	*lst = NULL;
	lst = NULL;
}
