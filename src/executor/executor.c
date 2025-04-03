/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vboxuser <vboxuser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 10:51:49 by vboxuser          #+#    #+#             */
/*   Updated: 2025/04/03 16:24:37 by vboxuser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	execute_command(t_vars *vars, struct s_command *curr_command_node)
{
	if (ft_strcmp(curr_command_node->argv[0], "echo") == 0)
		return (run_echo(1, curr_command_node->argv));
	else if (ft_strcmp(curr_command_node->argv[0], "pwd") == 0)
		return (run_pwd(1, curr_command_node->argv));
	else if (ft_strcmp(curr_command_node->argv[0], "cd") == 0)
		return (run_cd(vars));
	else if (ft_strcmp(curr_command_node->argv[0], "export") == 0)
		return (1);
	else if (ft_strcmp(curr_command_node->argv[0], "unset") == 0)
		return (1);
	else if (ft_strcmp(curr_command_node->argv[0], "env") == 0)
		return (1);
	else if (ft_strcmp(curr_command_node->argv[0], "exit") == 0)
		return (1);
	else
		return (run_executable(vars, curr_command_node));
	return (-1);
}

int	execute_ast(t_vars *vars, t_ast_node *current_node)
{
	if (current_node == NULL)
		return (0);
	if (current_node->type == AST_COMMAND)
		return (execute_command(vars, &current_node->u_data.s_command));
	else if (current_node->type == AST_PIPE)
		return (operator_pipe(vars, current_node));
	else if (current_node->type == AST_AND)
		return (operator_and(vars, current_node));
	else if (current_node->type == AST_OR)
		return (operator_and(vars, current_node));
	else if (current_node->type == AST_SUBSHELL)
		return (1);
	return (-1);
}

void	executor(t_vars *vars)
{
	//t_ast_node	*ast;

	printf("\n###################### MINISHELL OUTPUT ######################\n");
	//create a dummy
	//ast = malloc(sizeof(t_ast_node));
	//ast_dummy2(ast);
	//execute dummy
	execute_ast(vars, vars->ast);
	// free dummy
	//free_dummy1(ast);
	//free(ast);

	//(void)vars;

	return ;
}
