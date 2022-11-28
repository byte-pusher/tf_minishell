/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjupy <gjupy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 14:29:58 by gjupy             #+#    #+#             */
/*   Updated: 2022/11/28 18:29:35 by gjupy            ###   ########.fr       */
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
	if (env_arr == NULL)
		exit(ENOMEM);
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
		return (true);
	else
		return (false);
}

t_exec	*ft_create_exec(void)
{
	t_exec	*new_exec;

	new_exec = malloc(sizeof(t_exec));
	// count processes that were initiated
	new_exec->i = 0;
	new_exec->end[WRITE] = 0;
	new_exec->end[READ] = 0;
	new_exec->here_fd[WRITE] = 0;
	new_exec->here_fd[READ] = 0;
	// tmp_fd is always saving the STDIN/READ END of PIPE
	new_exec->tmp_fd = dup(STDIN_FILENO);
	// to where the STDIN should point at the end
	new_exec->stin = dup(STDIN_FILENO);
	// to where the STDOUT should point at the end
	new_exec->stout = dup(STDOUT_FILENO);
	return (new_exec);
}
