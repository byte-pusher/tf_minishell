/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjupy <gjupy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 20:38:19 by gjupy             #+#    #+#             */
/*   Updated: 2022/11/22 21:30:26 by gjupy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

bool	ft_is_builtin(t_cmd_table *cmd_table, char *builtin)
{
	if (ft_strlen(builtin) == 4 && (ft_strncmp(builtin, "echo", 4) == 0))
		cmd_table->builtin_type = ECHO;
	else if	(ft_strlen(builtin) == 2 && (ft_strncmp(builtin, "cd", 2) == 0))
		cmd_table->builtin_type = CD;
	else if (ft_strlen(builtin) == 3 && (ft_strncmp(builtin, "pwd", 3) == 0))
		cmd_table->builtin_type = PWD;
	else if (ft_strlen(builtin) == 6 && (ft_strncmp(builtin, "export", 6) == 0))
		cmd_table->builtin_type = EXPORT;
	else if (ft_strlen(builtin) == 5 && (ft_strncmp(builtin, "unset", 5) == 0))
		cmd_table->builtin_type = UNSET;
	else if (ft_strlen(builtin) == 3 && (ft_strncmp(builtin, "env", 3) == 0))
		cmd_table->builtin_type = ENV;
	else if (ft_strlen(builtin) == 4 && (ft_strncmp(builtin, "exit", 4) == 0))
		cmd_table->builtin_type = EXIT;
	else
		return (false);
	cmd_table->is_builtin = true;
	return (true);
}

void	ft_exit(void)
{
	printf("\n");
	printf("exit");
	exit(SUCCESS);
}

void	ft_env(t_env *env_tesh)
{
	print_env(&env_tesh);
}
