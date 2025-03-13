/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vboxuser <vboxuser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 10:51:49 by vboxuser          #+#    #+#             */
/*   Updated: 2025/03/13 17:33:24 by vboxuser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ast_dummy1(t_ast_node *ast)
{
	ast->type = AST_COMMAND;
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
	ast->type = AST_COMMAND;
	ast->u_data.s_command.argv = malloc(3 * sizeof(char *));
	ast->u_data.s_command.argv[0] = "cd";
	ast->u_data.s_command.argv[1] = "/root";
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

	ast->type = AST_PIPE;
	ast->u_data.s_operator.left = malloc(sizeof(t_ast_node));
	ast->u_data.s_operator.right = malloc(sizeof(t_ast_node));

	ast->u_data.s_operator.left->type = AST_COMMAND;
	ast->u_data.s_operator.left->u_data.s_command.argv = malloc(3 * sizeof(char*));
	ast->u_data.s_operator.left->u_data.s_command.argv[0] = command1;
	ast->u_data.s_operator.left->u_data.s_command.argv[1] = command2;
	ast->u_data.s_operator.left->u_data.s_command.argv[2] = command3;

	ast->u_data.s_operator.left->u_data.s_command.redirs = malloc(sizeof(t_redir));
	ast->u_data.s_operator.left->u_data.s_command.redirs->type = REDIR_INPUT;
	ast->u_data.s_operator.left->u_data.s_command.redirs->target = "infile";
	ast->u_data.s_operator.left->u_data.s_command.redirs->next = NULL;

	ast->u_data.s_operator.right->type = AST_COMMAND;
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

int	execute_command(t_vars *vars)
{
	if (ft_strcmp(vars->ast->u_data.s_command.argv[0], "echo") == 0)
		return (run_echo(1, vars->ast->u_data.s_command.argv));
	if (ft_strcmp(vars->ast->u_data.s_command.argv[0], "pwd") == 0)
		return (run_pwd(1, vars->ast->u_data.s_command.argv));
	if (ft_strcmp(vars->ast->u_data.s_command.argv[0], "cd") == 0)
		return (run_cd(vars));
	return (-1);
}

int	execute_ast(t_vars *vars)
{
	//int	left_status;
	//int	right_status;
	if (vars->ast->type == AST_COMMAND)
		return (execute_command(vars));
	else if (vars->ast->type == AST_PIPE)
		return (1);
	else if (vars->ast->type == AST_AND)
		return (1);
	else if (vars->ast->type == AST_OR)
		return (1);
	else if (vars->ast->type == AST_SUBSHELL)
		return (1);
	return (-1);
}

void	executor(t_vars *vars)
{
	//t_ast_node	*ast;

	printf("\n>>Minishell Output<<\n");
	//create a dummy
	//ast = malloc(sizeof(t_ast_node));
	//ast_dummy2(ast);
	//execute dummy
	execute_ast(vars);
	// free dummy
	//free_dummy1(ast);
	//free(ast);

	//(void)vars;

	return ;
}
