/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjupy <gjupy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 23:29:25 by gjupy             #+#    #+#             */
/*   Updated: 2022/12/14 16:51:43 by gjupy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

bool	ft_is_builtin(t_cmd_table *cmd_table, char *builtin)
{
	if (ft_strlen(builtin) == 4 && (ft_strncmp(builtin, "echo", 4) == 0
			|| ft_strncmp(builtin, "ECHO", 4) == 0))
		cmd_table->builtin_type = ECHO;
	else if (ft_strlen(builtin) == 2 && (ft_strncmp(builtin, "cd", 2) == 0))
		cmd_table->builtin_type = CD;
	else if (ft_strlen(builtin) == 3 && (ft_strncmp(builtin, "pwd", 3) == 0
			|| ft_strncmp(builtin, "PWD", 3) == 0))
		cmd_table->builtin_type = PWD;
	else if (ft_strlen(builtin) == 6 && (ft_strncmp(builtin, "export", 6) == 0))
		cmd_table->builtin_type = EXPORT;
	else if (ft_strlen(builtin) == 5 && (ft_strncmp(builtin, "unset", 5) == 0))
		cmd_table->builtin_type = UNSET;
	else if (ft_strlen(builtin) == 3 && (ft_strncmp(builtin, "env", 3) == 0
			|| ft_strncmp(builtin, "ENV", 3) == 0))
		cmd_table->builtin_type = ENV;
	else if (ft_strlen(builtin) == 4 && (ft_strncmp(builtin, "exit", 4) == 0))
		cmd_table->builtin_type = EXIT;
	else
		return (false);
	cmd_table->is_builtin = true;
	return (true);
}

t_env	*ft_set_head(t_env *env_tesh)
{
	t_env	*current_head;

	current_head = ft_lstfirst_env(&env_tesh);
	if (current_head->var == NULL)
		current_head = current_head->next;
	return (current_head);
}
