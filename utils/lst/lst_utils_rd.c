/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_utils_rd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjupy <gjupy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 12:23:50 by gjupy             #+#    #+#             */
/*   Updated: 2022/11/24 15:23:16 by gjupy            ###   ########.fr       */
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

void	ft_lstclear_rd(t_redir **lst)
{
	t_redir	*current;
	t_redir	*next;

	current = (*lst)->head; // bei allen so machen (dann brauch ich die lstfirst fktionen nicht) oder auch nicht hehe
	while (current != NULL)
	{
		next = current->next;
		free(current->file);
		// close(current->fd);
		free(current);
		current = next;
	}
	*lst = NULL;
	lst = NULL;
}
