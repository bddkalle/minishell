#include "../../include/minishell.h"

void	signal_handler(int signum)
{
	global_received_signal = signum;
}

void	sigint_handler(int signum)
{
	(void)signum;
	write(STDOUT_FILENO, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}
