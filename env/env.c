/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjupy <gjupy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 21:40:05 by gjupy             #+#    #+#             */
/*   Updated: 2022/11/22 15:46:18 by gjupy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

void	print_env(t_env **lst)
{
	t_env	*current;

	current = *lst;
	while (current)
	{
		printf("%s\n", current->var);
		current = current->next;
	}
}

void	ft_create_env_lst(t_env **env_tesh, char *s)
{
	t_env	*new_env;

	new_env = ft_lstnew_env();
	new_env->var = ft_strdup(s);
	ft_lstadd_back_env(env_tesh, new_env);
}

void	ft_get_env(char **env, t_env *env_tesh)
{
	int	i;

	i = 0;
	if (env[i] == NULL)
		ft_create_env_lst(&env_tesh, NULL);
	while (env[i])
	{
		ft_create_env_lst(&env_tesh, env[i]);
		i++;
	}
}
