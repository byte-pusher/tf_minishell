/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_utils_ct.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjupy <gjupy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 12:23:50 by gjupy             #+#    #+#             */
/*   Updated: 2022/12/08 13:32:58 by gjupy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell.h"

t_cmd_table	*ft_lstlast_ct(t_cmd_table *lst)
{
	t_cmd_table	*p;

	if (lst == NULL)
		return (NULL);
	p = lst;
	while (p->next)
		p = p->next;
	return (p);
}

void	ft_lstadd_back_ct(t_cmd_table **lst, t_cmd_table *new)
{
	t_cmd_table	*p;

	if (lst && new)
	{
		if (*lst == NULL)
			*lst = new;
		else
		{
			p = ft_lstlast_ct(*(lst));
			p->next = new;
			new->prev = p;
		}
	}
}

t_cmd_table	*ft_lstnew_ct(void)
{
	t_cmd_table	*node;

	node = malloc(sizeof(t_cmd_table));
	if (node == NULL)
		exit(ENOMEM);
	node->here_tmp_fd = dup(STDIN_FILENO);
	node->is_command = false;
	node->expander_delimiter = false;
	node->mixed_quotes = false;
	node->is_redir = false;
	node->cmd_not_found = false;
	node->is_builtin = false;
	node->redir = NULL;
	node->path_name = NULL;
	node->next = NULL;
	node->prev = NULL;
	return (node);
}

t_cmd_table	*ft_lstfirst_ct(t_cmd_table **lst)
{
	if (lst == NULL)
		return (NULL);
	return (*lst);
}

// void	ft_free_list(t_token **lst, bool exit, bool g_exit_status)
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

void	ft_lstclear_ct(t_cmd_table **lst)
{
	t_cmd_table	*current;
	t_cmd_table	*next;

	current = *lst;
	while (current != NULL)
	{
		next = current->next;
		close(current->here_tmp_fd);
		free(current);
		current = next;
	}
	*lst = NULL;
	lst = NULL;
}
