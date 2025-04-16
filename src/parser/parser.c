/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fschnorr <fschnorr@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 16:21:13 by fschnorr          #+#    #+#             */
/*   Updated: 2025/04/16 14:54:39 by fschnorr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_ast_node	*parse_expression(t_vars *vars)
{
	t_ast_node	*left;
	t_ast_node	*right;
	t_ast_node	*op_node;
	t_node_type	op_type;

	left = parse_command(vars);
	while (vars->parser->curr_tok && \
			(vars->parser->curr_tok->type == TOKEN_PIPE || \
			vars->parser->curr_tok->type == TOKEN_AND || \
			vars->parser->curr_tok->type == TOKEN_OR))
	{
		if (vars->parser->curr_tok->type == TOKEN_PIPE)
			op_type = AST_PIPE;
		else if (vars->parser->curr_tok->type == TOKEN_AND)
			op_type = AST_AND;
		else if (vars->parser->curr_tok->type == TOKEN_OR)
			op_type = AST_OR;
		advance_token(vars);
		right = parse_command(vars);
		op_node = _malloc(sizeof(t_ast_node), vars);
		op_node->type = op_type;
		op_node->u_data.s_operator.left = left;
		op_node->u_data.s_operator.right = right;
		left = op_node;
	}
	return (left);
}

t_ast_node	*parse_command(t_vars *vars)
{
	t_token		*tmp_token;

	if (!vars->parser->curr_tok)
		return (NULL);
	init_parse_command(vars);
	vars->parser->next_redir_node = \
							&vars->parser->node->u_data.s_command.redirs;
	while (vars->parser->curr_tok)
	{
		tmp_token = vars->parser->curr_tok;
		if (tmp_token && (tmp_token->type == TOKEN_REDIRECT_IN || \
                        	tmp_token->type == TOKEN_REDIRECT_OUT || \
                        	tmp_token->type == TOKEN_REDIRECT_APPEND || \
                            tmp_token->type == TOKEN_HEREDOC))
		{
			*vars->parser->next_redir_node = handle_redirs(vars);
			vars->parser->next_redir_node = \
							&(*vars->parser->next_redir_node)->next;
			continue ;
		}
		else if (tmp_token && (tmp_token->type == TOKEN_WORD))
			fill_cmd_argv(vars);
		else
			break ;
	}
	return (vars->parser->node);
}

/* t_ast_node	*parse_factor(t_vars *vars)
{
	t_ast_node	*node;
	
	 if (current_token_type_is("TOKEN_PARENT_LEFT", vars))
	{
		vars->parser->tok_pos++; // advance_token = *next
		node = parse_expression(vars);
		if (!current_token_is(")", vars)){
			//Handle syntax error: missing closing paranthesis
		}
		vars->parser->tok_pos++;// advance_token = *next
		return (node);
	} 
	return (parse_command(vars));
}
 */
void	parser(t_vars *vars)
{
	init_parser(vars);
	reclassification(vars);
	remove_quotes(vars);
	vars->ast = parse_expression(vars);
	//debug_parser(vars);
}
