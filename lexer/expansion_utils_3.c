/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils_3.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkoop <rkoop@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 12:32:58 by rkoop             #+#    #+#             */
/*   Updated: 2022/12/13 12:43:31 by rkoop            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

char	*get_value(t_data *data, char *var, bool *is_env_var)
{
	t_env	*current_env;
	int		i;

	if (ft_lstfirst_env(&data->env_tesh)->var == NULL)
		return (NULL);
	current_env = ft_set_head(data->env_tesh);
	i = 0;
	if (ft_strlen(var) == 1 && ft_strncmp("$", var, 1) == 0)
		return (ft_strdup("$"));
	if (ft_strncmp("?", var + 1, get_var_len(current_env->var)) == 0)
		return (ft_itoa(g_exit_status));
	while (current_env != NULL)
	{
		if (ft_strncmp(current_env->var, var + 1,
				get_var_len(current_env->var)) == 0
			&& var[get_var_len(current_env->var) + 1] == '\0')
		{
			while (current_env->var[i] != '=')
				i++;
			*is_env_var = true;
			return (current_env->var + ft_strlen(var));
		}
		current_env = current_env->next;
	}
	return (NULL);
}

void	insert_value(t_token *token, char *var, char *value, int start)
{
	size_t	len_token_name;
	size_t	len_value;
	char	*name_expanded;

	name_expanded = NULL;
	len_token_name = ft_strlen(token->name);
	len_value = ft_strlen(value);
	ft_str_remove(token->name, var);
	name_expanded = malloc(sizeof(char) * (len_token_name + len_value));
	if (name_expanded == NULL)
		exit(ENOMEM);
	ft_strlcpy(name_expanded, token->name, start + 1);
	ft_strlcat(name_expanded, value, (len_token_name + len_value));
	ft_strlcat(name_expanded, token->name + start,
		(len_token_name + len_value));
	if (token->name != NULL)
	{
		free(token->name);
		token->name = ft_strtrim(name_expanded, "\"");
	}
	free(name_expanded);
}

void	change_token_name(t_data *data, t_token *token, int start, int end)
{
	char	*variable;
	char	*value;
	bool	is_env_var;

	is_env_var = false;
	variable = NULL;
	value = NULL;
	variable = ft_substr(token->name, start, (end - start));
	if (variable == NULL)
		exit(ENOMEM);
	value = get_value(data, variable, &is_env_var);
	if (value != NULL)
	{
		if (value[0] == '$')
			value[0] = 127;
		insert_value(token, variable, value, start);
	}
	else
		ft_str_remove(token->name, variable);
	if (is_env_var == false)
		free(value);
	free(variable);
}
