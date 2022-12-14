/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjupy <gjupy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 13:30:17 by rkoop             #+#    #+#             */
/*   Updated: 2022/12/14 12:40:13 by gjupy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

int	i_else(t_token *token, int i, int *start)
{
	*start = i;
	i++;
	while (token->name[i] != '\0' && token->name[i] != ' '
		&& token->name[i] != '\"' && token->name[i] != '$'
		&& token->name[i] != '\'')
		i++;
	return (i);
}

int	i_if(t_token *token, int i, int *start)
{
	i++;
	*start = i;
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
		if (token->name[i] == '\'' && token->name[i + 1] == '$')
			i = i_if(token, i, &start);
		else if (token->name[i] == '$')
			i = i_else(token, i, &start);
		end = i;
		change_token_name(data, token, start, end);
		i = ft_get_next_var(token->name);
		if (i == -1)
			break ;
		continue ;
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
