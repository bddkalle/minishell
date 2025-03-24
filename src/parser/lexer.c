/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fschnorr <fschnorr@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 10:47:17 by fschnorr          #+#    #+#             */
/*   Updated: 2025/03/20 12:29:35 by fschnorr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	is_whitespace(char c)
{
	if (ft_strchr(DEL, c))
		return (1);
	return (0);
}

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
/* void	create_token(t_vars *vars)
{

	*vars->lexer->next_node = _malloc(sizeof(t_token), vars);
	(*vars->lexer->next_node)->type = vars->lexer->curr_token_type;
	//node->value = strdup(vars->lexer->curr_token);
	node->value = NULL;
	if (!node->value)
		error_exit(vars, "strdup failed to create new token", EXIT_FAILURE);
	node->next = NULL;
} */
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
		vars->lexer->curr_token_type = TOKEN_PIPE;
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

void	prepare_lexer(t_vars *vars)
{
	//set_lexer_state(vars, c);
	set_token_type(vars);
}

void	lexer(t_vars *vars)
{
	init_lexer(vars);
	while (1)
	{
		vars->lexer->c = vars->line[vars->lexer->line_pos];
		// End of input condition|
		if (vars->lexer->c == '\0')
		{
			if (vars->lexer->token_pos > 0)
			{
				vars->lexer->curr_token[vars->lexer->token_pos] = '\0';
				create_token(vars);
				//*vars->lexer->next_node = create_token(vars);
			}
			break;
		}
		//state = lexer_state(vars, c, state, token_pos);
		if (is_whitespace(vars->lexer->c))
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
		prepare_lexer(vars);
		vars->lexer->curr_token[vars->lexer->token_pos++] = vars->lexer->c;
		vars->lexer->line_pos++;
	}
	debug_lexer(vars);
}
