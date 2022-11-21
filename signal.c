#include "includes/shell.h"

void	signal_handler(int signum, siginfo_t *processinfo, void *context)
{
	(void) processinfo;
	(void) context;
	// ◦ ctrl-C displays a new prompt on a new line.
	
	if (signum == SIGINT)
	{
    	rl_replace_line("", 0);
        rl_on_new_line();
        printf("\n");
    	rl_redisplay();
	}
	// ◦ ctrl-\ does nothing.
	else if (signum == SIGQUIT)
	{
		write(1, "  \b\b", 4);
		ft_printf("\n sig ctrl +  handled.");
	}
	// ◦ ctrl-D exits the shell.
	// no signal, sends EOF to stdin. detect it in lexer and exit
	return ;
}

int connect_signals()
{
    struct sigaction handling;
    handling.sa_sigaction = signal_handler;
    sigaction(SIGINT, &handling, NULL);
	sigaction(SIGQUIT, &handling, NULL);
}