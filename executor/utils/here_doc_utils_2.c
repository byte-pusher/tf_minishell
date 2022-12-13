/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_utils_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjupy <gjupy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 17:13:43 by gjupy             #+#    #+#             */
/*   Updated: 2022/12/13 12:48:21 by gjupy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell.h"

// void	ft_expand_read(t_heredoc *heredoc, t_data *data)
// {
// 	int		i;
// 	int		start;
// 	int		end;

// 	i = 0;
// 	start = 0;
// 	end = 0;
// 	// if (ft_is_double_dollar(heredoc->read) == true)
// 	// {
// 	// 	free(heredoc->read);
// 	// 	heredoc->read = ft_strdup("$");
// 	// 	return ;
// 	// }
// 	while (heredoc->read[i] != '\0')
// 	{
// 		if (heredoc->read[i] == '$')
// 		{
// 			start = i;
// 			i++;
// 			while (heredoc->read[i] != '\0' && heredoc->read[i] != ' '
// 				&& heredoc->read[i] != '$' && heredoc->read[i] != '\"'
// 				&& heredoc->read[i] != '\'')
// 				i++;
// 			end = i;
// 			change_read_name(data, heredoc, start, end);
// 			i = ft_get_next_var(heredoc->read);
// 			if (i == -1)
// 				break ;
// 			// else if (heredoc->read[i + 1] == '\0')
// 			// {
// 			// 	change_read_name(data, heredoc, ft_strlen(heredoc->read) - 1,
// 			// 					ft_strlen(heredoc->read));
// 			// 	break ;
// 			// }
// 			// else if (ft_no_var_left(heredoc->read, i) == true)
// 			// 	break ;
// 			continue ;
// 		}
// 		i++;
// 	}
// 	i = 0;
// 	while (heredoc->read[i])
// 	{
// 		if (heredoc->read[i] == 127)
// 			heredoc->read[i] = '$';
// 		i++;
// 	}
// }

bool	ft_is_delimiter(char c)
{
	if (c == '\0' || c == ' ' || c == '$' || c == '\"' || c == '\'')
		return (true);
	else
		return (false);
}

char	*get_value_hd(t_data *data, char *var, bool *is_env_var)
{
	t_env	*current_env;
	size_t	len_current_env_var;
	size_t	len_var;
	int		i;

	current_env = ft_lstfirst_env(&data->env_tesh);
	len_var = ft_strlen(var);
	i = 0;
	if (len_var == 1 && ft_strncmp("$", var, 1) == 0)
		return (ft_strdup("$"));
	if (ft_strncmp("?", var + 1, get_var_len(current_env->var)) == 0)
		return (ft_itoa(g_exit_status));
	while (current_env != NULL)
	{
		len_current_env_var = get_var_len(current_env->var);
		if (ft_strncmp(current_env->var, var + 1, len_current_env_var) == 0
			&& var[len_current_env_var + 1] == '\0')
		{
			while (current_env->var[i] != '=')
				i++;
			return (*is_env_var = true, current_env->var + ft_strlen(var));
		}
		current_env = current_env->next;
	}
	return (NULL);
}

void	insert_value_hd(t_heredoc *heredoc, char *read_sub, char *value,
						int start)
{
	size_t	len_token_name;
	size_t	len_value;
	char	*new_read;

	len_token_name = ft_strlen(heredoc->read);
	len_value = ft_strlen(value) + 1;
	ft_str_remove(heredoc->read, read_sub);
	new_read = malloc(sizeof(char) * (len_token_name + len_value));
	if (new_read == NULL)
		exit(ENOMEM);
	ft_strlcpy(new_read, heredoc->read, start + 1);
	ft_strlcat(new_read, value, (len_token_name + len_value));
	ft_strlcat(new_read, heredoc->read + start, (len_token_name + len_value));
	if (heredoc->read != NULL)
	{
		free(heredoc->read);
		heredoc->read = ft_strdup(new_read);
	}
	free(new_read);
}

void	change_read_name(t_data *data, t_heredoc *heredoc, int start, int end)
{
	char	*variable;
	char	*value;
	bool	is_env_var;

	is_env_var = false;
	variable = NULL;
	value = NULL;
	variable = ft_substr(heredoc->read, start, (end - start));
	if (variable == NULL)
		exit(ENOMEM);
	value = get_value_hd(data, variable, &is_env_var);
	if (value != NULL)
	{
		if (value[0] == '$')
			value[0] = 127;
		insert_value_hd(heredoc, variable, value, start);
	}
	else
		ft_str_remove(heredoc->read, variable);
	if (is_env_var == false)
		free(value);
	free(variable);
}

void	ft_expand_read(t_heredoc *heredoc, t_data *data)
{
	int		i;
	int		start;
	int		end;

	i = 0;
	start = 0;
	end = 0;
	while (heredoc->read[i] != '\0')
	{
		if (heredoc->read[i] == '$')
		{
			start = i;
			i++;
			while (ft_is_delimiter(heredoc->read[i]) == false)
				i++;
			end = i;
			change_read_name(data, heredoc, start, end);
			i = ft_get_next_var(heredoc->read);
			if (i == -1)
				break ;
			continue ;
		}
		i++;
	}
	ft_insert_dollars(heredoc->read);
}
