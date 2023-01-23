/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjupy <gjupy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 13:45:09 by gjupy             #+#    #+#             */
/*   Updated: 2022/12/14 16:42:09 by gjupy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

char	*ft_find_path_str(t_env **env_tesh)
{
	t_env	*current;

	current = *env_tesh;
	if (current->var == NULL)
		return (NULL);
	while (current && ft_strncmp("PATH", current->var, 4))
		current = current->next;
	if (current == NULL)
	{
		return (NULL);
	}
	return (current->var + 5);
}

char	**ft_find_path_line(t_env **env_tesh)
{
	char	*path;
	char	**pathnames;

	path = ft_find_path_str(env_tesh);
	if (path == NULL)
		pathnames = NULL;
	else
	{
		pathnames = ft_split(path, ':');
		if (pathnames == NULL)
			exit(ENOMEM);
	}
	return (pathnames);
}

/*
checks if user entered the command pathname.
returns true if command exists
*/
bool	ft_check_for_input_with_path(t_cmd_table *cmd_table, char **pathnames)
{
	t_cmd_table	*first;

	if (cmd_table->cmd_args[0][0] == '/')
	{
		if (access(cmd_table->cmd_args[0], F_OK) == 0)
		{
			cmd_table->path_name = ft_strdup(cmd_table->cmd_args[0]);
			if (cmd_table->path_name == NULL)
				exit(ENOMEM);
			return (true);
		}
	}
	return (false);
}

int	ft_get_cmd(t_cmd_table *cmd_table, char **pathnames)
{
	char	*tmp;
	int		i;

	i = 0;
	if (ft_check_for_input_with_path(cmd_table, pathnames) == true)
		return (SUCCESS);
	if (cmd_table->cmd_args[0][0] == '\0' || pathnames == NULL)
		return (CMD_NOT_FOUND);
	while (pathnames && pathnames[i])
	{
		tmp = ft_strjoin(pathnames[i], "/");
		if (pathnames != NULL && tmp == NULL)
			exit(ENOMEM);
		cmd_table->path_name = ft_strjoin(tmp, cmd_table->cmd_args[0]);
		free(tmp);
		if (pathnames != NULL && cmd_table->path_name == NULL)
			exit(ENOMEM);
		if (access(cmd_table->path_name, F_OK) == 0)
			return (SUCCESS);
		free(cmd_table->path_name);
		i++;
	}
	cmd_table->path_name = NULL;
	return (CMD_NOT_FOUND);
}

void	ft_command_parser(t_cmd_table *cmd_table, t_token **token, t_data *data)
{
	char	**pathnames;

	ft_create_cmd_args(cmd_table, token);
	if (ft_is_builtin(cmd_table, cmd_table->cmd_args[0]) == true)
		g_exit_status = SUCCESS;
	else
	{
		pathnames = ft_find_path_line(&data->env_tesh);
		g_exit_status = ft_get_cmd(cmd_table, pathnames);
		if (pathnames != NULL)
			ft_free_strings(&pathnames);
		if (g_exit_status == CMD_NOT_FOUND)
		{
			cmd_table->cmd_not_found = true;
			if (cmd_table->cmd_args[0][0] == '\0')
				cmd_table->path_name = "\0";
			else
				cmd_table->path_name = ft_strdup(cmd_table->cmd_args[0]);
		}
	}
}
