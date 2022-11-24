/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkoop <rkoop@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 12:22:58 by gjupy             #+#    #+#             */
/*   Updated: 2022/11/24 17:10:29 by rkoop            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

bool	ft_is_space(char c)
{
	if (c == ' ' || c == '\n' || c == '\t')
		return (true);
	return (false);
}

int	ft_get_chartype(char *s, int *i)
{
	if (s[*i] == '|')
		return (PIPE);
	if (s[*i] == '>')
	{
		if (s[*i + 1] == '>')
			return (GREATGREAT);
		return (GREAT);
	}
	if (s[*i] == '<')
	{
		if (s[*i + 1] == '<')
			return (LESSLESS);
		return (LESS);
	}
	if (s[*i] == '\'')
		return (SQUOTE);
	if (s[*i] == '\"')
		return (DQUOTE);
	if (s[*i] == ' ')
		return (WHITE_SPACE);
	return (GENERAL);
}

void	ft_handle_squote(t_data *data, int *i, int type)
{
	int		start;
	int		end;
	t_token	*new_token;

	start = *i;
	new_token = ft_lstnew_t();
	new_token->type = type;
	while (data->input[*i] != '\0')
	{
		(*i)++;
		end = *i;
		if (data->input[*i] == '\'')
			break ;
	}
	end++;
	new_token->name = ft_substr(data->input, start + 1, end - start - 2);
	ft_lstadd_back_t(&data->tokens, new_token);
}

void	ft_handle_dquote(t_data *data, int *i, int type)
{
	int		start;
	int		end;
	t_token	*new_token;

	start = *i;
	new_token = ft_lstnew_t();
	new_token->type = type;
	while (data->input[*i] != '\0')
	{
		(*i)++;
		end = *i;
		if (data->input[*i] == '\"')
			break ;
	}
	end++;
	new_token->name = ft_substr(data->input, start + 1, end - start - 2);
	ft_lstadd_back_t(&data->tokens, new_token);
}
