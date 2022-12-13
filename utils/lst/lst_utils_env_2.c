/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_utils_env_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjupy <gjupy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 23:51:07 by gjupy             #+#    #+#             */
/*   Updated: 2022/12/13 14:28:44 by gjupy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell.h"

void	ft_lstdel_env(t_env *lst, t_env *node)
{
	t_env	*p;
	t_env	*prev;

	if (lst == NULL || node == NULL)
		return ;
	p = ft_lstfirst_env(&lst);
	while (p != NULL)
	{
		if (p->var == node->var)
		{
			if (p->next != NULL)
				p->next->prev = p->prev;
			if (p->prev != NULL)
				p->prev->next = p->next;
			free(p->var);
			free(p);
			break ;
		}
		p = p->next;
	}
}

void	ft_lstclear_env(t_env **lst)
{
	t_env	*current;
	t_env	*next;

	current = *lst;
	while (current != NULL)
	{
		next = current->next;
		free(current->var);
		free(current);
		current = next;
	}
	*lst = NULL;
	lst = NULL;
}
