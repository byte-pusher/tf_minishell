/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkoop <rkoop@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 15:51:11 by rkoop             #+#    #+#             */
/*   Updated: 2022/12/06 19:52:20 by rkoop            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

//check if var already exists, if yes delete
int	var_exists_del(char *cmd_arg, t_env *env_tesh)
{
	t_env	*current_env;
	int		var_len;

	current_env = env_tesh;
	var_len = comp_var_len(cmd_arg);
	while (current_env != NULL)
	{
		if(current_env->hidden == false)
		{
			if (ft_strncmp(current_env->var, cmd_arg, var_len + 1) == 0)
			{
				ft_lstdel_env(env_tesh, current_env);
				return (0);
			}
		}
		else if (current_env->hidden == true)
		{
			if (ft_strncmp(current_env->var, cmd_arg, ft_strlen(cmd_arg) == 0))
			{
				ft_lstdel_env(env_tesh, current_env);
				return (0);
			}
		}
		current_env = current_env->next;
	}
	return (1);
}

int	var_exists(char *cmd_arg, t_env *env_tesh)
{
	t_env	*current_env;
	int		var_len;

	current_env = env_tesh;
	var_len = comp_var_len(cmd_arg);
	while (current_env != NULL)
	{
		if(current_env->hidden == false)
		{
			if (ft_strncmp(current_env->var, cmd_arg, var_len + 1) == 0)
				return (0);
		}
		else if (current_env->hidden == true)
		{
			if (ft_strncmp(current_env->var, cmd_arg, ft_strlen(cmd_arg) == 0))
				return (0);
		}
		current_env = current_env->next;
	}
	return (1);
}


// //declare x functon
void	print_declare_x(t_env *env_tesh)
{
	t_env	*current_env;
	char	*modified_str;
	int		current_var_len;

	current_env = env_tesh;
	modified_str = NULL;
	current_var_len = 0;
	while(current_env != NULL)
	{
		current_var_len = ft_strlen(current_env->var);
		printf("declare -x ");
		modified_str = malloc(sizeof(char) * current_var_len + 2);
		ft_strlcpy(modified_str, current_env->var, comp_var_len(current_env->var) + 2);
		if (current_env->hidden == false)
			ft_strlcat(modified_str, "\"", current_var_len + 2);
		ft_strlcat(modified_str, current_env->var + (comp_var_len(current_env->var)+1), current_var_len + 2);
		if (current_env->hidden == false)
			ft_strlcat(modified_str, "\"", current_var_len + 3);
		printf("%s\n", modified_str);
		current_env = current_env->next;
		if (modified_str != NULL)
			free(modified_str);
	}
}

int		is_valid_input(char *cmd_arg)
{
	int	i;

	i = 0;
	if (is_var_declaration(cmd_arg) == 0)
	{
		while (cmd_arg[i] != '=')
		{
			if (ft_isalpha(cmd_arg[i]) == 1 || cmd_arg[i] == '_')
				i++;
			else
			return (1);
		}
	}
	while (cmd_arg[i] != '\0')
	{
		if (cmd_arg[i] == ')' || cmd_arg[i] == '(' || cmd_arg[i] == '&')
			return (1);
		if (cmd_arg[i] == '!')
		{
			if (is_var_declaration(cmd_arg) == 1)
				return(1);
			else if (is_var_declaration(cmd_arg) == 0 && cmd_arg[i + 1] != '\0')
				return(1);
		}
		i++;
	}
	return (0);
}


//simple version, if var already exists, deletes elem in lst and creates new
void	ft_export(char **cmd_args, t_env *env_tesh, t_data *data)
{
	t_env	*node;
	t_env	*last_node;
	int		i;

	node = NULL;
	last_node = NULL;
	i = 1;

	if (cmd_args[i] == NULL)
		print_declare_x(env_tesh);
	while (cmd_args[i] != NULL )
	{
		if (is_valid_input(cmd_args[i]) == 0)
		{
			var_exists_del(cmd_args[i], env_tesh);
			ft_lstadd_back_env(&env_tesh, ft_lstnew_env());
			ft_lstlast_env(env_tesh)->var = malloc(sizeof(char) * ft_strlen(cmd_args[i]));
			ft_strncpy(ft_lstlast_env(env_tesh)->var, ft_strtrim(cmd_args[i], "\"\'"), ft_strlen(ft_strtrim(cmd_args[i], "\"\'")));
			if (is_var_declaration(cmd_args[i]) == 1)
				ft_lstlast_env(env_tesh)->hidden = true;
		}
		// else if (is_valid_input(cmd_args[i]) == 1)
		// {
		// 	g_exit_status = ;
		// // 	//combine str for error message
		// // 	ft_err_msg("export: '%s': not a valid identifier", &cmd_args[i]);
		// }
		i++;
	}
}
