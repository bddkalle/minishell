#include "../../include/minishell.h"

void	close_fds(int in_fd, int out_fd)
{
	if (in_fd != STDIN_FILENO && in_fd != -1)
		close (in_fd);
	if (out_fd != STDOUT_FILENO && out_fd != -1)
		close (out_fd);
	return ;
}

int	execution_error(char *command, char *errmsg)
{
	write(STDERR_FILENO, "minishell: ", 11);
	write(STDERR_FILENO, command, ft_strlen(command));
	write(STDERR_FILENO, ": ", 2);
	write(STDERR_FILENO, errmsg, ft_strlen(errmsg));
	write(STDERR_FILENO, "\n", 1);
	return (-1);
}

void	fatal_error(t_vars *vars, char *errmsg)
{
	write(STDERR_FILENO, "minishell: ", 11);
	write(STDERR_FILENO, errmsg, ft_strlen(errmsg));
	write(STDERR_FILENO, "\n", 1);
	free_all(vars);
	exit(EXIT_FAILURE);
}

int	env_error(char *command, char *errmsg)
{
	write(STDERR_FILENO, "env: ", 5);
	write(STDERR_FILENO, command, ft_strlen(command));
	write(STDERR_FILENO, ": ", 2);
	write(STDERR_FILENO, errmsg, ft_strlen(errmsg));
	write(STDERR_FILENO, "\n", 1);
	return (-1);
}

int	env_fatal_error(t_vars *vars, char *command, char *errmsg, int fd)
{
	write(STDERR_FILENO, "env: ", 5);
	write(STDERR_FILENO, command, ft_strlen(command));
	write(STDERR_FILENO, ": ", 2);
	write(STDERR_FILENO, errmsg, ft_strlen(errmsg));
	write(STDERR_FILENO, "\n", 1);
	close(fd);
	free_all(vars);
	exit(EXIT_FAILURE);
}
