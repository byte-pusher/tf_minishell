/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkoop <rkoop@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 13:45:09 by gjupy             #+#    #+#             */
/*   Updated: 2022/11/28 12:20:12 by rkoop            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

// char	*find_path_str(char **env)
// {
// 	int	i;

// 	i = 0;
// 	if (env[i] == NULL)
// 		return (NULL);
// 	while (env[i] && ft_strncmp("PATH", env[i], 4))
// 		i++;
// 	if (env[i] == NULL)
// 		return (NULL);
// 	return (env[i] + 5);
// }

// void	find_path_line_and_split(char **env, t_pipex *pipex)
// {
// 	pipex->path = find_path_str(env);
// 	if (pipex->path == NULL)
// 		pipex->pathnames = NULL;
// 	else
// 	{
// 		pipex->pathnames = ft_split(pipex->path, ':');
// 		if (pipex->pathnames == NULL)
// 			exit(-1); // malloc error
// 	}
// }

// /*
// checks if user entered the command pathname.
// returns true if command exists
// */
// bool	check_for_input_with_path(t_pipex *pipex)
// {
// 	if (pipex->cmd_args[0][0] == '/')
// 	{
// 		if (access(*pipex->cmd_args, F_OK) == 0)
// 		{
// 			pipex->command = *pipex->cmd_args;
// 			return (true);
// 		}
// 		cmd_err(pipex);
// 	}
// 	return (false);
// }

// int	get_cmd(t_pipex *pipex)
// {
// 	char	*tmp;
// 	int		i;

// 	i = 0;
// 	if (check_for_input_with_path(pipex) == true)
// 		return (0);
// 	while (pipex->pathnames && pipex->pathnames[i])
// 	{
// 		tmp = ft_strjoin(pipex->pathnames[i], "/");
// 		if (pipex->pathnames != NULL && tmp == NULL)
// 			malloc_err();
// 		pipex->command = ft_strjoin(tmp, pipex->cmd_args[0]);
// 		free(tmp);
// 		if (pipex->pathnames != NULL && pipex->command == NULL)
// 			malloc_err();
// 		if (access(pipex->command, F_OK) == 0)
// 			return (0);
// 		free(pipex->command);
// 		i++;
// 	}
// 	exit_status = ;
// 	return (0);
// }

void	ft_command_parser(t_cmd_table *cmd_table, t_token *token)
{
	cmd_table->cmd_args = ft_split(token->name, ' '); // add \t to split
	cmd_table->is_command = true;
	// execute commands (or at least check If executable)
}
