#include "../../include/minishell.h"

int	search_executable(t_vars *vars, char *command, char *pathname)
{
	int		found;
	struct stat	sb;

	if (ft_strchr(command, '/') != NULL)
		ft_strlcpy(pathname, command, ft_strlen(command) + 1);
	else
	{
		found = search_env_path(vars, command, pathname);
		if (found != 0)
			return (found);
	}
	if (stat(pathname, &sb) == 0 && S_ISDIR(sb.st_mode))
		return (-3);
	if (access(pathname, F_OK) != 0 && (*pathname == '.' || *pathname == '/'))
		return (-4);
	if (access(pathname, F_OK) != 0)
		return (-5);
	if (access(pathname, X_OK) != 0)
		return (-6);
	return (0);
}

void	run_executable_child(t_vars *vars, char *pathname, struct s_command *curr_command_node, int in_fd, int out_fd)
{
	if (out_fd != STDOUT_FILENO)
	{
		dup2(out_fd, STDOUT_FILENO);
		close(out_fd);
	}
	if (in_fd != STDIN_FILENO)
	{
		dup2(in_fd, STDIN_FILENO);
		close(in_fd);
	}
	if (global_received_signal == 0)
	{
		signal_executable_setup();
		execve(pathname, curr_command_node->argv, envp_to_array(vars->envp_ll));
		execution_error(curr_command_node->argv[0], strerror(errno), 1);
	}
	else if (global_received_signal == SIGINT)
		global_received_signal = 0;
	free_all(vars);
	exit (EXIT_FAILURE);
}

int	run_executable_parent(pid_t pid)
{
	int	status;

	signal_ignore_setup();
	waitpid(pid, &status, 0);
	signal_shell_setup();
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == SIGINT)
			write(1, "\n", 1);
		else if (WTERMSIG(status) == SIGQUIT)
			write(1, "Quit (core dumped)\n", 19);
		return (WIFSIGNALED(status));
	}
	return (-1);
}

int	run_executable(t_vars *vars, struct s_command *curr_command_node, int in_fd, int out_fd)
{
	char	pathname[PATH_MAX];
	pid_t	pid;
	int		found;

	found = search_executable(vars, curr_command_node->argv[0], pathname);
	if (found == -1)
		return (execution_error(curr_command_node->argv[0], "command not found", 127));
	else if (found == -2)
		fatal_error(vars, "out of memory");
	else if (found == -3)
		return (execution_error(curr_command_node->argv[0], "Is a directory", 126));
	else if (found == -4)
		return (execution_error(curr_command_node->argv[0], "No such file or directory", 127));
	else if (found == -5)
		return (execution_error(curr_command_node->argv[0], "command not found", 127));
	else if (found == -6)
		return (execution_error(curr_command_node->argv[0], "Permission denied", 126));
	pid = fork();
	if (pid == -1)
		return (execution_error(curr_command_node->argv[0], strerror(errno), errno));
	if (pid == 0)
		run_executable_child(vars, pathname, curr_command_node, in_fd, out_fd);
	else
		return (run_executable_parent(pid));
	return (-1);
}
