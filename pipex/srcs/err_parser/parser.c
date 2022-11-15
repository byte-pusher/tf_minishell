/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjupy <gjupy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 17:18:09 by gjupy             #+#    #+#             */
/*   Updated: 2022/08/19 17:20:09 by gjupy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/pipex.h"

void	input_err_check(t_pipex *pipex, int argc, char **argv)
{
	if (argc > 1)
		is_here_doc(pipex, argv);
	if (argc < 5)
		input_err("HOW TO RUN PIPEX:\
 ./pipex infile 'cmd1 args' 'cmd2 args' ... outfile\n");
	if (pipex->here_doc == true && argc < 6)
		input_err("HOW TO RUN PIPEX WITH HERE_DOC:\
 ./pipex here_doc LIMITER 'cmd1 args' 'cmd2 args' ... outfile\n");
	if (check_cmd_strs(argv, pipex) == -1)
		input_err("argument should not be empty\n");
}
