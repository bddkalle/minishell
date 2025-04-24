#include "../../include/minishell.h"
#include <string.h>

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

struct s_command	*parse_env_commands(t_vars *vars, char **argv)
{
	int					i;
	char				*equal;
	struct s_command	*command;
	t_envp				*temp;

	i = 1;
	command = NULL;
	while (argv[i])
	{
		equal = ft_strchr(argv[i], '=');
		if (!equal)
			break;
		temp = create_envp_node(vars, argv[i]);
		if (!temp)
		{
			env_error("malloc", strerror(errno)); // not finished
			return (NULL);
		}
		add_or_replace_envp(vars, temp);
		i++;
	}
	if(argv[i])
	{
		command = malloc(sizeof(struct s_command));
		command->argv = &argv[i];
		command->redirs = NULL;
	}
	return (command);
}

// struct s_command	*parse_env_commands(t_vars *vars, char **argv)
// {
// 	int					i;
// 	char				*equal;
// 	struct s_command	*command;
// 	t_envp				*temp;

// 	i = 1;
// 	command = NULL;
// 	while (argv[i])
// 	{
// 		equal = ft_strchr(argv[i], '=');
// 		if (!equal)
// 			break;
// 		temp = create_envp_node(argv[i]);
// 				replace_envp_if_existing(vars, *envp)
// 		i++;
// 	}
// 	if(argv[i])
// 	{
// 		command = malloc(sizeof(struct s_command));
// 		command->argv = &argv[i];
// 		command->redirs = NULL;
// 	}
// 	return (command);
// }

int	env_childprocess(t_vars *vars, char **argv, int fd)
{
	struct s_command	*command;
	int					exit_code;

	command = parse_env_commands(vars, argv);
	if (!command)
	{
		write_env(fd, vars->envp_ll);
		exit_code = EXIT_SUCCESS;
	}
	else
	{
		exit_code = execute_command(vars, command, STDIN_FILENO, fd);
		free(command);
	}
	free_all(vars);
	close(fd);
	exit(exit_code);

}

int	run_env(t_vars *vars, char **argv, int fd)
{
	int					pid;
	int					status;

	pid = fork();
	if (pid < 0)
		env_error("fork", strerror(errno));
	if (pid == 0)
	{
		//signal handling?
		env_childprocess(vars, argv, fd);
	}
	else
	{
		signal_ignore_setup();
		waitpid(pid, &status, 0);
		signal_shell_setup();
	}
	return (0);
}
