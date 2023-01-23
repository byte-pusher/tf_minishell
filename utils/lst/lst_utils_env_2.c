/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_utils_env_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjupy <gjupy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 23:51:07 by gjupy             #+#    #+#             */
/*   Updated: 2022/12/14 16:48:36 by gjupy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell.h"

bool	ft_is_head(t_data *data, t_env *node)
{
	if (data->env_tesh == node)
	{
		if (node->next)
			data->env_tesh = node->next;
		else
			data->env_tesh = NULL;
		free(node->var);
		free(node);
		return (true);
	}
	return (false);
}

void	ft_lstdel_env(t_data *data, t_env *node)
{
	t_env	*p;

	if (data->env_tesh == NULL || node == NULL)
		return ;
	if (ft_is_head(data, node) == true)
		return ;
	p = data->env_tesh;
	while (p != NULL)
	{
		if (p->var != NULL)
		{
			if (ft_strncmp(p->var, node->var, comp_var_len(p->var) + 1) == 0)
			{
				if (p->next != NULL)
					p->next->prev = p->prev;
				if (p->prev != NULL)
					p->prev->next = p->next;
				free(p->var);
				free(p);
				break ;
			}
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
