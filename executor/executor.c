/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjupy <gjupy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 18:49:02 by gjupy             #+#    #+#             */
/*   Updated: 2022/12/02 17:06:35 by gjupy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

int	ft_exec_builtin(t_cmd_table *cmd_table)
{
	if (cmd_table->builtin_type == ECHO)
		ft_echo(cmd_table->cmd_args);
	return (SUCCESS);
}

void	ft_exec(t_cmd_table *cmd_table, t_env *env_tesh)
{
	char	**env_arr;

	env_arr = ft_get_env_arr(env_tesh);
	if (cmd_table->cmd_not_found == true)
	{
		g_exit_status = CMD_NOT_FOUND;
		ft_err_msg(cmd_table->path_name);
	}
	else if (cmd_table->is_command == true && cmd_table->is_builtin == false)
	{
		if (execve(cmd_table->path_name,
				cmd_table->cmd_args, env_arr) == -1)
			ft_err_msg(cmd_table->path_name);
	}
	else
	{
		ft_exec_builtin(cmd_table);
		exit (g_exit_status);
	}
	exit (g_exit_status);
}

void	ft_route_and_exec(t_cmd_table *cmd_table, t_env *env_tesh,
						t_exec *exec)
{
	close(exec->end[READ]); // das hat cat|cat|ls gefixt
	ft_route_stdin(cmd_table, exec);
	if (g_exit_status != OPEN_FILE_ERR)
		ft_route_stdout(cmd_table, exec);
	if (g_exit_status != OPEN_FILE_ERR && cmd_table->is_command == true)
		ft_exec(cmd_table, env_tesh);
	exit(g_exit_status); // ändern zu system code
}

int	ft_create_child_prc(t_cmd_table *cmd_table, t_env *env_tesh, t_exec *exec)
{
	if (pipe(exec->end) == -1)
	{
		ft_err_msg("pipe");
		return (1);
	}
	exec->i++;
	exec->pid = fork(); // noch entscheiden wie ich mit den errors umgehe
	if (exec->pid == 0)
	{
		if (ft_check_single_cmd(cmd_table) == true)
			ft_exec(cmd_table, env_tesh);
		else
			ft_route_and_exec(cmd_table, env_tesh, exec);
	}
	else if (exec->pid > 0)
	{
		if (dup2(exec->end[READ], exec->tmp_fd) == -1)
			ft_err_msg("dup2");
		close(exec->end[READ]);
		close(exec->end[WRITE]);
	}
	return (exec->pid);
}

// letztendlich geht es darum zu schauen was zu STDIN und was zu STDOUT pointen soll
// entweder igne file oder pipe
// de cmds finden dann automatisch 
void	ft_executor(t_data *data)
{
	t_cmd_table	*current;
	t_exec		*exec;

	current = ft_lstfirst_ct(&data->cmd_table);
	if (ft_check_single_builtin(current) == true)
	{
		ft_exec_builtin(current);
		return ;
	}
	exec = ft_create_exec();
	ft_open_heredocs(exec, &data->cmd_table);
	while (current != NULL)
	{
		if (ft_create_child_prc(current, data->env_tesh, exec) == -1)
			ft_err_msg("fork");
		current = current->next;
	}
	ft_end_prcs(exec);
}
