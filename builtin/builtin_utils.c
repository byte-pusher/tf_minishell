/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkoop <rkoop@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 23:29:25 by gjupy             #+#    #+#             */
/*   Updated: 2022/11/30 19:14:10 by rkoop            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

bool	ft_is_builtin(t_cmd_table *cmd_table, char *builtin)
{
	if (ft_strlen(builtin) == 4 && (ft_strncmp(builtin, "echo", 4) == 0 || ft_strncmp(builtin, "ECHO", 4) == 0))
		cmd_table->builtin_type = ECHO;
	else if (ft_strlen(builtin) == 2 && (ft_strncmp(builtin, "cd", 2) == 0))
		cmd_table->builtin_type = CD;
	else if (ft_strlen(builtin) == 3 && (ft_strncmp(builtin, "pwd", 3) == 0 || ft_strncmp(builtin, "PWD", 3) == 0))
		cmd_table->builtin_type = PWD;
	else if (ft_strlen(builtin) == 6 && (ft_strncmp(builtin, "export", 6) == 0))
		cmd_table->builtin_type = EXPORT;
	else if (ft_strlen(builtin) == 5 && (ft_strncmp(builtin, "unset", 5) == 0))
		cmd_table->builtin_type = UNSET;
	else if (ft_strlen(builtin) == 3 && (ft_strncmp(builtin, "env", 3) == 0 || ft_strncmp(builtin, "ENV", 3) == 0)) 
		cmd_table->builtin_type = ENV;
	else if (ft_strlen(builtin) == 4 && (ft_strncmp(builtin, "exit", 4) == 0)) 
		cmd_table->builtin_type = EXIT;
	else
		return (false);
	cmd_table->is_builtin = true;
	return (true);
}

bool	ft_is_flag(char **cmd_args)
{
	int	j;

	if (cmd_args[1][1] != '\0' && cmd_args[1][0] == '-'
		&& cmd_args[1][1] == 'n')
	{
		j = 2;
		while (cmd_args[1][j])
		{
			if (cmd_args[1][j] != 'n')
				return (false);
			j++;
		}
	}
	else
		return (false);
	return (true);
}

void	ft_skip_flags(char **cmd_args, int *i)
{
	int	j;

	*i = 2;
	while (cmd_args[*i] != NULL)
	{
		if (cmd_args[*i][1] != '\0' && cmd_args[*i][0] == '-'
			&& cmd_args[*i][1] == 'n')
		{
			j = 2;
			while (cmd_args[*i][j])
			{
				if (cmd_args[*i][j] != 'n')
					return ;
				j++;
			}
		}
		else
			return ;
		(*i)++;
	}
}
