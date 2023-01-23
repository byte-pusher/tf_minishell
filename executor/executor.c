/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjupy <gjupy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 18:49:02 by gjupy             #+#    #+#             */
/*   Updated: 2022/12/14 16:32:53 by gjupy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

int	ft_exec_builtin(t_cmd_table *cmd_table, t_env *env_tesh, t_data *data)
{
	if (cmd_table->builtin_type == ECHO)
		ft_echo(cmd_table->cmd_args);
	else if (cmd_table->builtin_type == UNSET)
		ft_unset(cmd_table->cmd_args, env_tesh, data);
	else if (cmd_table->builtin_type == ENV)
		print_env(&env_tesh, data);
	else if (cmd_table->builtin_type == CD)
		ft_cd(cmd_table->cmd_args, env_tesh, data);
	else if (cmd_table->builtin_type == PWD)
		ft_pwd();
	else if (cmd_table->builtin_type == EXPORT)
		ft_export(cmd_table->cmd_args, env_tesh, data);
	else if (cmd_table->builtin_type == EXIT)
		ft_exit(cmd_table->cmd_args, cmd_table, data);
	return (SUCCESS);
}

void	ft_exec(t_cmd_table *cmd_table, t_env *env_tesh, t_data *data,
				t_exec *exec)
{
	char	**env_arr;
	int		execve_ret;

	ft_close_open_fds(exec, &cmd_table);
	env_arr = ft_get_env_arr(env_tesh);
	if (cmd_table->is_command == true && cmd_table->is_builtin == false)
		execve_ret = execve(cmd_table->path_name, cmd_table->cmd_args, env_arr);
	else
	{
		ft_exec_builtin(cmd_table, env_tesh, data);
		exit (g_exit_status);
	}
	if (cmd_table->cmd_not_found == true)
	{
		g_exit_status = CMD_NOT_FOUND;
		ft_err_msg(cmd_table->path_name);
	}
	else if (execve_ret == -1)
	{
		if (ft_is_path_cmd(cmd_table->path_name) == false)
			ft_err_msg(cmd_table->path_name);
	}
	exit (g_exit_status);
}

void	ft_route_and_exec(t_cmd_table *cmd_table, t_env *env_tesh,
						t_exec *exec, t_data *data)
{
	close(exec->end[READ]);
	ft_route_stdin(cmd_table, exec);
	if (g_exit_status != OPEN_FILE_ERR)
		ft_route_stdout(cmd_table, exec);
	if (g_exit_status != OPEN_FILE_ERR && cmd_table->is_command == true)
		ft_exec(cmd_table, env_tesh, data, exec);
	ft_close_open_fds(exec, &cmd_table);
	exit(g_exit_status);
}

int	ft_create_child_prc(t_cmd_table *cmd_table, t_env *env_tesh, t_exec *exec,
						t_data *data)
{
	if (pipe(exec->end) == -1)
	{
		ft_err_msg("pipe");
		return (1);
	}
	exec->i++;
	exec->pid = fork();
	if (exec->pid == 0)
	{
		if (ft_check_single_cmd(cmd_table) == true)
			ft_exec(cmd_table, env_tesh, data, exec);
		else
			ft_route_and_exec(cmd_table, env_tesh, exec, data);
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

void	ft_executor(t_data *data)
{
	t_cmd_table	*current;
	t_exec		*exec;

	if (g_exit_status == SYNTAX_ERR || g_exit_status == ARG_REQ)
		return ;
	current = ft_lstfirst_ct(&data->cmd_table);
	if (ft_check_single_builtin(current) == true)
	{
		ft_exec_builtin(current, data->env_tesh, data);
		return ;
	}
	exec = ft_create_exec();
	ft_open_heredocs(exec, &data->cmd_table, data);
	while (current != NULL)
	{
		if (ft_create_child_prc(current, data->env_tesh, exec, data) == -1)
			ft_err_msg("fork");
		current = current->next;
	}
	ft_end_prcs(exec);
}
