/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjupy <gjupy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 13:25:44 by gjupy             #+#    #+#             */
/*   Updated: 2022/11/08 16:52:58 by gjupy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

void	ft_handle_cmd(t_data *data, int *i, int type)
{
	int		start;
	int		end;
	t_token	*new_token;

	start = *i;
	new_token = ft_lstnew(&data->tokens);
	new_token->type = type;
	while (data->input[*i] != '\0'
		&& ft_get_chartype(data->input, i) == COMMAND)
	{
		(*i)++;
		end = *i;
	}
	(*i)--;
	new_token->name = ft_substr(data->input, start, end - start);
	ft_lstadd_back(&data->tokens, new_token);
}

void	ft_handle_redirections(t_data *data, int type, char c)
{
	t_token	*new_token;

	new_token = ft_lstnew(&data->tokens);
	new_token->type = type;
	new_token->name = malloc(2);
	new_token->name[0] = c;
	new_token->name[1] = '\0';
	ft_lstadd_back(&data->tokens, new_token);
}

void	ft_handle_quotes(t_data *data, int type, char c)
{
	t_token	*new_token;

	new_token = ft_lstnew(&data->tokens);
	new_token->type = type;
	new_token->name = malloc(2);
	new_token->name[0] = c;
	new_token->name[1] = '\0';
	ft_lstadd_back(&data->tokens, new_token);
}

void	ft_handle_heredoc(t_data *data, int *i)
{
	t_token	*new_token;

	(*i)++;
	new_token = ft_lstnew(&data->tokens);
	new_token->type = LESSLESS;
	new_token->name = malloc(3);
	new_token->name[0] = '<';
	new_token->name[1] = '<';
	new_token->name[2] = '\0';
	ft_lstadd_back(&data->tokens, new_token);
}

void	ft_handle_append(t_data *data, int *i)
{
	t_token	*new_token;

	(*i)++;
	new_token = ft_lstnew(&data->tokens);
	new_token->type = GREATGREAT;
	new_token->name = malloc(3);
	new_token->name[0] = '>';
	new_token->name[1] = '>';
	new_token->name[2] = '\0';
	ft_lstadd_back(&data->tokens, new_token);
}

void	ft_handle_others(t_data *data, int type, char c)
{
	t_token	*new_token;

	new_token = ft_lstnew(&data->tokens);
	new_token->type = type;
	new_token->name = malloc(2);
	new_token->name[0] = c;
	new_token->name[1] = '\0';
	ft_lstadd_back(&data->tokens, new_token);
}

void	ft_lexer(t_data *data)
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
		else if (type == GREAT || type == LESS)
			ft_handle_redirections(data, type, data->input[i]);
		else if (type == LESSLESS)
			ft_handle_heredoc(data, &i);
		else if (type == GREATGREAT)
			ft_handle_append(data, &i);
		else if (type == SQUOTE || type == DQUOTE)
			ft_handle_quotes(data, type, data->input[i]);
		else if (type == PIPE)
			ft_handle_others(data, type, data->input[i]);
		i++;
	}
	// ft_print_list(&data->tokens);
}
