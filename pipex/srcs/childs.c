/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   childs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjupy <gjupy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/06 15:23:51 by gjupy             #+#    #+#             */
/*   Updated: 2022/08/19 17:02:28 by gjupy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

static void	exec_child_prc(char *cmd, char **env, t_pipex *pipex, int i)
{
	if (dup2(pipex->fd[1], STDOUT_FILENO) == -1)
		err("stdout");
	close(pipex->fd[1]);
	if (dup2(pipex->fd[0], STDIN_FILENO) == -1)
		err("stdin");
	close(pipex->fd[0]);
	find_path_line_and_split(env, pipex);
	pipex->cmd_args = ft_split(cmd, ' ');
	if (pipex->cmd_args == NULL)
		malloc_err();
	get_cmd(pipex);
	if (execve(pipex->command, pipex->cmd_args, env) == -1)
		err("failed to execute");
}

static void	child_prc_heredoc(t_pipex *pipex)
{
	int		i;
	char	*read;
	char	*delimiter_nl;

	delimiter_nl = ft_strjoin(pipex->delimiter, "\n");
	while (true)
	{
		write(2, "> ", 2);
		read = get_next_line(STDIN_FILENO);
		if (read == NULL)
			malloc_err();
		if (ft_strncmp(read, delimiter_nl,
				ft_strlen(delimiter_nl)) == 0)
			break ;
		write(pipex->fd[1], read, ft_strlen(read));
		free(read);
	}
	close(pipex->fd[1]);
	free(delimiter_nl);
	free(read);
}

/*
checks for different conditions, what STDIN and what STDOUT must be, 
according to the pipe ends.
first and last commands set respectively STDIN and STDOUT to infile and outfile.
i - 1, because read end of vorherige pipe.
*/
static void	child_prc(t_pipex *pipex, char **env, char **argv, int i)
{
	close_pipes(pipex, i);
	if (i > 0)
		pipex->fd[0] = pipex->pipes[i - 1][0];
	if (i != pipex->childs - 1)
		pipex->fd[1] = pipex->pipes[i][1];
	if (i == 0 && pipex->here_doc == false)
		open_file(argv, pipex, in);
	if (i == pipex->childs - 1)
		open_file(argv, pipex, out);
	if (i == 0 && pipex->here_doc == true)
		child_prc_heredoc(pipex);
	if (pipex->fd[0] > 0 && pipex->fd[1] > 0)
	{
		if (pipex->here_doc == true && i == 0)
			return ;
		exec_child_prc(argv[i + 2], env, pipex, i);
	}
}

/*
pipe saves its std in and out to the fd array.
the double pointer '**pipes' saves fd[2] arrays.
after the pipe have saved the fds, we create the processes with fork().
for every cmd, we create one child process.
*/
void	create_child_prcs(t_pipex *pipex, char **argv, char **env)
{
	int	i;

	i = -1;
	create_pipes_arr(pipex);
	pipex->pids = malloc(pipex->childs * sizeof(pid_t));
	while (++i < pipex->childs)
	{
		pipex->pids[i] = fork();
		if (pipex->pids[i] == -1)
			break ;
		if (pipex->pids[i] == 0)
			child_prc(pipex, env, argv, i);
		if (pipex->here_doc == true)
			waitpid(pipex->pids[0], NULL, 0);
	}
	close_pipes(pipex, -1);
	free_pipes(&pipex->pipes, pipex->nbr_of_pipes - 1);
}
