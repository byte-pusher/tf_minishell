/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjupy <gjupy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 18:49:02 by gjupy             #+#    #+#             */
/*   Updated: 2022/11/25 16:57:35 by gjupy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

void	ft_exec_builtin(t_cmd_table *cmd_table)
{
	if (cmd_table->builtin_type == ECHO)
		ft_echo(cmd_table->cmd_args);
}

void	ft_create_child_prc(t_cmd_table *cmd_table, t_env *env_tesh, t_exec *exec)
{
	char	**env_arr;

	env_arr = ft_get_env_arr(env_tesh);
	exec->i++; // count processes initiated
	if (pipe(exec->end) < 0)
		exit (-1); // noch entscheiden wie ich mit den errors umgehe
	exec->pid = fork();
	if (exec->pid < 0)
		exit (-1); // noch entscheiden wie ich mit den errors umgehe
	else if (exec->pid == 0)
	{
		if (ft_check_single_cmd(cmd_table) == true)
			exit_status = execve(cmd_table->path_name, cmd_table->cmd_args, env_arr);
	}
	close(exec->end[READ]);
	close(exec->end[WRITE]);
}

void	ft_end_prcs(t_exec	*exec)
{
	while (exec->i > 0)
	{
		waitpid(0, &exec->pid, 0);
		if (WIFEXITED(exec->pid))
			exit_status = WEXITSTATUS(exec->pid);
		exec->i--;
	}
	free(exec);
}

// letztendlich geht es darum zu schauen was zu STDIN und was zu STDOUT pointen soll
// entweder igne file oder pipe
// de cmds finden dann automatisch 
void	ft_executor(t_data *data)
{
	t_cmd_table	*current;
	t_exec	*exec;

	current = ft_lstfirst_ct(&data->cmd_table);
	if (ft_check_single_builtin(current) == true)
	{
		ft_exec_builtin(current);
		return ;
	}
	exec = ft_create_exec();
	while (current != NULL)
	{
		if (current->is_command == false)
		{
			current = current->next;
			continue ;
		}
		else
			ft_create_child_prc(current, data->env_tesh, exec);
		if (exit_status < 0)
			break ;
		current = current->next;
	}
	ft_end_prcs(exec);
}
