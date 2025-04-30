#include "../../include/minishell.h"

int	operator_or(t_vars *vars, t_ast_node *current_node, int in_fd, int out_fd)
{
	int	left_status;

	left_status = execute_ast(vars,\
		current_node->u_data.s_operator.left,\
		in_fd,\
		STDOUT_FILENO);
	if (left_status != EXIT_SUCCESS)
		return (execute_ast(vars,\
			current_node->u_data.s_operator.right,\
			STDIN_FILENO,\
			out_fd));
	else
		 return (left_status);
}

int	operator_and(t_vars *vars, t_ast_node *current_node, int in_fd, int out_fd)
{
	int	left_status;

	left_status = execute_ast(vars,\
		current_node->u_data.s_operator.left,\
		in_fd,\
		STDOUT_FILENO);
	if (left_status == EXIT_SUCCESS)
		return (execute_ast(vars,\
			current_node->u_data.s_operator.right,\
			STDIN_FILENO,\
			out_fd));
	else
		 return (left_status);
}

int	pipe_left(t_vars *vars, t_ast_node *current_node, int in_fd, int out_fd, int pipe_fd[])
{
	int	left_status;

	signal_pipe_setup();
	close(pipe_fd[0]);
	if (out_fd != STDOUT_FILENO)
		close(out_fd);
	left_status = execute_ast(vars, current_node->u_data.s_operator.left, in_fd, pipe_fd[1]);
	close(pipe_fd[1]);
	if (in_fd != STDIN_FILENO)
		close(in_fd);
	free_all(vars);
	exit (left_status);
}

int	pipe_right(t_vars *vars, t_ast_node *current_node, int in_fd, int out_fd, int pipe_fd[])
{
	int	right_status;

	signal_pipe_setup();
	close(pipe_fd[1]);
	if (in_fd != STDIN_FILENO)
		close(in_fd);
	right_status = execute_ast(vars, current_node->u_data.s_operator.right, pipe_fd[0], out_fd);
	close(pipe_fd[0]);
	if (out_fd != STDOUT_FILENO)
		close(out_fd);
	free_all(vars);
	exit (right_status);
}

int	operator_pipe(t_vars *vars, t_ast_node *current_node, int in_fd, int out_fd)
{
	int	pipe_fd[2];
	int	pid_left;
	int	pid_right;
	int	left_status;
	int	right_status;

	if (pipe(pipe_fd) == -1)
		return (execution_error("pipe", strerror(errno), -1));
	pid_left = fork();
	if (pid_left == -1)
		return (execution_error("fork", strerror(errno), -1));
	if (pid_left == 0)
		pipe_left(vars, current_node, in_fd, out_fd, pipe_fd);
	pid_right = fork();
	if (pid_right == 0)
		pipe_right(vars, current_node, in_fd, out_fd, pipe_fd);
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	if (in_fd != STDIN_FILENO)
		close(in_fd);
	if (out_fd != STDOUT_FILENO)
		close(out_fd);
	waitpid(pid_left, &left_status, 0);
	waitpid(pid_right, &right_status, 0);
	if (WIFEXITED(right_status))
		return (WEXITSTATUS(right_status));
	if (WIFSIGNALED(right_status))
		return (WTERMSIG(right_status));
	return (-1);
}
