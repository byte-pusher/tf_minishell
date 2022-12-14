/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjupy <gjupy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 13:25:44 by gjupy             #+#    #+#             */
/*   Updated: 2022/12/13 15:51:32 by gjupy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

void	ft_handle_cmd(t_data *data, int *i, int type)
{
	t_token	*new_token;

	new_token = ft_lstnew_t();
	ft_lstadd_back_t(&data->tokens, new_token);
	if (ft_is_file_name(new_token) == true || ((new_token->prev)
			&& ft_is_file_name(new_token->prev) == true
			&& new_token->prev->mixed_quotes == true))
		new_token->type = FILE_NAME;
	else
		new_token->type = COMMAND;
	ft_cpy_string(data, new_token, i);
}

void	ft_handle_heredoc_and_append(t_data *data, int *i, int type)
{
	t_token	*new_token;
	char	c;

	(*i)++;
	new_token = ft_lstnew_t();
	new_token->type = type;
	new_token->name = malloc(3);
	if (new_token->name == NULL)
		exit(ENOMEM);
	if (type == LESSLESS)
		c = '<';
	else if (type == GREATGREAT)
		c = '>';
	new_token->name[0] = c;
	new_token->name[1] = c;
	new_token->name[2] = '\0';
	ft_lstadd_back_t(&data->tokens, new_token);
}

void	ft_handle_quotes(t_data *data, int *i, int type, char c)
{
	int		start;
	int		end;
	t_token	*new_token;

	new_token = ft_lstnew_t();
	new_token->type = type;
	start = *i;
	while (data->input[*i] != '\0')
	{
		(*i)++;
		end = *i;
		if (data->input[*i] == c)
		{
			if (data->input[(*i) + 1] != '\0'
				&& ft_is_space(data->input[(*i) + 1]) == false
				&& ft_is_redir_token(data->input[(*i) + 1]) == false)
				new_token->mixed_quotes = true;
			break ;
		}
	}
	end++;
	new_token->name = ft_substr(data->input, start + 1, end - start - 2);
	if (new_token->name == NULL)
		exit(ENOMEM);
	ft_lstadd_back_t(&data->tokens, new_token);
}

void	ft_handle_others(t_data *data, int type, char c)
{
	t_token	*new_token;

	new_token = ft_lstnew_t();
	new_token->type = type;
	new_token->name = malloc(2);
	if (new_token->name == NULL)
		exit(ENOMEM);
	new_token->name[0] = c;
	new_token->name[1] = '\0';
	ft_lstadd_back_t(&data->tokens, new_token);
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
		if (type == GENERAL)
			ft_handle_cmd(data, &i, type);
		else if (type == LESSLESS || type == GREATGREAT)
			ft_handle_heredoc_and_append(data, &i, type);
		else if (type == SQUOTE || type == DQUOTE)
			ft_handle_quotes(data, &i, type, data->input[i]);
		else if (type == PIPE || type == GREAT || type == LESS)
			ft_handle_others(data, type, data->input[i]);
		i++;
	}
}
