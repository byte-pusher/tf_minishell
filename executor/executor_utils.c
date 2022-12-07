/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjupy <gjupy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 14:29:58 by gjupy             #+#    #+#             */
/*   Updated: 2022/12/07 20:21:44 by gjupy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

void	ft_end_prcs(t_exec *exec)
{
	close(exec->end[READ]);
	close(exec->end[WRITE]);
	close(exec->tmp_fd);
	close(exec->stout);
	while (exec->i > 0)
	{
		waitpid(0, &exec->pid, 0);
		if (WIFEXITED(exec->pid) == true)
			g_exit_status = WEXITSTATUS(exec->pid);
		exec->i--;
	}
	free(exec);
}

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
	new_exec->i = 0;
	new_exec->end[WRITE] = 0;
	new_exec->end[READ] = 0;
	new_exec->here_fd[WRITE] = 0;
	new_exec->here_fd[READ] = 0;
	// tmp_fd is always saving the STDIN/READ END of PIPE
	new_exec->tmp_fd = dup(STDIN_FILENO);
	if (new_exec->tmp_fd == -1)
		ft_err_msg("dup");
	// what STDOUT should have at the end
	new_exec->stout = dup(STDOUT_FILENO);
	if (new_exec->stout ==-1)
		ft_err_msg("dup");
	return (new_exec);
}
