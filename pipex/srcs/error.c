/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjupy <gjupy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/24 17:32:44 by aiarinov          #+#    #+#             */
/*   Updated: 2022/08/22 10:40:26 by gjupy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	cmd_err(t_pipex *pipex)
{
	write(STDERR_FILENO, "\033[31mERROR 🙁\n\033[0m", 21);
	write(STDERR_FILENO, "command not found: ", 20);
	write(STDERR_FILENO, pipex->cmd_args[0], ft_strlen(pipex->cmd_args[0]));
	write(STDERR_FILENO, "\n", 1);
	exit(EXIT_FAILURE);
}

void	malloc_err(void)
{
	write(STDERR_FILENO, "\033[31mERROR 🙁\n\033[0m", 21);
	perror("failed to allocate mem");
	exit(EXIT_FAILURE);
}

void	input_err(char *msg)
{
	write(STDERR_FILENO, "\033[31mERROR 🙁\n\033[0m", 21);
	write(STDERR_FILENO, msg, ft_strlen(msg));
	exit(EXIT_FAILURE);
}

void	err(char *msg)
{
	write(STDERR_FILENO, "\033[31mERROR 🙁\n\033[0m", 21);
	perror(msg);
	exit(EXIT_FAILURE);
}
