/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fschnorr <fschnorr@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 16:21:13 by fschnorr          #+#    #+#             */
/*   Updated: 2025/03/13 17:12:23 by fschnorr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_ast_node	*parse_expression(t_vars *vars)
{
	t_ast_node	*left;
	
	left = parse_command(vars);
	return (left);
}

t_ast_node	*parse_command(t_vars *vars)
{
	//t_ast_node	*node;
	t_token		*tmp_token;
	int			word_count;
	int			i;

	vars->parser->node = _malloc(sizeof(t_ast_node), vars);
	vars->parser->node->type = AST_COMMAND;
	tmp_token = vars->parser->curr_tok;
	word_count = 0;
	while (tmp_token && tmp_token->type == TOKEN_WORD)
	{
		word_count++;
		tmp_token = tmp_token->next;
	}
	vars->parser->node->u_data.s_command.argv = _malloc((word_count + 1) * sizeof(char *), vars);
	i = 0;
	while (vars->parser->curr_tok && vars->parser->curr_tok->type == TOKEN_WORD)
	{
	//	vars->parser->node->u_data.s_command.argv[i] = NULL;
		vars->parser->node->u_data.s_command.argv[i] = ft_strdup(vars->parser->curr_tok->value);
		if (!vars->parser->node->u_data.s_command.argv[i++])
			error_exit(vars, "strdup failed to fill nodes argv", EXIT_FAILURE);
		advance_token(vars);
	}
	vars->parser->node->u_data.s_command.argv[i] = NULL;
	vars->parser->node->u_data.s_command.redirs = NULL;
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
	//vars->parser->curr_tok = vars->token;
	vars->ast = parse_expression(vars);
	debug_parser(vars);
/* 	char	argv[20] = {};
	int		i;

	i = 0;
	argv[0] = NULL;
	while (vars->parser->curr_tok && vars->parser->curr_tok->type == TOKEN_WORD)
	{
		*argv[i++] = vars->parser->curr_tok->value;
		vars->parser->curr_tok = vars->parser->curr_tok->next;
	}
	argv[i] = NULL;
	// *vars->ast = parse_factor(vars);
	//parse_expression(vars);
	i = 0;
	while (argv[i])
		printf("%s\n", *argv[i++]);
 */
}
