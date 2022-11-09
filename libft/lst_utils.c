/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjupy <gjupy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 12:23:50 by gjupy             #+#    #+#             */
/*   Updated: 2022/11/09 19:03:07 by gjupy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

t_token	*ft_lstlast(t_token *lst)
{
	t_token	*p;

	if (lst == NULL)
		return (NULL);
	p = lst;
	while (p->next)
		p = p->next;
	return (p);
}

void	ft_lstadd_back(t_token **lst, t_token *new)
{
	t_token	*p;

	if (lst && new)
	{
		if (*lst == NULL)
			*lst = new;
		else
		{
			p = ft_lstlast(*(lst));
			p->next = new;
			new->prev = p;
		}
	}
}

t_token	*ft_lstnew(t_token **lst)
{
	t_token	*node;

	node = malloc(sizeof(t_token));
	if (node == NULL)
		exit(-1); // create here exit_failure funciton to free the tokens list
	node->next = NULL;
	node->prev = NULL;
	return (node);
}

t_token	*ft_lstfirst(t_token **lst)
{
	t_token	*current;
	t_token	*prev;

	if (lst == NULL)
		return (NULL);
	current = *lst;
	while (current->prev)
		current = current->prev;
	return (current);
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

void	ft_lst_clear(t_token **lst)
{
	t_token	*current;
	t_token	*next;

	current = *lst;
	while (current)
	{
		next = current->next;
		free(current);
		free(current->name);
		current = next;
	}
	*lst = NULL;
	lst = NULL;
}

void	ft_print_list(t_token **lst)
{
	t_token	*current;
	t_token	*next;

	current = *lst;
	while (current)
	{
		next = current->next;
		dprintf(2, "%s\n", current->name);
		current = next;
	}
}
