/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjupy <gjupy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 14:36:04 by gjupy             #+#    #+#             */
/*   Updated: 2022/11/07 21:05:40 by gjupy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/shell.h"

int main (void)
{
	t_data	data;

	data.tokens = NULL;
	while (true)
	{
		data.input = readline("teshno>");
		ft_lexer(&data);
	}
	return (EXIT_SUCCESS);
}