#include "../../include/minishell.h"
#include <unistd.h>

int	operator_or(t_vars *vars, t_ast_node *current_node, int in_fd, int out_fd)
{
	int	left_status;

	left_status = execute_ast(vars,\
		current_node->u_data.s_operator.left,\
		STDIN_FILENO,\
		STDOUT_FILENO);
	if (left_status != EXIT_SUCCESS)
		return (execute_ast(vars,\
			current_node->u_data.s_operator.right,\
			STDIN_FILENO,\
			STDOUT_FILENO));
	else
		 return (left_status);
}

int	operator_and(t_vars *vars, t_ast_node *current_node, int in_fd, int out_fd)
{
	int	left_status;

	left_status = execute_ast(vars,\
		current_node->u_data.s_operator.left,\
		STDIN_FILENO,\
		STDOUT_FILENO);
	if (left_status == EXIT_SUCCESS)
		return (execute_ast(vars,\
			current_node->u_data.s_operator.right,\
			STDIN_FILENO,\
			STDOUT_FILENO));
	else
		 return (left_status);
}

int	operator_pipe(t_vars *vars, t_ast_node *current_node, int in_fd, int out_fd)
{
	int	pipe_fd[2];
	int	pid_left;
	int	pid_right;
	int	left_status;
	int	right_status;
	char	pathname[PATH_MAX];

	if (pipe(pipe_fd) == -1)
		return (execution_error("pipe", strerror(errno)));
	ft_printf("Pipe with file descriptors read: %i and write: %i opened.\n", pipe_fd[0], pipe_fd[1]);
	pid_left = fork();
	if (pid_left == -1)
		return (execution_error("fork", strerror(errno)));
	if (pid_left == 0)
	{
		//dup2(fd[1], STDOUT_FILENO);
		//close(fd[0]);
		//close(fd[1]);
		//test version without recurseively open execute_ast() - only if left and right are command nodes
		//search_executable(vars, current_node->u_data.s_operator.left->u_data.s_command.argv[0], pathname);
		//execve(pathname, current_node->u_data.s_operator.left->u_data.s_command.argv, vars->envp);
		execute_ast(vars, current_node->u_data.s_operator.left, in_fd, pipe_fd[1]);
		//what happens if exection fails?
		//close(fd[0]);
		//close(fd[1]);
	}
	else
	{
		pid_right = fork();
		if (pid_right == 0)
		{
			//dup2(fd[0], STDIN_FILENO);
			//close(fd[0]),
			//close(fd[1]);
			//test version without recurseively open execute_ast() - only if left and right are command nodes
			//search_executable(vars, current_node->u_data.s_operator.right->u_data.s_command.argv[0], pathname);
			//execve(pathname, current_node->u_data.s_operator.right->u_data.s_command.argv, vars->envp);
			execute_ast(vars, current_node->u_data.s_operator.right, pipe_fd[0], out_fd);
		}
		else
		{
			close(pipe_fd[0]);
			close(pipe_fd[1]);
			waitpid(pid_left, &left_status, 0);
			waitpid(pid_right, &right_status, 0);
		}
	}
	return (1);
}
