/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjupy <gjupy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 13:42:34 by gjupy             #+#    #+#             */
/*   Updated: 2022/12/13 15:37:33 by gjupy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell.h"

void	ft_free_strings(char ***s)
{
	int	i;

	i = 0;
	while ((*s)[i] != NULL)
	{
		if ((*s)[i][0] != '\0')
			free((*s)[i]);
		i++;
	}
	free((*s)[i]);
	free(*s);
}

void	ft_free_cmd_args(t_cmd_table *cmd_table)
{
	t_cmd_table	*current;

	current = ft_lstfirst_ct(&cmd_table);
	while (current != NULL)
	{
		if (current->is_command == true)
		{
			if (current->path_name != NULL && current->path_name[0] != '\0')
				free(current->path_name);
			ft_free_strings(&current->cmd_args);
		}
		current = current->next;
	}
}

void	ft_free_redir(t_cmd_table *cmd_table)
{
	t_cmd_table	*current;

	current = ft_lstfirst_ct(&cmd_table);
	while (current != NULL)
	{
		if (current->is_redir == true)
			ft_lstclear_rd(&current->redir);
		current = current->next;
	}
}

void	ft_clear_cmd_table(t_cmd_table *cmd_table)
{
	ft_free_cmd_args(cmd_table);
	ft_free_redir(cmd_table);
	ft_lstclear_ct(&cmd_table);
}

void	ft_free_all(t_data *data)
{
	ft_lst_clear_t(&data->tokens);
	ft_clear_cmd_table(data->cmd_table);
	free(data->exec);
	free(data->input);
}
