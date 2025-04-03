#include "../../include/minishell.h"

int	operator_or(t_vars *vars, t_ast_node *current_node)
{
	int	left_status;

	left_status = execute_ast(vars, current_node->u_data.s_operator.left);
	if (left_status != EXIT_SUCCESS)
		return (execute_ast(vars, current_node->u_data.s_operator.right));
	else
		 return (left_status);
}

int	operator_and(t_vars *vars, t_ast_node *current_node)
{
	int	left_status;

	left_status = execute_ast(vars, current_node->u_data.s_operator.left);
	if (left_status == EXIT_SUCCESS)
		return (execute_ast(vars, current_node->u_data.s_operator.right));
	else
		 return (left_status);
}

int	operator_pipe(t_vars *vars, t_ast_node *current_node)
{
	int	fd[2];
	int	pid_left;
	int	pid_right;
	int	left_status;
	int	right_status;

	if (pipe(fd) == -1)
		return (execution_error("pipe", strerror(errno)));
	pid_left = fork();
	if (pid_left == -1)
		return (execution_error("fork", strerror(errno)));
	if (pid_left == 0)
	{
		dup2(fd[1], STDOUT_FILENO);
		close(fd[0]);
		close(fd[1]);
		//execute_ast(vars, current_node->u_data.s_operator.left);
	}
	pid_right = fork();
	if (pid_right == 0)
	{
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]),
		close(fd[1]);
		execute_ast(vars, current_node->u_data.s_operator.right);
	}
	close(fd[0]);
	close(fd[1]);
	waitpid(pid_left, &left_status, 0);
	waitpid(pid_right, &right_status, 0);
	return (1);
}
