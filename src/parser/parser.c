/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fschnorr <fschnorr@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 16:21:13 by fschnorr          #+#    #+#             */
/*   Updated: 2025/03/11 16:54:56 by fschnorr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/* void	parse_expression(t_vars *vars)
{
	if (vars->parser->curr_tok->type == TOKEN_PARENT_LEFT)		//handle paranthesis
	{
		vars->parser->curr_tok = vars->parser->curr_tok->next;
	}
	else
		

} */

/* t_ast_node	*parse_command(t_vars *vars)
{
	t_token	*tmp_token;
	int		i;

	tmp_token = vars->parser->curr_tok;
	i = 0;
	while (tmp_token->type == TOKEN_WORD)
	{
		i++;
		tmp_token = tmp_token->next;
	}
	argv[i] = NULL; 
}

t_ast_node	*parse_factor(t_vars *vars)
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
} */

void	parser(t_vars *vars)
{
	vars->parser->curr_tok = vars->token;

	char	argv[20] = {};
	int		i;

	i = 0;
	argv[0] = NULL;
	while (vars->parser->curr_tok && vars->parser->curr_tok->type == TOKEN_WORD)
	{
		*argv[i++] = vars->parser->curr_tok->value;
		vars->parser->curr_tok = vars->parser->curr_tok->next;
	}
	argv[i] = NULL;
	//*vars->ast = parse_factor(vars);
	//parse_expression(vars);
	i = 0;
	while (argv[i])
		printf("%s\n", *argv[i++]);
}
