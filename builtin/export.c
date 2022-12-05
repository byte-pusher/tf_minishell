/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjupy <gjupy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 15:51:11 by rkoop             #+#    #+#             */
/*   Updated: 2022/12/05 19:33:56 by gjupy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

// add print statements for export call without var ->declare list
// export with var  without = -> in declare list but not in env list 


int		is_var_declaration(char *cmd_arg)
{
	int	i;

	i = 0;
	while (cmd_arg[i] != '\0')
	{
		if (cmd_arg[i] == '=')
			return (0);
		i++;
	}
	return (1);
}

int	comp_var_len(char *cmd_arg)
{
	int	i;

	i = 0;
	while (cmd_arg[i] != '\0')
	{
		if (cmd_arg[i] == '=')
			return (i);
		i++;
	}
	return (0);
}

//check if var already exists, if yes replace complety 
int	var_exists(char *cmd_arg, t_env *env_tesh)
{
	t_env	*current_env;
	int		var_len;

	current_env = env_tesh;
	var_len = comp_var_len(cmd_arg);
	while (current_env != NULL)
	{
		if (ft_strncmp(current_env->var, cmd_arg, var_len + 1) == 0)
		{
			ft_lstdel_env(env_tesh, current_env);
			return (0);
		}
		current_env = current_env->next;
	}
	return (1);
}

int		valid_export(char *cmd_arg)
{
	int i;

	i = 0;
	
	while (cmd_arg[i] != '\0')
	{
		if (ft_isalpha(cmd_arg[i]) == 1)
			return (1);
		i++;
	}
	return(0);
}


// //declare x functon
// void	declare_x(t_env *env_tesh)
// {
// 	//first: print env list with modifications
// 	t_env	*current_env;
// 	char	*modified_str;

// 	current_env = env_tesh;
	

// 	while(current_env)
// 	{
// 		printf("declare -x ");
// 		modified_str = malloc(sizeof(char) * ft_strlen(current_env->var) + 2);
// 		ft_strlcat(modifie)
		
		
// 	}


	
// 	//second: print additional declarex list
// }



//simple version, if var already exists, deletes elem in lst and creates new
void	ft_export(char **cmd_args, t_env *env_tesh)
{
	t_env	*node;
	t_env	*last_node;
	int		i;

	node = NULL;
	last_node = NULL;
	i = 1;

	// if (cmd_args[i] == NULL)
	// {
	// 	//print declare -x per var
	// 	//var vaue has to be quoted
	// }
	while (cmd_args[i] != NULL )
	{
		//add validity check for current cmd args
		if (is_var_declaration(cmd_args[i]) == 0)
		{
			var_exists(cmd_args[i], env_tesh);
			ft_lstadd_back_env(&env_tesh, ft_lstnew_env());
			ft_lstlast_env(env_tesh)->var = malloc(sizeof(char) * ft_strlen(cmd_args[i]));
			ft_strncpy(ft_lstlast_env(env_tesh)->var, ft_strtrim(cmd_args[i], "\"\'"), ft_strlen(ft_strtrim(cmd_args[i], "\"\'")));

		}
		// else if (valid_export(cmd_args[i]) == 0)
		// {
		// 	//add to declare x list
		// }
		// else if(valid_export(cmd_args[i]) == 1)
		// {
		// 	g_exit_status = ;
		// 	ft_err_msg("export: '%s': not a valid identifier", cmd_args[i]);
		// }
		i++;
	}
}
