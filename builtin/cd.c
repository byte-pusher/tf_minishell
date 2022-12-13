/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjupy <gjupy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 16:09:36 by rkoop             #+#    #+#             */
/*   Updated: 2022/12/12 22:39:53 by gjupy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

char	*get_dir(t_env *env_tesh, char *var)
{
	t_env	*current_env;
	size_t	len_current_env_var;
	size_t	len_var;
	int		i;

	current_env = env_tesh;
	if (current_env->var == NULL)
		current_env = current_env->next;
	len_current_env_var = 0;
	len_var = (ft_strlen(var) - 1);
	i = 0;
	while (current_env != NULL)
	{
		len_current_env_var = get_var_len(current_env->var);
		if (ft_strncmp(current_env->var, var + 1, len_current_env_var)
			== 0 && var[len_current_env_var + 1] == '\0')
		{
			while (current_env->var[i] != '=')
				i++;
			return (current_env->var + ft_strlen(var));
		}
		current_env = current_env->next;
	}
	return (NULL);
}

//ft to set pwd 9in form of tmp)  as oldpwd
void	set_oldpwd(t_env *env_tesh, t_data *data, char *tmp_dir)
{
	t_env	*last_node;
	char	*buffer;

	buffer = NULL;
	var_exists_del("OLDPWD=", env_tesh, data);
	ft_lstadd_back_env(&env_tesh, ft_lstnew_env());
	ft_lstlast_env(env_tesh)->var = ft_strjoin("OLDPWD=", tmp_dir);
	free(buffer);
}

void	set_pwd(t_env *env_tesh, t_data *data)
{
	t_env	*current_env;
	char	*buffer;
	char	*path_name;

	buffer = NULL;
	path_name = getcwd(buffer, 0);
	current_env = ft_lstfirst_env(&env_tesh);
	if (current_env->var == NULL)
		current_env = current_env->next;
	var_exists_del("PWD=", env_tesh, data);
	ft_lstadd_back_env(&env_tesh, ft_lstnew_env());
	ft_lstlast_env(env_tesh)->var = ft_strjoin("PWD=", path_name);
	free(buffer);
	free(path_name);
}

int	ft_cd_flags(char flag, t_env *env_tesh, t_data *data, char *tmp_dir)
{
	char	*old_pwd;
	char	*home_dir;
	char	*buffer;

	old_pwd = NULL;
	home_dir = NULL;
	if (flag == '-' && get_dir(env_tesh, "$OLDPWD") != NULL)
	{
		old_pwd = malloc(sizeof(char) * ft_strlen(get_dir(env_tesh, "$OLDPWD") + 1));
		ft_strncpy(old_pwd, get_dir(env_tesh, "$OLDPWD"), ft_strlen(get_dir(env_tesh, "$OLDPWD") + 1));
		if (chdir(old_pwd) == 0)
		{
			set_oldpwd(env_tesh, data, tmp_dir);
			set_pwd(env_tesh, data);
			return (0);
		}	
		free(old_pwd);
	}
	else if (flag == '~' && get_dir(env_tesh, "$HOME") != NULL)
	{
		home_dir = malloc(sizeof(char) * ft_strlen(get_dir(env_tesh, "$HOME") + 1));
		ft_strncpy(home_dir, get_dir(env_tesh, "$HOME"), ft_strlen(get_dir(env_tesh, "$OLDPWD") + 1));
		if (chdir(home_dir) == 0)
		{
			set_oldpwd(env_tesh, data, tmp_dir);
			set_pwd(env_tesh, data);
			free(home_dir);
			return (0);
		}
		free(home_dir);
	}
	return (1);
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
		{
			g_exit_status = OPEN_FILE_ERR;
			ft_err_msg("cd: ");
		}
	}
	if (chdir(cmd_args[1]) == -1)
	{
		g_exit_status = OPEN_FILE_ERR;
		ft_err_msg("cd: ");
	}
	//set old pwd tp tmp
	set_oldpwd(env_tesh, data, tmp_dir);
	//rewrite pwd
	set_pwd(env_tesh, data);
	//add check for OLDPWD == PWD & remove OLDPWD?
	free(tmp_dir);
	free(buffer);
}
