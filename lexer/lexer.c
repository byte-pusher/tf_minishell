/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkoop <rkoop@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 13:25:44 by gjupy             #+#    #+#             */
/*   Updated: 2022/11/15 13:00:35 by rkoop            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

void	ft_handle_cmd(t_data *data, int *i, int type)
{
	int		start;
	int		end;
	t_token	*new_token;

	start = *i;
	new_token = ms_lstnew(&data->tokens);
	new_token->type = type;
	while (data->input[*i] != '\0'
		&& ft_get_chartype(data->input, i) == COMMAND)
	{
		(*i)++;
		end = *i;
	}
	(*i)--;
	new_token->name = ft_substr(data->input, start, end - start);
	ms_lstadd_back(&data->tokens, new_token);
}

void	ft_handle_heredoc_and_append(t_data *data, int *i, int type)
{
	t_token	*new_token;
	char	c;

	(*i)++;
	new_token = ms_lstnew(&data->tokens);
	new_token->type = type;
	new_token->name = malloc(3);
	if (type == LESSLESS)
		c = '<';
	else if (type == GREATGREAT)
		c = '>';
	new_token->name[0] = c;
	new_token->name[1] = c;
	new_token->name[2] = '\0';
	ms_lstadd_back(&data->tokens, new_token);
}

void	ft_handle_quotes(t_data *data, int *i, int type)
{
	if (type == SQUOTE)
		ft_handle_squote(data, i, type);
	else if (type == DQUOTE)
		ft_handle_dquote(data, i, type);
}

void	ft_handle_others(t_data *data, int type, char c)
{
	t_token	*new_token;

	new_token = ms_lstnew(&data->tokens);
	new_token->type = type;
	new_token->name = malloc(2);
	new_token->name[0] = c;
	new_token->name[1] = '\0';
	ms_lstadd_back(&data->tokens, new_token);
}

int	ft_lexer(t_data *data)
{
	int	i;
	int	type;

	i = 0;
	while (data->input[i] != '\0')
	{
		while (ft_is_space(data->input[i]) == true)
			i++;
		type = ft_get_chartype(data->input, &i);
		if (type == COMMAND)
			ft_handle_cmd(data, &i, type);
		else if (type == LESSLESS || type == GREATGREAT)
			ft_handle_heredoc_and_append(data, &i, type);
		else if (type == SQUOTE || type == DQUOTE)
			ft_handle_quotes(data, &i, type);
		else if (type == PIPE || type == GREAT || type == LESS)
			ft_handle_others(data, type, data->input[i]);
		i++;
	}
	return (SUCCESS);
	// ms_print_list(&data->tokens);
}
