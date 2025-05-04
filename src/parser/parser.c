/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fschnorr <fschnorr@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 16:21:13 by fschnorr          #+#    #+#             */
/*   Updated: 2025/05/05 00:09:11 by fschnorr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	check_syntax(t_vars *vars)
{
	if (!vars->token)
		return ;

	if (is_invalid_leading_op(vars->token->type))
	{
		ft_putstr_fd("minishell: syntax error near unexpected token »", 2);
		ft_putstr_fd(vars->token->value, 2);
		ft_putstr_fd("«\n", 2);
		vars->exit_status = 2;
		free_null_token(vars);
	}
	check_redir_syntax(vars);
}

t_ast_node	*parse_or_and(t_vars *vars)
{
	t_ast_node	*left;
	t_ast_node	*right;
	t_ast_node	*op_node;
	t_node_type	op_type;

	left = parse_factor(vars);
	while (vars->parser->curr_tok && \
			(vars->parser->curr_tok->type == TOKEN_PIPE || \
			vars->parser->curr_tok->type == TOKEN_AND || \
			vars->parser->curr_tok->type == TOKEN_OR))
	{
		op_type = set_op_type(vars->parser->curr_tok->type);
		advance_token(vars);
		if (!vars->parser->curr_tok || is_operator(vars->parser->curr_tok->type))
		{
			ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
			if (vars->parser->curr_tok)
					ft_putstr_fd(vars->parser->curr_tok->value, 2);
			else
				ft_putstr_fd("newline", 2);
            ft_putstr_fd("'\n", 2);
            vars->exit_status = 2;
            return NULL;
        }
		right = parse_factor(vars);
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
	init_parse_command(vars);
	vars->parser->next_redir_node = \
							&vars->parser->node->u_data.s_command.redirs;
	while (vars->parser->curr_tok)
	{
		if (is_redir_op(vars->parser->curr_tok->type))
		{
			if (!vars->parser->curr_tok->next \
				|| vars->parser->curr_tok->next->type != TOKEN_WORD)
			{
				ft_putstr_fd("minishell: syntax error near unexpected token `", \
				2);
				if (vars->parser->curr_tok->next)
					ft_putstr_fd(vars->parser->curr_tok->next->value, 2);
				else
					ft_putstr_fd("newline", 2);
				ft_putstr_fd("'\n", 2);
				vars->exit_status = 2;
				return (NULL);
			}
			*vars->parser->next_redir_node = handle_redirs(vars);
			vars->parser->next_redir_node = \
							&(*vars->parser->next_redir_node)->next;
			continue ;
		}
		else if (vars->parser->curr_tok->type == TOKEN_WORD)
			fill_cmd_argv(vars);
		else
			break ;
	}
	return (vars->parser->node);
}

t_ast_node	*parse_factor(t_vars *vars)
{
	t_ast_node	*child;
	t_ast_node	*node;

	if (!vars->parser->curr_tok)
		return (NULL);
	if (current_token_is(")", vars))
		printf("SYNTAX ERROR IN PARSER");		//syntax handling???
	if (current_token_is("(", vars))
	{
		advance_token(vars);
		child = parse_expression(vars);
		if (!vars->parser->curr_tok || !current_token_is(")", vars))
		{
			ft_putstr_fd("minishell: syntax error: missing `)`\n", 2);
			vars->exit_status = 2;
			return (NULL);
		}
		advance_token(vars);
		node = _malloc(sizeof(t_ast_node), vars);
		node->type = AST_SUBSHELL;
		node->u_data.s_subshell.child = child;
		return (node);
	}
	return (parse_command(vars));
}

void	parser(t_vars *vars)
{
	//check_syntax(vars);
	if (!vars->token)
		return ;
	init_parser(vars);
	reclassification(vars);
	if (!vars->parser)
		return ;
	remove_quotes(vars);
	vars->ast = parse_expression(vars);
	if (!vars->ast)
	{
		free_null_readline(vars);
		return ;
	}
	//debug_parser(vars);
}
