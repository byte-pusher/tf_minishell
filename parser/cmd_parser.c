/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjupy <gjupy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 13:45:09 by gjupy             #+#    #+#             */
/*   Updated: 2022/11/22 19:34:26 by gjupy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

char	*find_path_str(t_env **env_tesh)
{
	t_env	*current;

	current = *env_tesh;
	if (current->var == NULL)
		return (NULL);
	while (current && ft_strncmp("PATH", current->var, 4))
		current = current->next;
	if (current == NULL)
		return (NULL);
	return (current->var + 5);
}

char	**find_path_line_and_split(t_env **env_tesh)
{
	char	*path;
	char	**pathnames;

	path = find_path_str(env_tesh);
	if (path == NULL)
		pathnames = NULL;
	else
	{
		pathnames = ft_split(path, ':');
		if (pathnames == NULL)
			exit(-1); // malloc error
	}
	return (pathnames);
}

/*
checks if user entered the command pathname.
returns true if command exists
*/
bool	check_for_input_with_path(t_cmd_table *cmd_table, char **pathnames)
{
	t_cmd_table	*first;

	if (cmd_table->cmd_args[0][0] == '/')
	{
		if (access(cmd_table->cmd_args[0], F_OK) == 0)
		{
			cmd_table->path_name = cmd_table->cmd_args[0];
			return (true);
		}
	}
	return (false);
}

int	get_cmd(t_cmd_table *cmd_table, char **pathnames)
{
	char	*tmp;
	int		i;

	i = 0;
	if (check_for_input_with_path(cmd_table, pathnames) == true)
		return (SUCCESS);
	while (pathnames && pathnames[i]) // geht trotzdem rein, falls command mit '/' nicht existiert. evtl anders handeln.
	{
		tmp = ft_strjoin(pathnames[i], "/");
		if (pathnames != NULL && tmp == NULL)
			return (MALLOC_ERR);
		cmd_table->path_name = ft_strjoin(tmp, cmd_table->cmd_args[0]);
		free(tmp);
		if (pathnames != NULL && cmd_table->path_name == NULL)
			return (MALLOC_ERR);
		if (access(cmd_table->path_name, F_OK) == 0)
			return (SUCCESS);
		free(cmd_table->path_name);
		i++;
	}
	cmd_table->path_name = NULL;
	return (CMD_NOT_FOUND);
}

void	ft_command_parser(t_cmd_table *cmd_table, t_token *token, t_data *data)
{
	char	**pathnames;

	cmd_table->cmd_args = ft_split(token->name, ' '); // add \t to split
	cmd_table->is_command = true;
	pathnames = find_path_line_and_split(&data->env_tesh);
	exit_status = get_cmd(cmd_table, pathnames);
	if (pathnames != NULL)
		ft_free_strings(&pathnames);
	if (exit_status == CMD_NOT_FOUND)
		ft_err_msg(cmd_table->cmd_args[0]);
}
