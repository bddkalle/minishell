/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vboxuser <vboxuser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 10:47:17 by fschnorr          #+#    #+#             */
/*   Updated: 2025/05/04 10:46:20 by vboxuser         ###   ########.fr       */
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
	vars->lexer->curr_token[vars->lexer->token_pos++] = vars->lexer->c;
	vars->lexer->line_pos++;
	vars->lexer->state = NORMAL;
}

/* void	lexer(t_vars *vars)
{
	init_lexer(vars);
	while (1)
	{
		vars->lexer->c = vars->line[vars->lexer->line_pos];
		// #1 (End of input condition)
		if (vars->lexer->c == '\0')
		{
			if (vars->lexer->token_pos > 0)
				create_token(vars);
			break;
		}
		// #2 (&& and || operator)
		else if (vars->lexer->token_pos == 1 && char_is(MULT_OP, vars->lexer->curr_token[vars->lexer->token_pos - 1])\
		&& vars->lexer->state != IN_SINGLE_QUOTE && vars->lexer->state != IN_DOUBLE_QUOTE \
		&& is_valid_mult_op(vars->lexer->c, vars))
		{
			vars->lexer->curr_token[vars->lexer->token_pos++] = vars->lexer->c;
			vars->lexer->line_pos++;
		}
		// #3 (delimit after operator)
		else if (vars->lexer->token_pos && char_is(OPERATOR, vars->lexer->curr_token[vars->lexer->token_pos - 1])\
		&& !is_valid_mult_op(vars->lexer->c, vars))
		{
			create_token(vars);
			vars->lexer->next_node = &(*vars->lexer->next_node)->next;
			vars->lexer->token_pos = 0;
			vars->lexer->curr_token[0] = '\0';
		}
		// #4 (quotes)
		else if (char_is(QUOTES, vars->lexer->c) && vars->lexer->state != IN_SINGLE_QUOTE \
		&& vars->lexer->state != IN_DOUBLE_QUOTE)
		{
			if (char_is("'", vars->lexer->c))
				vars->lexer->state = IN_SINGLE_QUOTE;
			if (char_is("\"", vars->lexer->c))
				vars->lexer->state = IN_DOUBLE_QUOTE;
			handle_quoted_input(vars);
		}
		// #5 (parameter expansion)
		else if (char_is("$", vars->lexer->c) && vars->line[vars->lexer->line_pos + 1])
		{
			expand_parameter(vars);
		}

		// #6 (delimit before operator & set operator token)
		else if (char_is(OPERATOR, vars->lexer->c) && vars->lexer->state != IN_SINGLE_QUOTE \
		&& vars->lexer->state != IN_DOUBLE_QUOTE)
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

		// #7 AFAIK: CAN BE SKIPPED FOR INTERACTIVE MODE ONLY (delimit if <newline> - readline removes final newline, so unclear when/if lexer will ever get <newline>)

		// #8 (delimit if <blank>)
		else if (is_whitespace(vars->lexer->c) && vars->lexer->state != IN_SINGLE_QUOTE \
		&& vars->lexer->state != IN_DOUBLE_QUOTE)
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
		// #9 (if previous char = part of word > append char)
		else if (vars->lexer->token_pos && !char_is(OPERATOR, vars->lexer->curr_token[vars->lexer->token_pos - 1]))
		{
			vars->lexer->curr_token[vars->lexer->token_pos++] = vars->lexer->c;
			vars->lexer->line_pos++;
		}
		// #10 comments not needed

		// #11 (curr_char = start of new word)
		else
		{
			vars->lexer->curr_token[vars->lexer->token_pos++] = vars->lexer->c;
			vars->lexer->line_pos++;
		}
	}
	debug_lexer(vars);
}
 */

void	lexer(t_vars *vars)
{
	init_lexer(vars);
	while (1)
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
