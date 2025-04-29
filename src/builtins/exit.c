#include "../../include/minishell.h"
#include <unistd.h>

void	exit_error(char *arg, char *errmsg)
{
	write(STDERR_FILENO, "minishell: ", 11);
	write(STDERR_FILENO, arg, ft_strlen(arg));
	write(STDERR_FILENO, ": ", 2);
	write(STDERR_FILENO, errmsg, ft_strlen(errmsg));
	write(STDERR_FILENO, "\n", 1);
}

int	check_exit_parent(t_vars *vars)
{
	if (vars->ast->type == AST_COMMAND)
		if (ft_strcmp(vars->ast->u_data.s_command.argv[0], "exit") == 0)
			return (run_exit(vars, vars->ast->u_data.s_command.argv, STDIN_FILENO, STDOUT_FILENO, 1));
	return (0);
}

int	string_is_numeric(char *s)
{
	while(*s)
	{
		if (!ft_isdigit(*s))
			return (0);
		s++;
	}
	return (1);
}

int	run_exit(t_vars *vars, char **argv, int in_fd, int out_fd, int parent)
{
	int	argc;
	int	exit_code;

	argc = 0;
	while (argv[argc])
		argc++;
	if (argc == 1)
		exit_code = 0;
	else if (argc == 2)
	{
		if (!string_is_numeric(argv[1]))
			exit_code = 2;
		else
			exit_code = ft_atoi(argv[1]);
	}
	else
	 	return (execution_error("exit", strerror(errno), 1));
	if (parent)
		write(STDOUT_FILENO, "exit\n", 5);
	if (exit_code == 2)
		exit_error(argv[1], "numeric argument required");
	close_fds(in_fd, out_fd);
	free_all(vars);
	exit(exit_code % 256);
}
