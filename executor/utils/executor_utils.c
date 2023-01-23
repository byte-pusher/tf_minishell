/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjupy <gjupy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 14:29:58 by gjupy             #+#    #+#             */
/*   Updated: 2022/12/14 16:33:39 by gjupy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell.h"

void	ft_close_open_fds(t_exec *exec, t_cmd_table **cmd_table)
{
	t_cmd_table	*current;

	current = *cmd_table;
	while (current != NULL)
	{
		close(current->here_tmp_fd);
		current = current->next;
	}
	close(exec->tmp_fd);
	close(exec->stout);
	close(exec->end[WRITE]);
	close(exec->end[READ]);
}

void	ft_end_prcs(t_exec *exec)
{
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

	if (env_tesh && env_tesh->var == NULL)
		return (NULL);
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

/* 
tmp_fd is always saving the STDIN/READ END of PIPE
*/
t_exec	*ft_create_exec(void)
{
	t_exec	*new_exec;

	new_exec = malloc(sizeof(t_exec));
	new_exec->i = 0;
	new_exec->end[WRITE] = 0;
	new_exec->end[READ] = 0;
	new_exec->here_fd[WRITE] = 0;
	new_exec->here_fd[READ] = 0;
	new_exec->tmp_fd = dup(STDIN_FILENO);
	if (new_exec->tmp_fd == -1)
		ft_err_msg("dup");
	new_exec->stout = dup(STDOUT_FILENO);
	if (new_exec->stout == -1)
		ft_err_msg("dup");
	return (new_exec);
}
