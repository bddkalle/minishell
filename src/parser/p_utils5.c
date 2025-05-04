/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_utils5.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fschnorr <fschnorr@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 14:55:34 by fschnorr          #+#    #+#             */
/*   Updated: 2025/05/05 00:26:04 by fschnorr         ###   ########.fr       */
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
		{
			vars->lexer->curr_token[vars->lexer->token_pos++] = vars->lexer->c;
			vars->lexer->line_pos++;
			break ;
		}
		if (!vars->lexer->c)
		{
			ft_putstr_fd(\
			"minishell: syntax error: unexpected end of file in single-quote\n"\
			, 2);
			vars->exit_status = 2;
			free_null_readline(vars);
			return ;
		}
		vars->lexer->curr_token[vars->lexer->token_pos++] = vars->lexer->c;
		vars->lexer->c = vars->line[++vars->lexer->line_pos];
	}
}
