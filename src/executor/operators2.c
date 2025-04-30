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

int	operator_subshell(t_vars *vars, t_ast_node *current_node, int in_fd, int out_fd)
{
	return (execute_ast(vars, current_node->u_data.s_subshell.child, in_fd, out_fd));
}
