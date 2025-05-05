/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_utils8.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fschnorr <fschnorr@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 14:55:34 by fschnorr          #+#    #+#             */
/*   Updated: 2025/05/05 02:20:45 by fschnorr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	closing_par(t_vars *vars, t_token *curr_tok)
{
	curr_tok = curr_tok->next;
	while (curr_tok)
	{
		if (curr_tok->type == TOKEN_PARENT_RIGHT)
			break ;
		curr_tok = curr_tok->next;
	}
	if (!curr_tok)
	{
		ft_putstr_fd("minishell: syntax error: missing »)«\n", 2);
		vars->exit_status = 2;
		free_null_token(vars);
		return (0);
	}
	return (1);
}

t_ast_node	*parse_expression(t_vars *vars)
{
	if (is_invalid_leading_op(vars->parser->curr_tok->type))
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
		ft_putstr_fd(vars->parser->curr_tok->value, 2);
		ft_putstr_fd("'\n", 2);
		vars->exit_status = 2;
		return (NULL);
	}
	return (parse_or_and(vars));
}

t_size	is_op2(t_token_type type)
{
	if (type == TOKEN_PIPE || type == TOKEN_AND || type == TOKEN_OR)
		return (1);
	return (0);
}

t_size	is_redir_op(t_token_type type)
{
	if ((type == TOKEN_REDIRECT_IN || \
		type == TOKEN_REDIRECT_OUT || \
		type == TOKEN_REDIRECT_APPEND || \
		type == TOKEN_HEREDOC))
		return (1);
	return (0);
}

t_size	is_redirexh_op(t_token_type type)
{
	if ((type == TOKEN_REDIRECT_IN || \
		type == TOKEN_REDIRECT_OUT || \
		type == TOKEN_REDIRECT_APPEND))
		return (1);
	return (0);
}
