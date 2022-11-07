/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjupy <gjupy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 13:26:52 by gjupy             #+#    #+#             */
/*   Updated: 2022/11/07 21:30:59 by gjupy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
#define LEXER_H

#include "shell.h"

enum e_TOKEN_TYPE
{
	PIPE,
	GREAT,
	LESS,
	GREATGREAT,
	LESSLESS,
	SQUOTE,
	DQUOTE,
	COMMAND
};

typedef struct s_token
{
	char			*name;
	int				end;
	int				type;
	struct s_token	*next;
	struct s_token	*prev;
}	t_token;

#endif