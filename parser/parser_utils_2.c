/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjupy <gjupy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 18:56:52 by gjupy             #+#    #+#             */
/*   Updated: 2022/12/14 11:37:20 by gjupy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

void	check_dquotes(char *str, int *i, int *status)
{
	if (str[(*i)] == '\"')
	{
		*status = DOUBLE_OPEN;
		(*i)++;
		while (str[(*i)] != '\0' && *status == DOUBLE_OPEN)
		{
			if (str[(*i)] == '\"')
				*status = DOUBLE_CLOSED;
			else
				(*i)++;
		}
	}
}

void	check_squotes(char *str, int *i, int *status)
{
	if (str[(*i)] == '\'')
	{
		*status = SINGLE_OPEN;
		(*i)++;
		while (str[(*i)] != '\0' && *status == SINGLE_OPEN)
		{
			if (str[(*i)] == '\'')
				*status = SINGLE_CLOSED;
			else
				(*i)++;
		}
	}
}

bool	ft_check_quotes(char *str)
{
	int	status;
	int	i;

	status = NON;
	i = 0;
	while (str[i] != '\0')
	{
		check_dquotes(str, &i, &status);
		check_squotes(str, &i, &status);
		if (i < ft_strlen(str))
			i++;
	}
	if (status == SINGLE_OPEN || status == DOUBLE_OPEN)
	{
		g_exit_status = SYNTAX_ERR;
		ft_err_msg("newline");
		return (true);
	}
	return (false);
}

bool	ft_check_pipe_sequence(t_token *token)
{
	if (token->next != NULL && token->type == PIPE
		&& token->next->type == PIPE)
	{
		g_exit_status = SYNTAX_ERR;
		ft_err_msg("|");
		return (true);
	}
	return (false);
}

bool	ft_check_others(t_token **token)
{
	if (((*token)->type == PIPE || ft_lstlast_t(*token)->type == PIPE))
	{
		g_exit_status = SYNTAX_ERR;
		ft_err_msg("|");
		return (true);
	}
	if ((*token)->next == NULL && ft_strlen((*token)->name) == 1
		&& ft_strncmp((*token)->name, ".", 1) == 0)
	{
		g_exit_status = ARG_REQ;
		ft_err_msg(".");
		return (true);
	}
	return (false);
}
