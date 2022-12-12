/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_short.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkoop <rkoop@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 13:30:17 by rkoop             #+#    #+#             */
/*   Updated: 2022/12/12 21:29:22 by rkoop            ###   ########.fr       */
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

int	is_in_set(char a, char *set)
{
	unsigned int	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == a)
			return (0);
		i++;
	}
	return (1);
}

int	i_else(t_token *token, int i)
{
	i++;
	while (token->name[i] != '\0' && token->name[i] != ' '
		&& token->name[i] != '\"' && token->name[i] != '$'
		&& token->name[i] != '\'')
		i++;
	return (i);
}

int	i_if(t_token *token, int i)
{
	while (token->name[i] != '\0' && token->name[i] != '\''
		&& token->name[i] != ' ')
	{
		i++;
		if (token->name[i] == '$')
			break ;
	}
	return (i);
}

void	expand_tokens(t_data *data, t_token *token)
{
	int		i;
	int		start;
	int		end;

	i = 0;
	start = 0;
	end = 0;
	while (token->name[i] != '\0')
	{
		if (token->name[i] == '$' || ((token->name[i] == '\''
			&& token->name[i + 1] == '$')))
		{
			if (token->name[i] == '\'' && token->name[i + 1] == '$')
			{
				i++;
				start = i;
				i = i_if(token, i);
			}
			else
			{
				start = i;
				i = i_else(token, i);
			}
			end = i;
			change_token_name(data, token, start, end);
			i = ft_get_next_var(token->name);
			if (i == -1)
				break ;
			continue ;
		}
		i++;
	}
	ft_insert_dollars(token->name);
}

void	expansion(t_data *data)
{
	t_token	*current_token;

	current_token = data->tokens;
	while (current_token != NULL)
	{
		if ((current_token->type == DQUOTE || current_token->type == COMMAND)
			&& ft_is_var(current_token->name) == true)
		{
			if (current_token->prev != NULL
				&& current_token->prev->type == LESSLESS)
			{
				current_token = current_token->next;
				continue ;
			}
			expand_tokens(data, current_token);
		}
		current_token = current_token->next;
	}
}
