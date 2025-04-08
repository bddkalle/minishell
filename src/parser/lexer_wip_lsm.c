/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fschnorr <fschnorr@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 10:47:17 by fschnorr          #+#    #+#             */
/*   Updated: 2025/03/25 14:55:55 by fschnorr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	is_whitespace(char c)
{
	if (ft_strchr(DEL, c))
		return (1);
	return (0);
}

/* t_lexer_state	set_lexer_state(t_vars *vars)
{
	if (vars->lexer->state == NORMAL)				// NORMAL MODE
	{
		if (vars->lexer->c == '\'')
		{
			vars->lexer->state = IN_SINGLE_QUOTE;
			vars->lexer->line_pos++;
			continue;
		}
		else if (vars->lexer->c == '"')
		{
			vars->lexer->state = IN_DOUBLE_QUOTE;
			vars->lexer->line_pos++;
			continue;
		}
		else if (vars->lexer->c == '$')
		{
			vars->lexer->state = IN_VARIABLE;
			vars->lexer->line_pos++;	
		}
		else if (is_whitespace(vars->lexer->c))
		{
			if (vars->lexer->token_pos > 0)
			{
				vars->lexer->curr_token[vars->lexer->token_pos] = '\0';
				create_token(vars);
				vars->lexer->next_node = &(*vars->lexer->next_node)->next;
				vars->lexer->token_pos = 0;
			}
			vars->lexer->line_pos++;
			continue;
		}
		else
			vars->lexer->curr_token[vars->lexer->token_pos++] = vars->lexer->c;
	}
	else if (vars->lexer->state == IN_SINGLE_QUOTE)		// SINGLE QUOTE MODE
	{
		if (vars->lexer->c == '\'')
		{
			vars->lexer->state = NORMAL;
			vars->lexer->line_pos++;
			continue;
		}
		else
			vars->lexer->curr_token[vars->lexer->token_pos++] = vars->lexer->c;
	}
	else if (vars->lexer->state == IN_DOUBLE_QUOTE)		// DOUBLE QUOTE MODE
	{
		if (vars->lexer->c == '"')
		{
			vars->lexer->state = NORMAL;
			vars->lexer->line_pos++;
			continue;
		}
		else if (vars->lexer->c == '$')
		{
			vars->lexer->state = IN_VARIABLE;
			vars->lexer->curr_token[vars->lexer->token_pos++] = vars->lexer->c;
		}
		else
			vars->lexer->curr_token[vars->lexer->token_pos++] = vars->lexer->c;
	}
	else if (vars->lexer->state == IN_VARIABLE)		// VARIABLE MODE
	{
		if (!is_valid_var_char(vars->lexer->c))
		{
			vars->lexer->state = NORMAL;
			continue;
		}
		else
			vars->lexer->curr_token[vars->lexer->token_pos++] = vars->lexer->c;
	}
		return (vars->lexer->state);		
}
 */
void	create_token(t_vars *vars)
{
	t_token	*node;

	node = _malloc(sizeof(t_token), vars);
	*vars->lexer->next_node = node;
	*node = (t_token){};
	node->type = vars->lexer->curr_token_type;
	node->value = strdup(vars->lexer->curr_token);
	if (!node->value)
		error_exit(vars, "strdup failed to create new token", EXIT_FAILURE);
	node->next = NULL;
}

void	set_token_type(t_vars *vars)
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
	else if (vars->lexer->c == '&')
	{
		if (vars->line[vars->lexer->line_pos + 1] == '&')
		{
			vars->lexer->curr_token_type = TOKEN_AND;
			vars->lexer->line_pos++;
		}
		else
			vars->lexer->curr_token_type = TOKEN_AND_SYNER;
	}
}

/* void	prepare_lexer(t_vars *vars)
{
	set_lexer_state(vars);
	set_token_type(vars);
}
 */
void	lexer(t_vars *vars)
{
	init_lexer(vars);
	while (1)
	{
		vars->lexer->c = vars->line[vars->lexer->line_pos];
		// End of input condition
		if (vars->lexer->c == '\0')
		{
			if (vars->lexer->token_pos > 0)
			{
				vars->lexer->curr_token[vars->lexer->token_pos] = '\0';
				create_token(vars);
			}
			break;
		}
		if (vars->lexer->line_pos && is_op_char(vars->line[vars->lexer->line_pos - 1]) == )
		//state = lexer_state(vars, c, state, token_pos);
	/* 	if (is_whitespace(vars->lexer->c))
		{
			if (vars->lexer->token_pos > 0)
			{
				vars->lexer->curr_token[vars->lexer->token_pos] = '\0';
				create_token(vars);
				vars->lexer->next_node = &(*vars->lexer->next_node)->next;
				vars->lexer->token_pos = 0;
			}
			vars->lexer->line_pos++;
			continue;
		} */
		if (vars->lexer->state == NORMAL)				// NORMAL MODE
		{
			if (vars->lexer->c == '\'')
			{
				vars->lexer->state = IN_SINGLE_QUOTE;
				vars->lexer->line_pos++;
				continue;
			}
			else if (vars->lexer->c == '"')
			{
				vars->lexer->state = IN_DOUBLE_QUOTE;
				vars->lexer->line_pos++;
				continue;
			}
			else if (vars->lexer->c == '$')
			{
				vars->lexer->state = IN_VARIABLE;
				vars->lexer->line_pos++;	
			}
			else if (is_whitespace(vars->lexer->c))
			{
				if (vars->lexer->token_pos > 0)
				{
					vars->lexer->curr_token[vars->lexer->token_pos] = '\0';
					create_token(vars);
					vars->lexer->next_node = &(*vars->lexer->next_node)->next;
					vars->lexer->token_pos = 0;
				}
				vars->lexer->line_pos++;
				continue;
			}
			else
				vars->lexer->curr_token[vars->lexer->token_pos++] = vars->lexer->c;
		}
		else if (vars->lexer->state == IN_SINGLE_QUOTE)		// SINGLE QUOTE MODE
		{
			if (vars->lexer->c == '\'')
			{
				vars->lexer->state = NORMAL;
				vars->lexer->line_pos++;
				continue;
			}
			else
				vars->lexer->curr_token[vars->lexer->token_pos++] = vars->lexer->c;
		}
		else if (vars->lexer->state == IN_DOUBLE_QUOTE)		// DOUBLE QUOTE MODE
		{
			if (vars->lexer->c == '"')
			{
				vars->lexer->state = NORMAL;
				vars->lexer->line_pos++;
				continue;
			}
			else if (vars->lexer->c == '$')
			{
				vars->lexer->state = IN_VARIABLE;
				vars->lexer->curr_token[vars->lexer->token_pos++] = vars->lexer->c;
			}
			else
				vars->lexer->curr_token[vars->lexer->token_pos++] = vars->lexer->c;
		}
		/* 	else if (vars->lexer->state == IN_VARIABLE)		// VARIABLE MODE
		{
			if (!is_valid_var_char(vars->lexer->c))
			{
				vars->lexer->state = NORMAL;
				continue;
			}
			else
				vars->lexer->curr_token[vars->lexer->token_pos++] = vars->lexer->c;
		}
		*/
		vars->lexer->line_pos++;
	}
	debug_lexer(vars);
}
