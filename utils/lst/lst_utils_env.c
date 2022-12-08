/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_utils_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjupy <gjupy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 12:23:50 by gjupy             #+#    #+#             */
/*   Updated: 2022/12/08 16:05:07 by gjupy            ###   ########.fr       */
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

// void	ft_free_list(t_token **lst, bool exit, bool exit_status)
// {
// 	t_token	*current;
// 	t_token	*next;

// 	current = *lst;
// 	while (current)
// 	{
// 		next = current->next;
// 		free(current);
// 		current = next;
// 	}
// 	if (exit == true && g_exit_status == false)
// 		ft_exit_print(g_exit_status, "Error\n", 2);
// 	else if (exit == true && g_exit_status == true)
// 		ft_exit_print(g_exit_status, "Error\n", 2);
// 	*lst = NULL;
// 	lst = NULL;
// }

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

int	ft_lstsize_env(t_env **lst)
{
	int		i;
	t_env	*current;

	i = 0;
	current = *lst;
	while (current != NULL)
	{
		i++;
		current = current->next;
	}
	return (i);
}
