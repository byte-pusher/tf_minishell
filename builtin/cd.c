/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkoop <rkoop@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 16:09:36 by rkoop             #+#    #+#             */
/*   Updated: 2022/12/07 19:24:26 by rkoop            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"


// create OLDPWD if it has been unset or non existing
char	*get_dir(t_env *env_tesh, char *var)
{
	t_env	*current_env;
	size_t	len_current_env_var;
	size_t	len_var;
	int		i;

	current_env = env_tesh;
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
void	set_oldpwd(t_env *env_tesh)
{
	t_env	*last_node;
	char	*buffer;
	
	buffer = NULL;
	ft_lstdel_env(env_tesh, get_var_node(env_tesh, "OLDPWD="));
	ft_lstadd_back_env(&env_tesh, ft_lstnew_env());
	ft_lstlast_env(env_tesh)->var = malloc(sizeof(char) * (ft_strlen(getcwd(buffer, 0)) + 8));
	ft_strncpy(ft_lstlast_env(env_tesh)->var, "OLDPWD=", ft_strlen(getcwd(buffer, 0)) + 8);
	ft_lstlast_env(env_tesh)->var = ft_strjoin(ft_lstlast_env(env_tesh)->var, getcwd(buffer, 0));
	free(buffer);
}

void	set_pwd(t_env *env_tesh)
{
	t_env	*current_env;
	char	pwd_var[] = "PWD=";
	int		len_new_pwd;
	char	*buffer;
	
	buffer = NULL;
	current_env = env_tesh;
	len_new_pwd = ft_strlen(getcwd(NULL, 0)) + 4;
	//rewrite pwd in env
	while (current_env != NULL)
	{
		if (ft_strnstr(current_env->var, pwd_var, 4) != NULL)
		{
			free(current_env->var);
			current_env->var = malloc(sizeof(char) * len_new_pwd);
			ft_strlcpy(current_env->var, pwd_var, len_new_pwd);
			ft_strlcat(current_env->var, getcwd(buffer, 0), len_new_pwd);
			free(buffer);
		}	
		current_env = current_env->next;
	}
}

void	ft_cd(char **cmd_args, t_env *env_tesh)
{
	char	*old_pwd;
	char	*home_dir;

	old_pwd = NULL;
	home_dir = NULL;
	
	if (!cmd_args[1] || env_tesh == NULL )
		return ;
	//check for - 
	if (ft_strncmp(cmd_args[1], "-", 1) == 0 &&
		get_dir(env_tesh, "$OLDPWD") != NULL)
	{
		old_pwd = get_dir(env_tesh, "$OLDPWD");
		set_oldpwd(env_tesh);
		chdir(old_pwd);
		set_pwd(env_tesh);
		return ;
	}
	if (ft_strncmp(cmd_args[1], "~", 1) == 0 &&
		get_dir(env_tesh, "$HOME") != NULL)
	{
		home_dir = get_dir(env_tesh, "$HOME");
		set_oldpwd(env_tesh);
		chdir(home_dir);
		set_pwd(env_tesh);
		return ;
	}
	//set current as old pwd
	set_oldpwd(env_tesh);
	if (chdir(cmd_args[1]) == -1)
	{
		g_exit_status = OPEN_FILE_ERR;
		//also need to pass path string that has been tried to reach
		ft_err_msg("cd: ");
		printf("%s", cmd_args[1]);
	}
	//rewrite pwd
	set_pwd(env_tesh);
}
