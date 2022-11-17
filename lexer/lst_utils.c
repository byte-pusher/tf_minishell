/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjupy <gjupy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 12:23:50 by gjupy             #+#    #+#             */
/*   Updated: 2022/11/17 14:19:44 by gjupy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

t_token	*ms_lstlast(t_token *lst)
{
	t_token	*p;

	if (lst == NULL)
		return (NULL);
	p = lst;
	while (p->next)
		p = p->next;
	return (p);
}

t_cmd_table	*lstlast_ct(t_cmd_table *lst)
{
	t_cmd_table	*p;

	if (lst == NULL)
		return (NULL);
	p = lst;
	while (p->next)
		p = p->next;
	return (p);
}

void	ms_lstadd_back(t_token **lst, t_token *new)
{
	t_token	*p;

	if (lst && new)
	{
		if (*lst == NULL)
			*lst = new;
		else
		{
			p = ms_lstlast(*(lst));
			p->next = new;
			new->prev = p;
		}
	}
}

void	lstadd_back_ct(t_cmd_table **lst, t_cmd_table *new)
{
	t_cmd_table	*p;

	if (lst && new)
	{
		if (*lst == NULL)
			*lst = new;
		else
		{
			p = lstlast_ct(*(lst));
			p->next = new;
			new->prev = p;
		}
	}
}

t_token	*ms_lstnew(t_token **lst)
{
	t_token	*node;

	node = malloc(sizeof(t_token));
	if (node == NULL)
		exit(-1); // create here exit_failure funciton to free the tokens list
	node->next = NULL;
	node->prev = NULL;
	return (node);
}

t_cmd_table	*lstnew_ct(t_cmd_table **lst)
{
	t_cmd_table	*node;

	node = malloc(sizeof(t_cmd_table));
	if (node == NULL)
		exit(-1); // create here exit_failure funciton to free the tokens list
	node->is_command = false;
	node->next = NULL;
	node->prev = NULL;
	return (node);
}

t_cmd_table	*lstfirst_ct(t_cmd_table **lst)
{
	t_cmd_table	*current;
	t_cmd_table	*prev;

	if (lst == NULL)
		return (NULL);
	current = *lst;
	while (current->prev)
		current = current->prev;
	return (current);
}

t_token	*ms_lstfirst(t_token **lst)
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

void	ms_lst_clear(t_token **lst)
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

void	ft_lstclear_ct(t_cmd_table **lst)
{
	t_cmd_table	*current;
	t_cmd_table	*next;

	current = *lst;
	while (current != NULL)
	{
		next = current->next;
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
		// dprintf(2, "%d\n", current->type);
		current = next;
	}
}
