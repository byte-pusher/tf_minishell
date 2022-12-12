/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_utils_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjupy <gjupy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 12:23:50 by gjupy             #+#    #+#             */
/*   Updated: 2022/12/12 23:51:26 by gjupy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell.h"

t_env	*ft_lstlast_env(t_env *lst)
{
	t_env	*p;

	if (lst == NULL)
		return (NULL);
	p = lst;
	while (p->next)
		p = p->next;
	return (p);
}

void	ft_lstadd_back_env(t_env **lst, t_env *new)
{
	t_env	*p;

	if (lst && new)
	{
		if (*lst == NULL)
			*lst = new;
		else
		{
			p = ft_lstlast_env(*(lst));
			p->next = new;
			new->prev = p;
		}
	}
}

t_env	*ft_lstnew_env(void)
{
	t_env	*node;

	node = malloc(sizeof(t_env));
	if (node == NULL)
		exit(ENOMEM);
	node->hidden = false;
	node->var = NULL;
	node->next = NULL;
	return (node);
}

t_env	*ft_lstfirst_env(t_env **lst)
{
	if (lst == NULL)
		return (NULL);
	return (*lst);
}

int	ft_lstsize_env(t_env **lst)
{
	int		i;
	t_env	*current;

	i = 0;
	if (!lst)
		return (i);
	current = *lst;
	while (current != NULL)
	{
		i++;
		current = current->next;
	}
	return (i);
}
