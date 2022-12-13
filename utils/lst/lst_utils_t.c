/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_utils_t.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjupy <gjupy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 12:23:50 by gjupy             #+#    #+#             */
/*   Updated: 2022/12/12 23:52:21 by gjupy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell.h"

t_token	*ft_lstlast_t(t_token *lst)
{
	t_token	*p;

	if (lst == NULL)
		return (NULL);
	p = lst;
	while (p->next)
		p = p->next;
	return (p);
}

void	ft_lstadd_back_t(t_token **lst, t_token *new)
{
	t_token	*p;

	if (lst && new)
	{
		if (*lst == NULL)
			*lst = new;
		else
		{
			p = ft_lstlast_t(*(lst));
			p->next = new;
			new->prev = p;
		}
	}
}

t_token	*ft_lstnew_t(void)
{
	t_token	*node;

	node = malloc(sizeof(t_token));
	if (node == NULL)
		exit(ENOMEM);
	node->mixed_quotes = false;
	node->name = NULL;
	node->next = NULL;
	node->prev = NULL;
	return (node);
}

t_token	*ft_lstfirst_t(t_token **lst)
{
	if (lst == NULL)
		return (NULL);
	return (*lst);
}

void	ft_lst_clear_t(t_token **lst)
{
	t_token	*current;
	t_token	*next;

	current = *lst;
	while (current != NULL)
	{
		next = current->next;
		free(current->name);
		free(current);
		current = next;
	}
	*lst = NULL;
	lst = NULL;
}
