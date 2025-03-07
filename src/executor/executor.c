#include "../../include/minishell.h"
#include <string.h>

void	ast_dummy1(t_ast_node *ast)
{
	ast->type = NODE_COMMAND;
	ast->u_data.s_command.argv = malloc(5 * sizeof(char *));
	ast->u_data.s_command.argv[0] = "echo";
	ast->u_data.s_command.argv[1] = "";
	ast->u_data.s_command.argv[2] = "Hallo";
	ast->u_data.s_command.argv[3] = "Gallo";
	ast->u_data.s_command.argv[4] = NULL;
	return ;
}

void	free_dummy1(t_ast_node *ast)
{
	free(ast->u_data.s_command.argv);
}
void	ast_dummy2(t_ast_node *ast)
{
	ast->type = NODE_COMMAND;
	ast->u_data.s_command.argv = malloc(3 * sizeof(char *));
	ast->u_data.s_command.argv[0] = "cd";
	ast->u_data.s_command.argv[1] = "../bashtests";
	ast->u_data.s_command.argv[2] = NULL;
	return ;
}

void	ast_dummy3(t_ast_node *ast)
{
	char	*command1 = "ls";
	char	*command2 = "-l";
	char	*command3 = NULL;
	char	*command4 = "wc";
	char	*command5 = "-l";
	char	*command6 = NULL;

	ast->type = NODE_PIPE;
	ast->u_data.s_operator.left = malloc(sizeof(t_ast_node));
	ast->u_data.s_operator.right = malloc(sizeof(t_ast_node));

	ast->u_data.s_operator.left->type = NODE_COMMAND;
	ast->u_data.s_operator.left->u_data.s_command.argv = malloc(3 * sizeof(char*));
	ast->u_data.s_operator.left->u_data.s_command.argv[0] = command1;
	ast->u_data.s_operator.left->u_data.s_command.argv[1] = command2;
	ast->u_data.s_operator.left->u_data.s_command.argv[2] = command3;

	ast->u_data.s_operator.left->u_data.s_command.redirs = malloc(sizeof(t_redir));
	ast->u_data.s_operator.left->u_data.s_command.redirs->type = REDIR_INPUT;
	ast->u_data.s_operator.left->u_data.s_command.redirs->target = "infile";
	ast->u_data.s_operator.left->u_data.s_command.redirs->next = NULL;

	ast->u_data.s_operator.right->type = NODE_COMMAND;
	ast->u_data.s_operator.right->u_data.s_command.argv = malloc(3 * sizeof(char*));
	ast->u_data.s_operator.right->u_data.s_command.argv[0] = command4;
	ast->u_data.s_operator.right->u_data.s_command.argv[1] = command5;
	ast->u_data.s_operator.right->u_data.s_command.argv[2] = command6;

	ast->u_data.s_operator.right->u_data.s_command.redirs = malloc(sizeof(t_redir));
	ast->u_data.s_operator.right->u_data.s_command.redirs->type = REDIR_OUTPUT;
	ast->u_data.s_operator.right->u_data.s_command.redirs->target = "outfile";
	ast->u_data.s_operator.right->u_data.s_command.redirs->next = NULL;

	return ;
}

void	free_dummy3(t_ast_node *ast)
{
	free(ast->u_data.s_operator.left->u_data.s_command.redirs);
	free(ast->u_data.s_operator.right->u_data.s_command.redirs);
	free(ast->u_data.s_operator.left->u_data.s_command.argv);
	free(ast->u_data.s_operator.right->u_data.s_command.argv);
	free(ast->u_data.s_operator.left);
	free(ast->u_data.s_operator.right);
	return ;
}

int	execute_command(char **argv)
{
	if (ft_strcmp(argv[0], "echo") == 0)
		return (run_echo(1, argv));
	if (ft_strcmp(argv[0], "cd") == 0)
		return (run_cd(1, argv));
	return (0);
}

int	execute_ast(t_ast_node *node)
{
	if (node->type == NODE_COMMAND)
		return (execute_command(node->u_data.s_command.argv));
	else if (node->type == NODE_PIPE)
		return (1);
	else if (node->type == NODE_AND)
		return (1);
	else if (node->type == NODE_OR)
		return (1);
	else if (node->type == NODE_SUBSHELL)
		return (1);
	return (-1);
}

void	executor(t_vars *vars)
{
	t_ast_node	*ast;

	printf("executor output:\n");
	//create a dummy
	ast = malloc(sizeof(t_ast_node));
	ast_dummy1(ast);
	//execute dummy
	execute_ast(ast);
	// free dummy
	free_dummy1(ast);
	free(ast);

	(void)vars;

	return ;
}

/* void	executor(t_vars *vars)
{
	t_token *tmp;

	while (tmp)
	{
		if (vars->token->type == 3)
		{
			redirect_out()
		}
	{

	}
	if (vars->token->value && ft_strcmp(vars->token->value, "echo") == 0)
	{
		echo(vars->token->next->value);
	}
	return ;
} */
