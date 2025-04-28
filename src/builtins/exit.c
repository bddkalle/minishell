#include "../../include/minishell.h"

int	run_exit(t_vars *vars, char **argv, int in_fd, int out_fd)
{
	int	argc;
	int	exit_code;

	argc = 0;
	while (argv[argc])
		argc++;
	if (argc == 1)
		exit_code = 0;
	else if (argc == 2)
		exit_code = ft_atoi(argv[1]);
	else
	 	return (execution_error("exit", strerror(errno), 1));
	close_fds(in_fd, out_fd);
	free_all(vars);
	write(STDOUT_FILENO, "exit\n", 5);
	exit(exit_code);
}
