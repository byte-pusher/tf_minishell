/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkoop <rkoop@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 12:03:04 by rkoop             #+#    #+#             */
/*   Updated: 2022/12/14 16:02:57 by rkoop            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

int	var_exists_del(char *cmd_arg, t_env *env_tesh, t_data *data)
{
	t_env	*current_env;
	int		var_len;

	if (data->env_exists == false)
		return (1);
	current_env = ft_set_head(env_tesh);
	var_len = comp_var_len(cmd_arg);
	while (current_env != NULL)
	{
		if (current_env->hidden == false
			&& ft_strncmp(current_env->var, cmd_arg, var_len + 1) == 0)
		{
			ft_lstdel_env(data, current_env);
			return (0);
		}
		else if (current_env->hidden == true
			&& ft_strncmp(current_env->var, cmd_arg, var_len) == 0)
		{
			ft_lstdel_env(data, current_env);
			return (0);
		}
		current_env = current_env->next;
	}
	return (1);
}

int	var_exists(char *cmd_arg, t_env *env_tesh, t_data *data)
{
	t_env	*current_env;
	int		var_len;

	if (data->env_exists == false)
		return (1);
	current_env = ft_lstfirst_env(&env_tesh);
	if (current_env->var == NULL)
		current_env = current_env->next;
	var_len = comp_var_len(cmd_arg);
	while (current_env != NULL)
	{
		if (current_env->hidden == false)
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
