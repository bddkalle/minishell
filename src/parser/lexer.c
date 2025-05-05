/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdahne <cdahne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 10:47:17 by fschnorr          #+#    #+#             */
/*   Updated: 2025/05/05 08:43:57 by cdahne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	create_token(t_vars *vars)
{
	t_token	*node;

	vars->lexer->curr_token[vars->lexer->token_pos] = '\0';
	node = _malloc(sizeof(t_token), vars);
	*vars->lexer->next_node = node;
	*node = (t_token){};
	node->next = NULL;
	node->value = ft_strdup(vars->lexer->curr_token);
	if (!node->value)
		error_exit(vars, "strdup failed to create new token", EXIT_FAILURE);
	node->type = vars->lexer->curr_token_type;
	node->type = token_identifier(vars);
}

t_token_type	token_identifier(t_vars *vars)
{
	if (char_is(OPERATOR, vars->lexer->curr_token[vars->lexer->token_pos - 1]))
	{
		if (!ft_strncmp("<<", vars->lexer->curr_token, 2))
			return (TOKEN_HEREDOC);
		else if (!ft_strncmp(">>", vars->lexer->curr_token, 2))
			return (TOKEN_REDIRECT_APPEND);
		else if (!ft_strncmp("<", vars->lexer->curr_token, 1))
			return (TOKEN_REDIRECT_IN);
		else if (!ft_strncmp(">", vars->lexer->curr_token, 1))
			return (TOKEN_REDIRECT_OUT);
		else if (!ft_strncmp("&&", vars->lexer->curr_token, 2))
			return (TOKEN_AND);
		else if (!ft_strncmp("||", vars->lexer->curr_token, 2))
			return (TOKEN_OR);
		else if (!ft_strncmp("|", vars->lexer->curr_token, 1))
			return (TOKEN_PIPE);
		else if (!ft_strncmp("(", vars->lexer->curr_token, 1))
			return (TOKEN_PARENT_LEFT);
		else if (!ft_strncmp(")", vars->lexer->curr_token, 1))
			return (TOKEN_PARENT_RIGHT);
	}
	if (token_cof_digits(vars->lexer->curr_token) && (vars->lexer->c == '<' \
	|| vars->lexer->c == '>') && OPEN_MAX > ft_atoi(vars->lexer->curr_token))
		return (TOKEN_IO_NUMBER);
	return (TOKEN);
}

void	handle_quoted_input(t_vars *vars)
{
	vars->lexer->curr_token[vars->lexer->token_pos++] = vars->lexer->c;
	vars->lexer->c = vars->line[++vars->lexer->line_pos];
	if (vars->lexer->state == IN_SINGLE_QUOTE)
		handle_single_qt(vars);
	else if (vars->lexer->state == IN_DOUBLE_QUOTE)
		handle_double_qt(vars);
	if (vars->lexer)
		vars->lexer->state = NORMAL;
}

void	lexer(t_vars *vars)
{
	init_lexer(vars);
	while (vars->lexer)
	{
		vars->lexer->c = vars->line[vars->lexer->line_pos];
		if (vars->lexer->c == '\0')
		{
			handle_eoi(vars);
			break ;
		}
		else if (is_mult_op(vars))
			fill_token(vars);
		else if (is_op(vars))
			delimit_operator(vars);
		else if (char_is(QUOTES, vars->lexer->c))
			handle_quotes(vars);
		else if (is_parameter(vars))
			expand_parameter(vars);
		else if (char_is(OPERATOR, vars->lexer->c))
			handle_operator(vars);
		else if (is_whitespace(vars->lexer->c))
			handle_whitespace(vars);
		else
			fill_token(vars);
	}
	//debug_lexer(vars);
}
