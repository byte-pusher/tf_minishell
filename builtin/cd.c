/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkoop <rkoop@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 16:09:36 by rkoop             #+#    #+#             */
/*   Updated: 2022/12/12 13:19:25 by rkoop            ###   ########.fr       */
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
	len_var = ft_strlen(var);
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

//ft to get var node
t_env	*get_var_node(t_env *env_tesh, char *var)
{
	t_env	*current_env;
	size_t	len_current_env_var;
	

	current_env = env_tesh;
	if (current_env->var == NULL)
		current_env = current_env->next;
	len_current_env_var = 0;
	while (current_env != NULL)
	{
		len_current_env_var = get_var_len(current_env->var);
		if (ft_strncmp(current_env->var, var, len_current_env_var) == 0
			&& var[len_current_env_var + 1] == '\0')
		{
			return(current_env);
		}
		current_env = current_env->next;
	}
	return(NULL);
}


//ft to set pwd as oldpwd
void	set_oldpwd(t_env *env_tesh, t_data *data)
{
	t_env	*last_node;
	char	*buffer;
	
	buffer = NULL;
	
	var_exists_del("OLDPWD=", env_tesh, data);
	ft_lstadd_back_env(&env_tesh, ft_lstnew_env());
	ft_lstlast_env(env_tesh)->var = malloc(sizeof(char) * (ft_strlen(getcwd(buffer, 0)) + 8));
	ft_strncpy(ft_lstlast_env(env_tesh)->var, "OLDPWD=", ft_strlen(getcwd(buffer, 0)) + 8);
	ft_lstlast_env(env_tesh)->var = ft_strjoin(ft_lstlast_env(env_tesh)->var, getcwd(buffer, 0));
	free(buffer);
}

//leaking
void	set_pwd(t_env *env_tesh, t_data *data)
{
	t_env	*current_env;
	char	pwd_var[] = "PWD=";
	int		len_new_pwd;
	char	*buffer;
	
	buffer = NULL;
	current_env = ft_lstfirst_env(&env_tesh);
	if (current_env->var == NULL)
		current_env = current_env->next;
	len_new_pwd = ft_strlen(getcwd(NULL, 0)) + 4;
	var_exists_del(pwd_var, env_tesh, data);
	ft_lstadd_back_env(&env_tesh, ft_lstnew_env());
	ft_lstlast_env(env_tesh)->var = malloc(sizeof(char) * (ft_strlen(getcwd(buffer, 0)) + 4));
	ft_strncpy(ft_lstlast_env(env_tesh)->var, pwd_var, ft_strlen(getcwd(buffer, 0)) + 4);
	ft_lstlast_env(env_tesh)->var = ft_strjoin(ft_lstlast_env(env_tesh)->var, getcwd(buffer, 0));
	if (buffer != NULL)
		free(buffer);
}

void	ft_cd(char **cmd_args, t_env *env_tesh, t_data *data)
{
	char	*old_pwd;
	char	*home_dir;

	old_pwd = NULL;
	home_dir = NULL;
	
	if (!cmd_args[1])
		return ;
	if (ft_strncmp(cmd_args[1], "-", 1) == 0 &&
		get_dir(env_tesh, "$OLDPWD") != NULL)
	{
		
		old_pwd = get_dir(env_tesh, "$OLDPWD");
		set_oldpwd(env_tesh, data);
		//print_env(&env_tesh, data);
		chdir(old_pwd);
		set_pwd(env_tesh, data);
		return ;
	}
	if (ft_strncmp(cmd_args[1], "~", 1) == 0 &&
		get_dir(env_tesh, "$HOME") != NULL)
	{
		home_dir = get_dir(env_tesh, "$HOME");
		set_oldpwd(env_tesh, data);
		chdir(home_dir);
		set_pwd(env_tesh, data);
		return ;
	}
	//set current as old pwd
	set_oldpwd(env_tesh, data);
	if (chdir(cmd_args[1]) == -1)
	{
		g_exit_status = OPEN_FILE_ERR;
		ft_err_msg("cd: ");
	}
	//rewrite pwd
	set_pwd(env_tesh, data);
}
