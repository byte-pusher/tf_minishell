/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjupy <gjupy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 14:36:04 by gjupy             #+#    #+#             */
/*   Updated: 2022/11/09 16:47:09 by gjupy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/shell.h"

int	main(void)
{
	t_data	data;

	data.tokens = NULL;
	while (true)
	{
		data.input = readline(TESHNO);
		if (data.input[0] != '\0')
		{
			add_history(data.input);
			ft_lexer(&data);		// still need to handle malloc errors in ft_lexer
			ft_parser(&data.tokens);
		}
	}
	clear_history();
	return (EXIT_SUCCESS);
}
