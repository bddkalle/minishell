/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operators.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vboxuser <vboxuser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 15:08:06 by cdahne            #+#    #+#             */
/*   Updated: 2025/05/04 20:57:32 by vboxuser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	pipe_left(t_vars *vars, t_ast_node *curr_node, int in_fd, int pipe_fd_w)
{
	int	left_status;

	signal_pipe_setup();
	left_status = execute_ast(vars, \
		curr_node->u_data.s_operator.left, \
		in_fd, pipe_fd_w);
	close(pipe_fd_w);
	if (in_fd != STDIN_FILENO)
		close(in_fd);
	free_all(vars);
	exit (left_status);
}

int	pipe_right(t_vars *vars, t_ast_node *curr_node, int pipe_fd_r, int out_fd)
{
	int	right_status;

	signal_pipe_setup();
	right_status = execute_ast(vars, \
		curr_node->u_data.s_operator.right, \
		pipe_fd_r, out_fd);
	close(pipe_fd_r);
	if (out_fd != STDOUT_FILENO)
		close(out_fd);
	free_all(vars);
	exit (right_status);
}

int	pipe_parent(int pid_left, int pid_right)
{
	int	left_status;
	int	right_status;

	signal_ignore_setup();
	waitpid(pid_left, &left_status, 0);
	waitpid(pid_right, &right_status, 0);
	signal_shell_setup();
	if (WIFEXITED(right_status))
		return (WEXITSTATUS(right_status));
	if (WIFSIGNALED(right_status))
		return (WTERMSIG(right_status));
	return (-1);
}

int	operator_pipe(t_vars *vars, t_ast_node *current_node, int in_fd, int out_fd)
{
	int	pipe_fd[2];
	int	pid_left;
	int	pid_right;

	if (pipe(pipe_fd) == -1)
		return (execution_error("pipe", strerror(errno), -1));
	pid_left = fork();
	if (pid_left == -1)
		return (execution_error("fork", strerror(errno), -1));
	if (pid_left == 0)
	{
		close_fds(out_fd, pipe_fd[0]);
		pipe_left(vars, current_node, in_fd, pipe_fd[1]);
	}
	pid_right = fork();
	if (pid_right == 0)
	{
		close_fds(pipe_fd[1], in_fd);
		pipe_right(vars, current_node, pipe_fd[0], out_fd);
	}
	close_fds(pipe_fd[0], pipe_fd[1]);
	close_fds(in_fd, out_fd);
	return (pipe_parent(pid_left, pid_right));
}
