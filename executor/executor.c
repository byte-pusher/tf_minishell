/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjupy <gjupy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 18:49:02 by gjupy             #+#    #+#             */
/*   Updated: 2022/11/23 23:19:01 by gjupy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

// void	create_child_prcs(t_pipex *pipex, char **argv, char **env)
// {
// 	int	i;

// 	i = -1;
// 	create_pipes_arr(pipex);
// 	pipex->pids = malloc(pipex->childs * sizeof(pid_t));
// 	while (++i < pipex->childs)
// 	{
// 		pipex->pids[i] = fork();
// 		if (pipex->pids[i] == -1)
// 			break ;
// 		if (pipex->pids[i] == 0)
// 			child_prc(pipex, env, argv, i);
// 		if (pipex->here_doc == true)
// 			waitpid(pipex->pids[0], NULL, 0);
// 	}
// 	close_pipes(pipex, -1);
// 	free_pipes(&pipex->pipes, pipex->nbr_of_pipes - 1);
// }

void	ft_exec_builtin(t_cmd_table *cmd_table)
{
	if (cmd_table->builtin_type == ECHO)
		ft_echo(cmd_table->cmd_args);
}

void	ft_executor(t_data *data)
{
	t_cmd_table	*current;

	current = ft_lstfirst_ct(&data->cmd_table);
	while (current != NULL)
	{
		if (current->is_builtin == true)
			ft_exec_builtin(current);
		current = current->next;
	}
}