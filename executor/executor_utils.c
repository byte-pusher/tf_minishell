/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjupy <gjupy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 14:29:58 by gjupy             #+#    #+#             */
/*   Updated: 2022/11/25 14:32:18 by gjupy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

char	**ft_get_env_arr(t_env *env_tesh)
{
	int		i;
	t_env	*current;
	char	**env_arr;

	current = ft_lstfirst_env(&env_tesh);
	env_arr = malloc(sizeof(char *) * (ft_lstsize_env(&env_tesh) + 1));
	i = 0;
	while (current)
	{
		env_arr[i] = ft_strdup(current->var);
		i++;
		current = current->next;
	}
	env_arr[i] = NULL;
	return (env_arr);
}

bool	ft_check_single_builtin(t_cmd_table *cmd_table)
{
	if (cmd_table->is_builtin == true && cmd_table->is_redir == false
		&& cmd_table->prev == NULL && cmd_table->next == NULL)
		return (true);
	else
		return (false);
}

bool	ft_check_single_cmd(t_cmd_table *cmd_table)
{
	if (cmd_table->is_command == true && cmd_table->is_builtin == false
		&& cmd_table->is_redir == false && cmd_table->next == NULL
		&& cmd_table->prev == NULL)
		return (false);
	else
		return (true);
}
