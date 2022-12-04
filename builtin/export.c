/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkoop <rkoop@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 15:51:11 by rkoop             #+#    #+#             */
/*   Updated: 2022/12/04 12:33:38 by rkoop            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

//add feature for existing vars, is del and new creation fine?
//also works in dquotes and squotes
int		is_var_declaration(char *cmd_arg)
{
	int 	i;
	
	i = 0;
	while(cmd_arg[i] != '\0')
	{
		if (cmd_arg[i] == '=')
			return(0);
		i++;
	}
	return(1);
}

int		comp_var_len(char *cmd_arg)
{
	int 	i;
	
	i = 0;
	while(cmd_arg[i] != '\0')
	{
		if (cmd_arg[i] == '=')
			return(i);
		i++;
	}
	return(0);
}

//check if var already exists, if yes replace complety 
int		var_exists(char *cmd_arg, t_env *env_tesh)
{
	t_env	*current_env;
	int		var_len;
	
	current_env = env_tesh;
	var_len = comp_var_len(cmd_arg);
	while(current_env != NULL)
	{
		if (ft_strncmp(current_env->var, cmd_arg, var_len + 1 ) == 0)
		{
			ft_lstdel_env(env_tesh, current_env);
			return(0);
		}
		current_env = current_env->next;
	}
	return(1);
}

//simple version, if var already exists, deletes elem in lst and creates new
void	ft_export(char **cmd_args, t_env *env_tesh)
{
	t_env	*node;
	t_env	*last_node;
	int		i;

	node = NULL;
	last_node = NULL;
	i = 1;
	
	while (cmd_args[i] != NULL )
	{
		if (is_var_declaration(cmd_args[i]) == 0)
		{
			var_exists(cmd_args[i], env_tesh);
			ft_lstadd_back_env(&env_tesh, ft_lstnew_env());
			ft_lstlast_env(env_tesh)->var = malloc(sizeof(char) * ft_strlen(cmd_args[i]));
			ft_strncpy(ft_lstlast_env(env_tesh)->var, ft_strtrim(cmd_args[i], "\"\'"), ft_strlen(cmd_args[i]));
		}
		i++;
	}
}
