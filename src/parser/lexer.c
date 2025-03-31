/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fschnorr <fschnorr@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 10:47:17 by fschnorr          #+#    #+#             */
/*   Updated: 2025/03/31 16:40:41 by fschnorr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/* t_lexer_state	set_lexer_state(t_vars *vars, char c)
{
	if(vars->lexer->state ==)
	{
		case NORMAL:
			if (c == '\'')
				vars->lexer->state = IN_SINGLE_QUOTE;
			else if (c == '"')
			{
				vars->lexer->state = IN_DOUBLE_QUOTE;
				vars->lexer->curr_token[vars->lexer->token_pos++] = c;
			}
			else if (c == '$')
			{
				vars->lexer->state = IN_VARIABLE;
				vars->lexer->curr_token[vars->lexer->token_pos++] = c;
			}
			else if (is_whitespace(c))
			{
				if (vars->lexer->token_pos > 0)
				{
					vars->lexer->curr_token[vars->lexer->token_pos] = '\0';
					*vars->lexer->next_node = create_token(TOKEN_WORD, vars);
					vars->lexer->next_node = &(*vars->lexer->next_node)->next;
					vars->lexer->token_pos = 0;
				}
				i++;
				continue;
			}
			break;
		case IN_SINGLE_QUOTE:
			if (c == '\'')
				vars->lexer->state = NORMAL;
			else
				;
	}
		return (vars->lexer->state);
}
 */
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
	//node->next = NULL;
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
	|| vars->lexer->c == '>'))
		return (TOKEN_IO_NUMBER);
	return (TOKEN_WORD);
}

/* void	set_token_type(t_vars *vars)
{
	vars->lexer->curr_token_type = TOKEN_WORD;
	if (vars->lexer->c == '|')
	{
		if (vars->line[vars->lexer->line_pos + 1] == '|')
		{
			vars->lexer->curr_token_type = TOKEN_OR;
			vars->lexer->line_pos++;
		}
		else
			vars->lexer->curr_token_type = TOKEN_PIPE;
	}
	else if (vars->lexer->c == '<')
	{
		if (vars->line[vars->lexer->line_pos + 1] == '<')
		{
			vars->lexer->curr_token_type = TOKEN_HEREDOC;
			vars->lexer->line_pos++;
		}
		else
			vars->lexer->curr_token_type = TOKEN_REDIRECT_IN;
	}
	else if (vars->lexer->c == '>')
	{
		if (vars->line[vars->lexer->line_pos + 1] == '>')
		{
			vars->lexer->curr_token_type = TOKEN_REDIRECT_APPEND;
			vars->lexer->line_pos++;
		}			
		else
			vars->lexer->curr_token_type = TOKEN_REDIRECT_OUT;
	}
}
 */
void	handle_quoted_input(t_vars *vars)
{
	vars->lexer->curr_token[vars->lexer->token_pos++] = vars->lexer->c;
	vars->lexer->line_pos++;
	vars->lexer->c = vars->line[vars->lexer->line_pos];	
	if (vars->lexer->state == IN_SINGLE_QUOTE)
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
			vars->lexer->line_pos++;
			vars->lexer->c = vars->line[vars->lexer->line_pos];
		}
	}
	else if (vars->lexer->state == IN_DOUBLE_QUOTE)
	{
		while (1)
		{
			if (vars->lexer->c && char_is("\"", vars->lexer->c))
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
			vars->lexer->line_pos++;
			vars->lexer->c = vars->line[vars->lexer->line_pos];
		}
	}
	vars->lexer->curr_token[vars->lexer->token_pos++] = vars->lexer->c;
	vars->lexer->line_pos++;
	vars->lexer->state = NORMAL;
}

void	prepare_lexer(t_vars *vars)
{
	//set_lexer_state(vars, c);
	token_identifier(vars);
}

void	lexer(t_vars *vars)
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

		// #6 (delimit before operator & set operator token)
		else if (char_is(OPERATOR, vars->lexer->c) && vars->lexer->state != IN_SINGLE_QUOTE \
		&& vars->lexer->state != IN_DOUBLE_QUOTE)
		{
			if (vars->lexer->token_pos > 0)
			{
				create_token(vars);
				vars->lexer->next_node = &(*vars->lexer->next_node)->next;
				vars->lexer->token_pos = 0;
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
		//state = lexer_state(vars, c, state, token_pos);
		//prepare_lexer(vars);
	}
	debug_lexer(vars);
}
