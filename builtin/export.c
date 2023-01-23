/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkoop <rkoop@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 15:51:11 by rkoop             #+#    #+#             */
/*   Updated: 2022/12/14 15:25:46 by rkoop            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

void	print_declare_x(t_env *env_tesh, t_data *data)
{
	t_env	*current_env;
	char	*modified_str;

	if (data->env_exists == false)
		return ;
	current_env = ft_lstfirst_env(&env_tesh);
	if (current_env->var == NULL)
		current_env = current_env->next;
	while (current_env != NULL)
	{
		printf("declare -x ");
		modified_str = malloc((ft_strlen(current_env->var) + 3));
		ft_strlcpy(modified_str, current_env->var,
			(comp_var_len(current_env->var) + 2));
		if (current_env->hidden == false)
			ft_strlcat(modified_str, "\"", ft_strlen(current_env->var) + 2);
		ft_strlcat(modified_str, current_env->var
			+ (comp_var_len(current_env->var) + 1),
			ft_strlen(current_env->var) + 2);
		if (current_env->hidden == false)
			ft_strlcat(modified_str, "\"", ft_strlen(current_env->var) + 3);
		printf("%s\n", modified_str);
		current_env = current_env->next;
		free(modified_str);
	}
}

int	check_exclamation(char *cmd_arg, int i)
{
	if (cmd_arg[i] == '!' && is_var_declaration(cmd_arg) == 1
		|| (cmd_arg[i] == '!' && is_var_declaration(cmd_arg) == 0
			&& cmd_arg[i + 1] != '\0'))
		return (0);
	else
		return (1);
}

int	is_valid_input(char *cmd_arg)
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
		if (i < 1)
			return (1);
	}
	while (cmd_arg[i] != '\0')
	{
		if (cmd_arg[i] == ')' || cmd_arg[i] == '('
			|| cmd_arg[i] == '&' || cmd_arg[i] == '+')
			return (1);
		if (check_exclamation(cmd_arg, i) == 0)
			return (1);
		i++;
	}
	return (0);
}

void	ft_create_env_var(char **cmd_args, t_env *env_tesh, t_data *data, int i)
{
	char	*tmp_trim;

	tmp_trim = NULL;
	tmp_trim = ft_strtrim(cmd_args[i], "\"\'");
	var_exists_del(cmd_args[i], env_tesh, data);
	ft_lstadd_back_env(&env_tesh, ft_lstnew_env());
	ft_lstlast_env(env_tesh)->var = malloc(ft_strlen(cmd_args[i]) + 1);
	ft_strncpy(ft_lstlast_env(env_tesh)->var, tmp_trim,
		ft_strlen(tmp_trim));
	if (is_var_declaration(cmd_args[i]) == 1)
		ft_lstlast_env(env_tesh)->hidden = true;
	data->env_exists = true;
	free(tmp_trim);
}

void	ft_export(char **cmd_args, t_env *env_tesh, t_data *data)
{
	char	*tmp_trim;
	int		i;

	i = 1;
	tmp_trim = NULL;
	if (cmd_args[i] == NULL)
		print_declare_x(env_tesh, data);
	while (cmd_args[i] != NULL )
	{
		if (is_valid_input(cmd_args[i]) == 0)
		{
			if (is_var_declaration(cmd_args[i]) == 0
				|| var_exists(cmd_args[i], env_tesh, data) == 1)
				ft_create_env_var(cmd_args, env_tesh, data, i);
		}
		else if (is_valid_input(cmd_args[i]) == 1)
		{
			g_exit_status = INVALID_IDENTIFIER;
			ft_err_msg(cmd_args[i]);
		}
		i++;
	}
}
