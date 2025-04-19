#include "../../include/minishell.h"

void	signal_handler_global(int signum)
{
	global_received_signal = signum;
}

void	sigint_shell_handler(int signum)
{
	global_received_signal = signum;
	write(STDOUT_FILENO, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	sigint_heredoc_handler(int signum)
{
	global_received_signal = signum;
	// rl_replace_line("", 0);
	// rl_on_new_line();
	// rl_redisplay();
	rl_done = 1;
}

void	signal_heredoc_setup(void)
{
	struct sigaction	sa_int;
	struct sigaction	sa_int_old;
	struct sigaction	sa_quit;

	sa_int.sa_handler = sigint_heredoc_handler;
	sigemptyset(&sa_int.sa_mask);
	sa_int.sa_flags = 0;
	sigaction(SIGINT, &sa_int, &sa_int_old);

	sa_quit.sa_handler = SIG_IGN;
	sa_quit.sa_flags = 0;
	sigemptyset(&sa_quit.sa_mask);
	sigaction(SIGQUIT, &sa_quit, NULL);
}

void	signal_shell_setup(void)
{
	struct sigaction	sa_int;
	struct sigaction	sa_quit;

	sa_int.sa_handler = sigint_shell_handler;
	sigemptyset(&sa_int.sa_mask);
	sa_int.sa_flags = 0;
	sigaction(SIGINT, &sa_int, NULL);

	//sa_quit.sa_handler = signal_handler_global;
	sa_quit.sa_handler = SIG_IGN;
	sa_quit.sa_flags = 0;
	sigemptyset(&sa_quit.sa_mask);
	sigaction(SIGQUIT, &sa_quit, NULL);
}

void	signal_executable_setup(void)
{
	struct sigaction	sa_int;
	struct sigaction	sa_quit;

	sa_int.sa_handler = SIG_DFL;
	sa_int.sa_flags = 0;
	sigemptyset(&sa_int.sa_mask);
	sigaction(SIGINT, &sa_int, NULL);

	sa_quit.sa_handler = SIG_DFL;
	sa_quit.sa_flags = 0;
	sigemptyset(&sa_quit.sa_mask);
	sigaction(SIGQUIT, &sa_quit, NULL);
}
