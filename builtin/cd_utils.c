/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkoop <rkoop@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 12:26:13 by rkoop             #+#    #+#             */
/*   Updated: 2022/12/13 14:26:00 by rkoop            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

char	*get_dir(t_env *env_tesh, char *var)
{
	t_env	*current_env;
	size_t	len_current_env_var;
	size_t	len_var;
	int		i;

	current_env = ft_lstfirst_env(&env_tesh);
	if (current_env->var == NULL)
		current_env = current_env->next;
	len_current_env_var = 0;
	len_var = (ft_strlen(var) - 1);
	i = 0;
	while (current_env != NULL)
	{
		len_current_env_var = get_var_len(current_env->var);
		if (ft_strncmp(current_env->var, var + 1, len_current_env_var)
			== 0 && var[len_current_env_var + 1] == '\0')
		{
			while (current_env->var[i] != '=')
				i++;
			return (current_env->var + ft_strlen(var));
		}
		current_env = current_env->next;
	}
	return (NULL);
}

void	set_oldpwd(t_env *env_tesh, t_data *data, char *tmp_dir)
{
	t_env	*last_node;
	char	*buffer;

	buffer = NULL;
	var_exists_del("OLDPWD=", env_tesh, data);
	ft_lstadd_back_env(&env_tesh, ft_lstnew_env());
	last_node = ft_lstlast_env(env_tesh);
	last_node->var = ft_strjoin("OLDPWD=", tmp_dir);
	free(buffer);
}

void	set_pwd(t_env *env_tesh, t_data *data)
{
	t_env	*last_node;
	t_env	*current_env;
	char	*buffer;
	char	*path_name;

	buffer = NULL;
	current_env = ft_lstfirst_env(&env_tesh);
	if (current_env->var == NULL)
		current_env = current_env->next;
	var_exists_del("PWD=", env_tesh, data);
	ft_lstadd_back_env(&env_tesh, ft_lstnew_env());
	last_node = ft_lstlast_env(env_tesh);
	path_name = getcwd(buffer, 0);
	last_node->var = ft_strjoin("PWD=", path_name);
	free(buffer);
	free(path_name);
}
