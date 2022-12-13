/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjupy <gjupy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 12:22:58 by gjupy             #+#    #+#             */
/*   Updated: 2022/12/12 23:01:55 by gjupy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

bool	ft_is_space(char c)
{
	if (c == ' ' || c == '\n' || c == '\t')
		return (true);
	else
		return (false);
}

bool	ft_is_redir_token(char c)
{
	if (c == '>' || c == '<')
		return (true);
	else
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
	if (s[*i] == ' ' || s[*i] == '\t' || s[*i] == '\n')
		return (WHITE_SPACE);
	return (GENERAL);
}

bool	ft_is_file_name(t_token *new_token)
{
	if (new_token->prev != NULL
		&& (new_token->prev->type == GREAT
			|| new_token->prev->type == GREATGREAT
			|| new_token->prev->type == LESS
			|| new_token->prev->type == LESSLESS))
		return (true);
	return (false);
}
