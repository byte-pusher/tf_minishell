/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjupy <gjupy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 23:00:36 by gjupy             #+#    #+#             */
/*   Updated: 2022/12/13 12:54:46 by gjupy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

void	ft_cpy_string(t_data *data, t_token *new_token, int *i)
{
	int		start;
	int		end;
	char	*tmp_name;

	start = *i;
	while (data->input[*i] != '\0'
		&& (ft_get_chartype(data->input, i) == GENERAL))
	{
		(*i)++;
		end = *i;
	}
	if (data->input[*i] == '\"' || data->input[*i] == '\'')
		new_token->mixed_quotes = true;
	(*i)--;
	tmp_name = ft_substr(data->input, start, end - start);
	new_token->name = ft_strtrim(tmp_name, "\t\n ");
	free(tmp_name);
}
