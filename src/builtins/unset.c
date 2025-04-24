#include "../../include/minishell.h"

int	unset_error(char *command, char *var, char *errmsg)
{
	write(STDERR_FILENO, "minishell: ", 11);
	write(STDERR_FILENO, command, ft_strlen(command));
	write(STDERR_FILENO, ": ", 2);
	write(STDERR_FILENO, var, ft_strlen(var));
	write(STDERR_FILENO, ": ", 2);
	write(STDERR_FILENO, errmsg, ft_strlen(errmsg));
	return (-1);
}

int	run_unset(t_vars *vars, char **argv)
{
	int	i;

	i = 1;
	while (argv[i])
	{

		i++;
	}
	return (0);
}
