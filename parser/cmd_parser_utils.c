/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_parser_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkoop <rkoop@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 18:59:51 by gjupy             #+#    #+#             */
/*   Updated: 2022/12/13 13:30:49 by rkoop            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

int	ft_count_args(t_token *token)
{
	t_token	*current;
	int		ret;

	current = token;
	ret = 0;
	while (current != NULL && ft_is_cmd_or_quotes(current) == true)
	{
		if (current->mixed_quotes == false)
			ret++;
		else
		{
			while (current != NULL && current->mixed_quotes == true)
				current = current->next;
			ret++;
		}
		if (current != NULL)
			current = current->next;
	}
	return (ret);
}

void	ft_join_args(t_cmd_table *cmd_table, t_token **token, char **tmp, int i)
{
	if ((*token)->next != NULL && (*token)->next->name[0] != '\0')
	{
		if (cmd_table->cmd_args[i][0] == '\0')
			cmd_table->cmd_args[i] = ft_strdup((*token)->next->name);
		else
		{
			*tmp = ft_strdup(cmd_table->cmd_args[i]);
			if (tmp == NULL)
				exit(ENOMEM);
			free(cmd_table->cmd_args[i]);
			cmd_table->cmd_args[i] = ft_strjoin(*tmp, (*token)->next->name);
			if (cmd_table->cmd_args[i] == NULL)
				exit(ENOMEM);
			free(*tmp);
		}
	}
	(*token) = (*token)->next;
}

void	ft_create_cmd_args(t_cmd_table *cmd_table, t_token **token)
{
	int		nbr_of_args;
	int		i;
	char	*tmp;

	nbr_of_args = ft_count_args(*token);
	cmd_table->cmd_args = malloc(sizeof(char *) * (nbr_of_args + 1));
	if (cmd_table->cmd_args == NULL)
		exit(ENOMEM);
	i = 0;
	while (*token != NULL && ft_is_cmd_or_quotes(*token) == true)
	{
		if ((*token)->name[0] == '\0')
			cmd_table->cmd_args[i] = "";
		else
			cmd_table->cmd_args[i] = ft_strdup((*token)->name);
		while ((*token) != NULL && (*token)->mixed_quotes == true
			&& ft_is_cmd_or_quotes(*token) == true)
			ft_join_args(cmd_table, token, &tmp, i);
		if (*token != NULL)
			*token = (*token)->next;
		i++;
	}
	cmd_table->cmd_args[i] = NULL;
	cmd_table->is_command = true;
}
