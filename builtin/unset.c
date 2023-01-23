/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkoop <rkoop@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 15:28:21 by rkoop             #+#    #+#             */
/*   Updated: 2022/12/14 16:00:33 by rkoop            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

//tester
//     - unset ""
//     - unset "="
//     - unset ""=
//     - unset =""

int	valid_unset_input(char *cmd_arg)
{
	int	i;

	i = 0;
	if (cmd_arg[0] == '\0')
	{
		g_exit_status = INVALID_IDENTIFIER;
		ft_err_msg(cmd_arg);
		return (1);
	}
	while (cmd_arg[i] != '\0')
	{
		if (ft_isalpha(cmd_arg[i]) == 1 || cmd_arg[i] == '_')
			i++;
		else
		{
			g_exit_status = INVALID_IDENTIFIER;
			ft_err_msg(cmd_arg);
		}
		return (1);
	}
	return (0);
}

int	ft_get_var_len(char *s)
{
	int	i;

	i = 0;
	while (s[i] != '=')
		i++;
	return (i);
}

void	ft_unset(char **cmd_args, t_env *env_tesh, t_data *data)
{
	t_env	*current_env;
	t_env	*next_env;
	int		i;

	i = 1;
	if (data->env_exists == false)
		return ;
	while (cmd_args[i] != NULL)
	{
		valid_unset_input(cmd_args[i]);
		current_env = ft_set_head(env_tesh);
		while (current_env != NULL)
		{
			next_env = current_env->next;
			if (cmd_args[i][0] != '\0'
				&& ft_strncmp(current_env->var, cmd_args[i],
					comp_var_len(current_env->var)) == 0)
				ft_lstdel_env(data, current_env);
			current_env = next_env;
		}
		i++;
	}
	if (ft_lstsize_env(&env_tesh) <= 1)
		data->env_exists = false;
}
