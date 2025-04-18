/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_free.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fschnorr <fschnorr@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 15:13:48 by fschnorr          #+#    #+#             */
/*   Updated: 2025/04/01 13:14:41 by fschnorr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	free_op_node(t_ast_node **curr_node)
{
	free_ast_node(&(*curr_node)->u_data.s_operator.left);
	free_ast_node(&(*curr_node)->u_data.s_operator.right);
	free_null((void **)curr_node);
}

void	free_cmd_node(t_ast_node **curr_node)
{
	t_size	i;
	t_redir	*tmp;

	if (*curr_node && (*curr_node)->type == AST_COMMAND)
	{
		i = 0;
		while ((*curr_node)->u_data.s_command.argv[i])
			free_null((void **)&(*curr_node)->u_data.s_command.argv[i++]);
		free_null((void **)&(*curr_node)->u_data.s_command.argv);
		while ((*curr_node)->u_data.s_command.redirs)
		{
			tmp = (*curr_node)->u_data.s_command.redirs->next;
			free_null((void **)&(*curr_node)->u_data.s_command.redirs);
			(*curr_node)->u_data.s_command.redirs = tmp;
		}
		free_null((void **)curr_node);
	}

}

void	free_ast_node(t_ast_node **curr_node)
{
	if (curr_node && ((*curr_node)->type == AST_PIPE || \
		(*curr_node)->type == AST_AND || \
		(*curr_node)->type == AST_OR))
		free_op_node(curr_node);
	else if (curr_node && (*curr_node)->type == AST_COMMAND)
		free_cmd_node(curr_node);
}

void	free_parser(t_vars *vars)
{
	t_size	i;

	if (vars->ast)
	{
		free_ast_node(&vars->ast);
		vars->parser->node = NULL;
	}
	else if (vars->parser)
	{
		if (vars->parser->node && vars->parser->node->type == AST_COMMAND)
		{
			i = 0;
			while (vars->parser->node->u_data.s_command.argv && \
			vars->parser->node->u_data.s_command.argv[i])
				free_null((void **)&vars->parser->node->\
							u_data.s_command.argv[i++]);
			free_null((void **)&vars->parser->node->u_data.s_command.argv);
			free_null((void **)&vars->parser->node);
		}
	}
	free_null_token(vars);
	free_null((void **)&vars->line);
	free_null((void **)&vars->lexer);
	free_null((void **)&vars->parser);
}

void	free_null_token(t_vars *vars)
{
	t_token	*tmp;

	if (vars->lexer)
		free_null((void **)&vars->lexer->curr_token);

	while (vars->token)
	{
		free_null((void **)&vars->token->value);
		tmp = vars->token->next;
		free_null((void **)&vars->token);
		vars->token = tmp;
	}
}

void	close_parser(t_vars *vars)
{
	_close(vars->prompt->fd_hostname);
}
