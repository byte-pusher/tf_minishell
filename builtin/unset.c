/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjupy <gjupy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 15:28:21 by rkoop             #+#    #+#             */
/*   Updated: 2022/12/08 16:06:29 by gjupy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

int	valid_unset_input(char *cmd_arg)
{
	int	i;

	i = 0;
	while (cmd_arg[i] != '\0')
	{
		if (ft_isalpha(cmd_arg[i]) == 1 || cmd_arg[i] == '_')
			i++;
		else
			return (1);
	}
	return (0);
}

void	ft_unset(char **cmd_args, t_env *env_tesh)
{
	t_env	*current_env;
	t_env	*next_env;
	int		i;

	current_env = NULL;
	i = 1;
	while (cmd_args[i] != NULL)
	{
		if (valid_unset_input(cmd_args[i]) == 1)
		{
			g_exit_status = INVALID_IDENTIFIER;
			ft_err_msg(cmd_args[i]);
		}
		current_env = ft_lstfirst_env(&env_tesh);
		while (current_env != NULL)
		{
			next_env = current_env->next;
			if (ft_strnstr(current_env->var, cmd_args[i],
					ft_strlen(current_env->var)) != NULL)
				ft_lstdel_env(env_tesh, current_env);
			current_env = next_env;
		}
		i++;
	}
}
