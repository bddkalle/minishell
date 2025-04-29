/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_utils5.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fschnorr <fschnorr@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 14:55:34 by fschnorr          #+#    #+#             */
/*   Updated: 2025/04/29 23:14:25 by fschnorr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	fill_token(t_vars *vars)
{
	vars->lexer->curr_token[vars->lexer->token_pos++] = vars->lexer->c;
	vars->lexer->line_pos++;
}

t_size	is_mult_op(t_vars *vars)
{
	if (vars->lexer->token_pos == 1 && char_is(MULT_OP, \
		vars->lexer->curr_token[vars->lexer->token_pos - 1]) \
		&& is_valid_mult_op(vars->lexer->c, vars))
		return (1);
	return (0);
}

t_size	is_op(t_vars *vars)
{
	if (vars->lexer->token_pos && \
		char_is(OPERATOR, vars->lexer->curr_token[vars->lexer->token_pos - 1]) \
		&& !is_valid_mult_op(vars->lexer->c, vars))
		return (1);
	return (0);
}

t_size	is_parameter(t_vars *vars)
{
	if (char_is("$", vars->lexer->c) \
		&& vars->line[vars->lexer->line_pos + 1])
		return (1);
	return (0);
}

void	handle_single_qt(t_vars *vars)
{
	while (1)
	{
		if (vars->lexer->c && char_is("'", vars->lexer->c))
			break ;
		if (!vars->lexer->c)
		{
			vars->lexer->curr_token[vars->lexer->token_pos++] = '\n';
			free_null((void **)&vars->line);
			vars->lexer->line_pos = 0;
			vars->line = readline("> ");
			add_history(vars->line);
			vars->lexer->c = vars->line[vars->lexer->line_pos];
			continue ;
		}
		vars->lexer->curr_token[vars->lexer->token_pos++] = vars->lexer->c;
		vars->lexer->c = vars->line[++vars->lexer->line_pos];
	}
}
