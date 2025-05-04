/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executables.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vboxuser <vboxuser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 15:19:41 by cdahne            #+#    #+#             */
/*   Updated: 2025/05/04 10:45:32 by vboxuser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	search_executable(t_vars *vars, char *command)
{
	int			found;
	struct stat	sb;

	found = 0;
	if (!*command)
		return (execution_error(command, "command not found", 127));
	if (ft_strchr(command, '/') != NULL)
		ft_strlcpy(vars->pathname, command, ft_strlen(command) + 1);
	else
		found = search_env_path(vars, command);
	if (found == -1)
		found = execution_error(command, "command not found", 127);
	else if (stat(vars->pathname, &sb) == 0 && S_ISDIR(sb.st_mode))
		found = execution_error(command, "Is a directory", 126);
	else if (access(vars->pathname, F_OK) != 0 && \
		(vars->pathname[0] == '.' || vars->pathname[0] == '/'))
		found = execution_error(command, "No such file or directory", 127);
	else if (access(vars->pathname, F_OK) != 0)
		found = execution_error(command, "command not found", 127);
	else if (access(vars->pathname, X_OK) != 0)
		found = execution_error(command, "Permission denied", 126);
	return (found);
}

void	run_executable_child(t_vars *vars, struct s_command *curr_command_node, \
			int in_fd, int out_fd)
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
	if (g_received_signal == 0)
	{
		signal_executable_setup();
		execve(vars->pathname, curr_command_node->argv, \
			envp_to_array(vars, 0));
		execution_error(curr_command_node->argv[0], strerror(errno), 1);
	}
	else if (g_received_signal == SIGINT)
		g_received_signal = 0;
	free_all(vars);
	close_fds(in_fd, out_fd);
	exit (EXIT_FAILURE);
}

int	run_executable_parent(t_vars *vars, pid_t pid)
{
	int	status;

	signal_ignore_setup();
	waitpid(pid, &status, 0);
	signal_shell_setup();
	ft_bzero(vars->pathname, PATH_MAX);
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

int	run_executable(t_vars *vars, struct s_command *curr_command_node, \
	int in_fd, int out_fd)
{
	pid_t	pid;
	int		found;

	found = search_executable(vars, curr_command_node->argv[0]);
	if (found != 0)
		return (found);
	pid = fork();
	if (pid == -1)
		return (execution_error(curr_command_node->argv[0], \
		strerror(errno), errno));
	if (pid == 0)
		run_executable_child(vars, curr_command_node, in_fd, out_fd);
	else
		return (run_executable_parent(vars, pid));
	return (-1);
}
