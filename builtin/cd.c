/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkoop <rkoop@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 16:09:36 by rkoop             #+#    #+#             */
/*   Updated: 2022/12/04 14:51:36 by rkoop            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

// create old pwd if not existing?
char *get_old_pwd(t_env *env_tesh, char *var)
{
	t_env	*current_env;
	size_t	len_current_env_var;
	size_t 	len_var;
	int		i;

	current_env = env_tesh;
	len_current_env_var = 0;
	len_var = ft_strlen(var);
	i = 0;

	while (current_env != NULL)
	{
		len_current_env_var = get_var_len(current_env->var);
		if (ft_strncmp(current_env->var, var + 1, len_current_env_var) == 0 && var[len_current_env_var + 1] == '\0')
		{
			while(current_env->var[i] != '=')
				i++;
			return(current_env->var + ft_strlen(var));
		}
		current_env = current_env->next;
	}
	return(NULL);
}




void	ft_cd(char **cmd_args, t_env *env_tesh)
{
	t_env 	*current_env;
	char	pwd_var[] = "PWD=";
	int		len_new_pwd;
	char	*buffer;
	char	*old_pwd;
	
	current_env = env_tesh;
	len_new_pwd = ft_strlen(getcwd(NULL, 0)) + 4;
	buffer = NULL;
	old_pwd = NULL;
	
	//check for empty input
	if (!cmd_args[1])
		return ;
	//check for - 
	if (ft_strncmp(cmd_args[1], "-", 1) == 0)
	{
		old_pwd = get_old_pwd(env_tesh, "$OLDPWD");
		len_new_pwd = ft_strlen(old_pwd);
		chdir(old_pwd);
	}
	else if (chdir(cmd_args[1]) == -1)
	{
		g_exit_status = OPEN_FILE_ERR;
		//also need to pass path string that has been tried to reach
		ft_err_msg("cd: ");
		printf("%s", cmd_args[1]);
	}
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
