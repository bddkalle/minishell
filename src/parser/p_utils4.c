/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_utils4.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fschnorr <fschnorr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 14:55:34 by fschnorr          #+#    #+#             */
/*   Updated: 2025/04/29 14:00:42 by fschnorr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	handle_operator(t_vars *vars)
{
	if (vars->lexer->token_pos > 0)
	{
		create_token(vars);
		vars->lexer->next_node = &(*vars->lexer->next_node)->next;
		vars->lexer->token_pos = 0;
		vars->lexer->curr_token[0] = '\0';
	}
	vars->lexer->curr_token[vars->lexer->token_pos++] = vars->lexer->c;
	vars->lexer->line_pos++;
}

void	handle_whitespace(t_vars *vars)
{
	if (vars->lexer->token_pos > 0)
	{
		create_token(vars);
		vars->lexer->next_node = &(*vars->lexer->next_node)->next;
		vars->lexer->token_pos = 0;
		vars->lexer->curr_token[0] = '\0';
	}
	vars->lexer->line_pos++;
}

void	handle_quotes(t_vars *vars)
{
	if (char_is("'", vars->lexer->c))
		vars->lexer->state = IN_SINGLE_QUOTE;
	if (char_is("\"", vars->lexer->c))
		vars->lexer->state = IN_DOUBLE_QUOTE;
	handle_quoted_input(vars);
}

void	delimit_operator(t_vars *vars)
{
	create_token(vars);
	vars->lexer->next_node = &(*vars->lexer->next_node)->next;
	vars->lexer->token_pos = 0;
	vars->lexer->curr_token[0] = '\0';
}

void	handle_eoi(t_vars *vars)
{
	if (vars->lexer->token_pos > 0)
		create_token(vars);
}
