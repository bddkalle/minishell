#include "../../include/minishell.h"

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

void	signal_pipe_setup(void)
{
	struct sigaction	sa_int;
	struct sigaction	sa_quit;

	sa_int.sa_handler = signal_handler_global;
	sa_int.sa_flags = 0;
	sigemptyset(&sa_int.sa_mask);
	sigaction(SIGINT, &sa_int, NULL);

	sa_quit.sa_handler = SIG_IGN;
	sa_quit.sa_flags = 0;
	sigemptyset(&sa_quit.sa_mask);
	sigaction(SIGQUIT, &sa_quit, NULL);
}

void	disable_echotcl(void)
{
	struct termios	term;

	if (tcgetattr(STDIN_FILENO, &term) == -1)
		return ;
	term.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
}

void	enable_echoctl(void)
{
	struct termios	term;

	if (tcgetattr(STDIN_FILENO, &term) == -1)
		return;
	term.c_lflag |= ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
}

void	signal_heredoc_setup(void)
{
	struct sigaction	sa_int;
	struct sigaction	sa_quit;

	sa_int.sa_handler = signal_handler_global;
	sigemptyset(&sa_int.sa_mask);
	sa_int.sa_flags = 0;
	sigaction(SIGINT, &sa_int, NULL);

	sa_quit.sa_handler = SIG_IGN;
	sa_quit.sa_flags = 0;
	sigemptyset(&sa_quit.sa_mask);
	sigaction(SIGQUIT, &sa_quit, NULL);
}

// void	signal_heredoc_readline_setup(void)
// {
// 	struct sigaction	sa_int;
// 	struct sigaction	sa_quit;

// 	rl_catch_signals = 1;
// 	rl_free_line_state();
// 	rl_cleanup_after_signal();
// 	sa_int.sa_handler = SIG_DFL;
// 	sigemptyset(&sa_int.sa_mask);
// 	sa_int.sa_flags = 0;
// 	sigaction(SIGINT, &sa_int, NULL);

// 	sa_quit.sa_handler = SIG_IGN;
// 	sa_quit.sa_flags = 0;
// 	sigemptyset(&sa_quit.sa_mask);
// 	sigaction(SIGQUIT, &sa_quit, NULL);
// }
