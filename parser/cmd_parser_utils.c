/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_parser_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjupy <gjupy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 18:59:51 by gjupy             #+#    #+#             */
/*   Updated: 2022/12/05 21:29:12 by gjupy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

// 	{
// 		cmd_table->cmd_args = ft_split(token->name, ' ');
// 		if (cmd_table->cmd_args == NULL)
// 			exit(ENOMEM);
// 		cmd_table->is_command = true;
// 	}

int	ft_count_args(t_token *token)
{
	t_token	*current;
	int		ret;

	current = token;
	ret = 0;
	while (current != NULL && ft_is_cmd_or_quotes(current))
	{
		ret++;
		current = current->next;
	}
	return (ret);
}

void	ft_create_cmd_args(t_cmd_table *cmd_table, t_token **token)
{
	int	nbr_of_args;
	int	i;

	nbr_of_args = ft_count_args(*token);
	cmd_table->cmd_args = malloc(sizeof(char *) * (nbr_of_args + 1));
	if (cmd_table->cmd_args == NULL)
		exit(ENOMEM);
	i = 0;
	while (*token != NULL && ft_is_cmd_or_quotes((*token)) == true)
	{
		if ((*token)->type == COMMAND)
			cmd_table->cmd_args[i] = ft_strtrim((*token)->name, "\t\n ");
		else
			cmd_table->cmd_args[i] = ft_strdup((*token)->name);
		if (cmd_table->cmd_args[i] == NULL)
			exit(ENOMEM);
		i++;
		*token = (*token)->next;
	}
	cmd_table->cmd_args[i] = NULL;
	cmd_table->is_command = true;
}
