/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkoop <rkoop@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 18:49:02 by gjupy             #+#    #+#             */
/*   Updated: 2022/11/30 20:27:22 by gjupy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

int	ft_exec_builtin(t_cmd_table *cmd_table, t_env *env_tesh, t_data *data)
{
	if (cmd_table->builtin_type == ECHO)
		ft_echo(cmd_table->cmd_args);
	if (cmd_table->builtin_type == UNSET)
		ft_unset(cmd_table->cmd_args, env_tesh);
	if (cmd_table->builtin_type == ENV)
		print_env(&env_tesh);
	if (cmd_table->builtin_type == CD)
		ft_cd(cmd_table->cmd_args, env_tesh);
	if (cmd_table->builtin_type == PWD)
		ft_pwd();
	if (cmd_table->builtin_type == EXPORT)
		ft_export(cmd_table->cmd_args, env_tesh);
	return (SUCCESS);
}

void	ft_exec(t_cmd_table *cmd_table, t_env *env_tesh, t_data *data)
{
	char	**env_arr;

	env_arr = ft_get_env_arr(env_tesh);
	if (cmd_table->is_command == true && cmd_table->is_builtin == false)
		exit_status = execve(cmd_table->path_name, cmd_table->cmd_args, env_arr); // noch entscheiden wie ich mit den errors umgehe	
	else
	{
		exit_status = ft_exec_builtin(cmd_table, env_tesh, data);
		exit (SUCCESS);
	}
}

void	ft_create_child_prc(t_cmd_table *cmd_table, t_env *env_tesh, t_exec *exec, t_data *data)
{
	exec->i++;
	pipe(exec->end); 	// noch entscheiden wie ich mit den errors umgehe
	exec->pid = fork(); // noch entscheiden wie ich mit den errors umgehe
	if (exec->pid == 0)
	{
		if (ft_check_single_cmd(cmd_table) == true)
			ft_exec(cmd_table, env_tesh);
		else
		{
			close(exec->end[READ]); // das hat cat|cat|ls gefixt
			ft_route_stdin(cmd_table, exec);
			if (exit_status != OPEN_FILE_ERR)
				ft_route_stdout(cmd_table, exec);
			if (exit_status != OPEN_FILE_ERR && cmd_table->is_command == true)
				ft_exec(cmd_table, env_tesh);
			exit(exit_status); // ändern zu system code
		}
	}
	// close(exec->tmp_fd);
	dup2(exec->end[READ], exec->tmp_fd);
	// pipe ends need to be closed in the main process
	close(exec->end[READ]);
	close(exec->end[WRITE]);
}

void	ft_end_prcs(t_exec	*exec)
{
	close(exec->tmp_fd);
	close(exec->stout);
	while (exec->i > 0)
	{
		waitpid(0, &exec->pid, 0);
		if (WIFEXITED(exec->pid) == true)
			exit_status = WEXITSTATUS(exec->pid);
		exec->i--;
	}
	free(exec);
}

void	ft_open_heredocs(t_exec *exec, t_cmd_table **cmd_table)
{
	t_cmd_table	*current;

	current = ft_lstfirst_ct(cmd_table);
	while (current != NULL)
	{
		if (current->is_redir == true && ft_is_heredoc(&current->redir) == true)
			ft_heredoc(exec, current);
		current = current->next;
	}
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
		ft_exec_builtin(current, data->env_tesh, data);
		return ;
	}
	exec = ft_create_exec();
	ft_open_heredocs(exec, &data->cmd_table);
	while (current != NULL)
	{
		if (current->is_command == false)
		{
			current = current->next;
			continue ;
		}
		else
			ft_create_child_prc(current, data->env_tesh, exec, data);
		if (exit_status < 0)
			break ;
		current = current->next;
	}
	ft_end_prcs(exec);
}
