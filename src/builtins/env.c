#include "../../include/minishell.h"
#include <stdlib.h>
#include <unistd.h>

int		env_error(char *command, char *errmsg)
{
	write(STDERR_FILENO, "env: ", 5);
	write(STDERR_FILENO, command, ft_strlen(command));
	write(STDERR_FILENO, ": ", 2);
	write(STDERR_FILENO, errmsg, ft_strlen(errmsg));
	write(STDERR_FILENO, "\n", 1);
	return (-1);
}

void	write_env(int fd, t_envp *envp)
{
	while(envp)
	{
		write(fd, envp->var, ft_strlen(envp->var));
		write(fd, "=", 1);
		write(fd, envp->value, ft_strlen(envp->value));
		write(fd, "\n", 1);
		envp = envp->next;
	}
}

struct s_command	*parse_env_commands(t_vars *vars)
{
	int	i;
	char	*equal;
	char	**argv;
	struct s_command *command;

	argv = vars->ast->u_data.s_command.argv;
	ft_printf("argv[0]: %s", argv[0]);
	ft_printf("argv[1]: %s", argv[1]);
	i = 1;
	command = NULL;
	// while (argv[i])
	// {
	// 	ft_printf("%i\n", i);
	// 	i++;
	// }
	// i = 1;
	while (argv[i])
	{
		equal = ft_strchr(argv[i], '=');
		if (!equal)
			break;
		//ft_printf("argv[%d]: %s\n", i, argv[i]);
		add_envp(vars->envp_ll, argv[i]);
		i++;
	}
	if(argv[i]) // fehler bei | && ||
	{
		ft_printf("try to run command %s\n", argv[i]);
		command = malloc(sizeof(struct s_command));
		command->argv = &argv[i];
		command->redirs = NULL;
	}
	return (command);
}

int	run_env(int fd, t_vars *vars, struct s_command *curr_command_node)
{
	int					pid;
	int					status;
	struct s_command	*command;

	pid = fork();
	if (pid < 0)
		env_error("fork", strerror(errno));
	if (pid == 0)
	{
		//signal handling?
		command = parse_env_commands(vars);
		if (!command)
			write_env(fd, vars->envp_ll);
		else
		{
			execute_command(vars, command, STDIN_FILENO, fd);
			free(command);
		}
		free_all(vars);
		exit(EXIT_SUCCESS);
	}
	else
	{
		signal_ignore_setup();
		waitpid(pid, &status, 0);
		signal_shell_setup();
	}
	return (0);
}
