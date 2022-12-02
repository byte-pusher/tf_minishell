/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkoop <rkoop@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 16:09:36 by rkoop             #+#    #+#             */
/*   Updated: 2022/11/30 18:42:08 by rkoop            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

void	ft_cd(char **cmd_args, t_env *env_tesh)
{
	t_env 	*current_env;
	char	pwd_var[] = "PWD=";
	int		len_new_pwd;
	char	*buffer;
	
	current_env = env_tesh;
	len_new_pwd = ft_strlen(getcwd(NULL, 0)) + 4;
	buffer = NULL;
	
	//check if path is valid && chdir command changes dir 
	if (chdir(cmd_args[1]) == -1)
	{
		exit_status = OPEN_FILE_ERR;
		//also need to pass path string that has been tried to reach
		ft_err_msg("cd: ");
	}
	else
	{
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
}
