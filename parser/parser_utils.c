/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjupy <gjupy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 17:32:11 by gjupy             #+#    #+#             */
/*   Updated: 2022/11/21 14:55:54 by gjupy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

bool	ft_is_redir(int type)
{
	if (type == GREAT || type == GREATGREAT || type == LESS
		|| type == LESSLESS)
			return (true);
	return (false);
}

void	ft_create_cmd_table_lst(t_data *data)
{
	t_token	*current;

	ft_lstadd_back_ct(&data->cmd_table, ft_lstnew_ct());
	current = ft_lstfirst_t(&data->tokens);
	while (current != NULL)
	{
		if (current->type == PIPE)
			ft_lstadd_back_ct(&data->cmd_table, ft_lstnew_ct());
		current = current->next;
	}
}

void	print_cmd_strings(t_cmd_table *cmd_table)
{
	t_cmd_table *current;

	current = ft_lstfirst_ct(&cmd_table);
	while (current != NULL)
	{
		if (current->is_command == true)
		{
			int i = 0;
			while (current->cmd_args[i] != NULL)
			{
				printf("%s ", current->cmd_args[i]);
				i++;
			}
			printf("\n");
		}
		current = current->next;
	}
}
