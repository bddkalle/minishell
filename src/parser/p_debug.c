/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_debug.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdahne <cdahne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 16:18:32 by fschnorr          #+#    #+#             */
/*   Updated: 2025/05/05 14:29:22 by cdahne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*void	debug_lexer(t_vars *vars)
{
	t_token	*tmp;
	int		i;

	printf("\n###################### DEBUG LEXER ######################\n");
	i = 0;
	tmp = vars->token;
	if (!tmp)
		printf("\nvars->token = %p\n", vars->token);
	while (tmp)
	{
		printf("\n>>Token %d<<\n", i++);
		printf("\tvalue: %s\n", tmp->value);
		if (tmp->type == TOKEN_WORD)
			printf("\ttype: TOKEN_WORD\n");
		else if (tmp->type == TOKEN_PIPE)
			printf("\ttype: TOKEN_PIPE\n");
		else if (tmp->type == TOKEN_REDIRECT_IN)
			printf("\ttype: TOKEN_REDIRECT_IN\n");
		else if (tmp->type == TOKEN_REDIRECT_OUT)
			printf("\ttype: TOKEN_REDIRECT_OUT\n");
		else if (tmp->type == TOKEN_REDIRECT_APPEND)
			printf("\ttype: TOKEN_REDIRECT_APPEND\n");
		else if (tmp->type == TOKEN_HEREDOC)
			printf("\ttype: TOKEN_HEREDOC\n");
		else if (tmp->type == TOKEN_AND)
			printf("\ttype: TOKEN_AND\n");
		else if (tmp->type == TOKEN_OR)
			printf("\ttype: TOKEN_OR\n");
		else if (tmp->type == TOKEN_QUOTE)
			printf("\ttype: TOKEN_QUOTE\n");
		else if (tmp->type == TOKEN_PARENT_LEFT)
			printf("\ttype: TOKEN_PARENT_LEFT\n");
		else if (tmp->type == TOKEN_PARENT_RIGHT)
			printf("\ttype: TOKEN_PARENT_RIGHT\n");
		else if (tmp->type == TOKEN_VAR)
			printf("\ttype: TOKEN_VAR\n");
		else if (tmp->type == TOKEN_IO_NUMBER)
			printf("\ttype: TOKEN_IO_NUMBER\n");
		else if (tmp->type == TOKEN_EXIT_STATUS)
			printf("\ttype: TOKEN_EXIT_STATUS\n");
		else if (tmp->type == TOKEN)
			printf("\ttype: TOKEN\n");
		tmp = tmp->next;
	}
}

int	print_op_node(t_ast_node *curr_node, int nodenum)
{
	t_ast_node	*tmp_node;
	int			opnodes;

	printf("\n>>AST NODE %d = OPERATOR NODE<<\n", nodenum++);
	if (curr_node->type == AST_PIPE)
			printf("\ttype = AST_PIPE\n");
	if (curr_node->type == AST_AND)
			printf("\ttype = AST_AND\n");
	if (curr_node->type == AST_OR)
			printf("\ttype = AST_OR\n");
	printf("\tleft = AST NODE %d\n", nodenum);
	if (curr_node->u_data.s_operator.left->type == AST_COMMAND)
		printf("\tright = AST NODE %d\n", nodenum + 1);
	else
	{
		tmp_node = curr_node;
		opnodes = 0;
		while (tmp_node->u_data.s_operator.left->type != AST_COMMAND)
		{
			if (tmp_node->u_data.s_operator.left->type == AST_SUBSHELL)
				opnodes++;
			else
				opnodes += 2;
			tmp_node = tmp_node->u_data.s_operator.left;
		}
		printf("\tright = AST NODE %d\n", nodenum + 1 + opnodes);
	}
	nodenum = print_ast_node(curr_node->u_data.s_operator.left, nodenum);
	nodenum = print_ast_node(curr_node->u_data.s_operator.right, nodenum);
	return (nodenum);
}

int	print_cmd_node(t_ast_node *curr_node, int nodenum)
{
	printf("\n>>AST NODE %d = COMMAND NODE<<\n", nodenum++);
	for (int i = 0; curr_node && curr_node->u_data.s_command.argv[i]; i++)
	{
		printf("\targv[%d] = %s\n", i, curr_node->u_data.s_command.argv[i]);
	}
	if (curr_node->u_data.s_command.redirs)
		{
			int j = 0;
			for (t_redir *tmp = curr_node->u_data.s_command.redirs; \
			tmp; tmp = tmp->next)
			{
				if (tmp->type == REDIR_INPUT)
					printf("\n\tredir_node%d.type =\tREDIR_INPUT\n", j);
				else if (tmp->type == REDIR_OUTPUT)
					printf("\n\tredir_node%d.type =\tREDIR_OUTPUT\n", j);
				else if (tmp->type == REDIR_APPEND)
					printf("\n\tredir_node%d.type =\tREDIR_APPEND\n", j);
				else if (tmp->type == REDIR_HEREDOC)
					printf("\n\tredir_node%d.type =\tREDIR_HEREDOC\n", j);
				if (tmp->fd != -1)
					printf("\tredir_node%d.fd =\t%d\n", j, tmp->fd);
				printf("\tredir_node%d.target =\t%s\n", j++, tmp->target);
			}
		}
	return (nodenum);
}

int	print_subshell_node(t_ast_node *curr_node, int nodenum)
{
	printf("\n>>AST NODE %d = SUBSHELL NODE<<\n", nodenum++);
	printf("\tchild = AST NODE %d\n", nodenum);
	nodenum = print_ast_node(curr_node->u_data.s_subshell.child, nodenum);
	return (nodenum);
}

int	print_ast_node(t_ast_node *curr_node, int nodenum)
{
	if (! curr_node)
		return (nodenum);
	if (curr_node->type == AST_PIPE || \
			curr_node->type == AST_AND || \
			curr_node->type == AST_OR)
		nodenum = print_op_node(curr_node, nodenum);
	else if (curr_node->type == AST_COMMAND)
		nodenum = print_cmd_node(curr_node, nodenum);
	else if (curr_node->type == AST_SUBSHELL)
		nodenum = print_subshell_node(curr_node, nodenum);
	return (nodenum);
}

void	debug_parser(t_vars *vars)
{
	t_ast_node	*tmp_ast;
	int	nodenum = 0;

	tmp_ast = vars->ast;
	printf("\n###################### DEBUG PARSER ######################\n");
	if (!vars->ast)
		printf("\nvars->ast = %p\n", vars->ast);
	print_ast_node(tmp_ast, nodenum);
}*/
