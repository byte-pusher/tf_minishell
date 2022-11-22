/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjupy <gjupy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 12:23:50 by gjupy             #+#    #+#             */
/*   Updated: 2022/11/21 22:54:01 by gjupy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

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
		}
	}
}

t_token	*ft_lstnew_t(void)
{
	t_token	*node;

	node = malloc(sizeof(t_token));
	if (node == NULL)
		exit(-1); // create here exit_failure funciton to free the tokens list
	node->name = NULL;
	node->next = NULL;
	node->prev = NULL;
	return (node);
}

t_cmd_table	*ft_lstnew_ct(void)
{
	t_cmd_table	*node;

	node = malloc(sizeof(t_cmd_table));
	if (node == NULL)
		exit(-1); // create here exit_failure funciton to free the tokens list
	node->is_command = false;
	node->is_redir = false;
	node->redir = NULL;
	node->next = NULL;
	node->prev = NULL;
	return (node);
}

t_redir	*ft_lstnew_rd(void)
{
	t_redir	*node;

	node = malloc(sizeof(t_redir));
	if (node == NULL)
		exit(-1); // create here exit_failure funciton to free the tokens list
	node->file = NULL;
	node->next = NULL;
	node->prev = NULL;
	return (node);
}

t_env	*ft_lstnew_env(void)
{
	t_env	*node;

	node = malloc(sizeof(t_env));
	if (node == NULL)
		exit(-1); // create here exit_failure funciton to free the tokens list
	node->var = NULL;
	node->next = NULL;
	return (node);
}

t_cmd_table	*ft_lstfirst_ct(t_cmd_table **lst)
{
	if (lst == NULL)
		return (NULL);
	return (*lst);
}

t_token	*ft_lstfirst_t(t_token **lst)
{
	if (lst == NULL)
		return (NULL);
	return (*lst);
}

t_redir	*ft_lstfirst_rd(t_redir **lst)
{
	if (lst == NULL)
		return (NULL);
	return (*lst);
}

t_env	*ft_lstfirst_env(t_env **lst)
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

void	ft_lstclear_env(t_env **lst)
{
	t_env	*current;

	current = *lst;
	while (current != NULL)
	{
		printf("jo\n");
		free(current->var);
		free(current);
		current = current->next;
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
