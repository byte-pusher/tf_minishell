/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkoop <rkoop@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 16:09:36 by rkoop             #+#    #+#             */
/*   Updated: 2022/12/13 13:29:38 by rkoop            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

int	ft_handle_home(t_env *env_tesh, t_data *data, char *tmp_dir)
{
	char	*home_dir;

	home_dir = NULL;
	home_dir = malloc(sizeof(char) * ft_strlen(get_dir(env_tesh, "$HOME")));
	ft_strncpy(home_dir, get_dir(env_tesh, "$HOME"),
		ft_strlen(get_dir(env_tesh, "$OLDPWD")));
	if (chdir(home_dir) == 0)
	{
		set_oldpwd(env_tesh, data, tmp_dir);
		set_pwd(env_tesh, data);
		free(home_dir);
		return (0);
	}
	free(home_dir);
	return (0);
}

int	ft_cd_flags(char flag, t_env *env_tesh, t_data *data, char *tmp_dir)
{
	char	*old_pwd;
	char	*buffer;

	old_pwd = NULL;
	if (flag == '-' && get_dir(env_tesh, "$OLDPWD") != NULL)
	{
		old_pwd = malloc(sizeof(char)
				* ft_strlen(get_dir(env_tesh, "$OLDPWD")));
		ft_strncpy(old_pwd, get_dir(env_tesh, "$OLDPWD"),
			ft_strlen(get_dir(env_tesh, "$OLDPWD")));
		if (chdir(old_pwd) == 0)
		{
			set_oldpwd(env_tesh, data, tmp_dir);
			set_pwd(env_tesh, data);
			free(old_pwd);
			return (0);
		}	
		free(old_pwd);
	}
	else if (flag == '~' && get_dir(env_tesh, "$HOME") != NULL)
	{
		if (ft_handle_home(env_tesh, data, tmp_dir) == 0)
			return (0);
	}
	return (1);
}

void	ft_exit_file_error(char *path)
{
	g_exit_status = OPEN_FILE_ERR;
	ft_err_msg(ft_strjoin("cd: ", path));
}

void	ft_cd(char **cmd_args, t_env *env_tesh, t_data *data)
{
	char	*tmp_dir;
	char	*buffer;

	buffer = NULL;
	tmp_dir = getcwd(buffer, 0);
	// kann man das einfach nicht ganz am Anfang checken bevor man getcwd call ?
	if (!cmd_args[1])
	{
		free(tmp_dir);
		return ;
	}
	if (cmd_args[1][0] == '-' || cmd_args[1][0] == '~')
	{
		if (ft_cd_flags(cmd_args[1][0], env_tesh, data, tmp_dir) == 0)
			return ;
		else
			ft_exit_file_error(cmd_args[1]);
	}
	else if (chdir(cmd_args[1]) == -1)
		ft_exit_file_error(cmd_args[1]);
	set_oldpwd(env_tesh, data, tmp_dir);
	set_pwd(env_tesh, data);
	free(tmp_dir);
	free(buffer);
}
