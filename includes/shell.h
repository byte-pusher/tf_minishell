/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjupy <gjupy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 14:36:57 by gjupy             #+#    #+#             */
/*   Updated: 2022/11/07 21:19:49 by gjupy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_H
# define SHELL_H

# define PURPLE "\033[0;35m"
# define RESET "\033[0m"

# include "lexer.h"

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <limits.h>
# include <stdbool.h>
# include <errno.h>

struct s_token;

typedef struct s_data
{
	char	*input;
	struct s_token *tokens;
} t_data;

void	ft_lexer(t_data *data);
char	*ft_substr(char const *s, unsigned int start, size_t len);

#endif