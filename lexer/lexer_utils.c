/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjupy <gjupy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 12:22:58 by gjupy             #+#    #+#             */
/*   Updated: 2022/12/05 13:04:41 by gjupy            ###   ########.fr       */
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
	if (s[*i] == ' ' || s[*i] == '\t' || s[*i] == '\n')
		return (WHITE_SPACE);
	return (GENERAL);
}
