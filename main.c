/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjupy <gjupy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 14:36:04 by gjupy             #+#    #+#             */
/*   Updated: 2022/11/08 21:26:18 by gjupy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/shell.h"

int	main(void)
{
	t_data	data;
	int		exit;				// to store different error codes

	data.tokens = NULL;
	while (true)
	{
		data.input = readline(TESHNO);
		add_history(data.input);
		exit = ft_lexer(&data); // still need to handle malloc errors in ft_lexer
		if (exit == 0)
			ft_parser(&data.tokens);
	}
	clear_history();
	return (EXIT_SUCCESS);
}
