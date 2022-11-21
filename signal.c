#include "includes/shell.h"

void signal_handler(int signum)
{
	// ◦ ctrl-C displays a new prompt on a new line.
	if (signum == SIGINT)
	{
		//printf("\n%s",rl_line_buffer);
		rl_replace_line("", 0);
		rl_redisplay();
		write(2, "\n", 1);
		rl_on_new_line();
		rl_redisplay();
	}
	// ◦ ctrl-D exits the shell.
	// no signal, sends EOF to stdin. detect it in lexer and exit
	return;
}

void connect_signals()
{
	//connects to function signal_handler
	signal(SIGINT, signal_handler);
	//silences signal
	signal(SIGQUIT, SIG_IGN);
}
