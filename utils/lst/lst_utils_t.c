/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_utils_t.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjupy <gjupy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 12:23:50 by gjupy             #+#    #+#             */
/*   Updated: 2022/11/24 16:57:26 by gjupy            ###   ########.fr       */
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
// 	if (exit == true && exit_status == false)
// 		ft_exit_print(exit_status, "Error\n", 2);
// 	else if (exit == true && exit_status == true)
// 		ft_exit_print(exit_status, "Error\n", 2);
// 	*lst = NULL;
// 	lst = NULL;
// }

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

void	ms_print_list(t_token **lst)
{
	t_token	*current;
	t_token	*next;

	current = *lst;
	while (current)
	{
		next = current->next;
		dprintf(2, "%s\n", current->name);
		dprintf(2, "%d\n", current->type);
		current = next;
	}
}