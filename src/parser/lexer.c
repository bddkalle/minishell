/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fschnorr <fschnorr@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 10:47:17 by fschnorr          #+#    #+#             */
/*   Updated: 2025/03/05 12:01:35 by fschnorr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include <stdio.h>

/* void	fill_token(t_vars *vars, char c, t_lexer_state state)
{
	if (!vars->token)
		vars->token->value = ft_strjoin("", (char *) c);

	
	
	//printf("%s\n", vars->token[0]->value);
}
 */
int		is_whitespace(char c)
{
	if (ft_strchr(DEL, c))
		return (1);
	return (0);
}

/* t_lexer_state	lexer_state(t_vars *vars, char c, t_lexer_state state, int token_pos)
{
	switch (state)
		{
			case NORMAL:
				if (c == '\'')
					state = IN_SINGLE_QUOTE;
				else if (c == '"')
				{
					state = IN_DOUBLE_QUOTE;
					vars->curr_token[token_pos++] = c;
				}
				else if (c == '$')
				{
					state = IN_VARIABLE;
					vars->curr_token[token_pos++] = c;
				}
				else if (is_whitespace(c))
				{
					if (token_pos > 0)
					{
						vars->curr_token[token_pos] = '\0';
						*next_node = create_token(TOKEN_WORD, vars);
						next_node = &(*next_node)->next;
						token_pos = 0;
					}
					i++;
					continue;
				}
				break;

			case IN_SINGLE_QUOTE:
				if (c == '\'')
					state = NORMAL;
				else
				 	;
		}
		return (state);
}
 */
t_token	*create_token(t_token_type type, t_vars *vars)
{
	t_token	*node;

	node = _malloc(sizeof(t_token), vars);
	node->type = type;
	node->value = strdup(vars->lexer->curr_token);
	if (!node->value)
		error_exit(vars, "strdup failed to create new token", EXIT_FAILURE);
	node->next = NULL;
	return (node);
}


void	lexer(t_vars *vars)
{
	int		i;
	char	c;

	vars->lexer->next_node = &vars->token;
	vars->lexer->curr_token = _malloc((ft_strlen(vars->line) + 1) * sizeof(vars->lexer->curr_token), vars);
	i = 0;
	vars->lexer->token_pos = 0;
	while (1)
	{
		c = vars->line[i];
		// End of input condition
		if (c == '\0')
		{
			if (vars->lexer->token_pos > 0)
			{
				vars->lexer->curr_token[vars->lexer->token_pos] = '\0';
				*vars->lexer->next_node = create_token(TOKEN_WORD, vars);
			}
			break;
		}
		//state = lexer_state(vars, c, state, token_pos);
		if (is_whitespace(c))
		{
			//if curr token (finish token)
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
		vars->lexer->curr_token[vars->lexer->token_pos++] = c;
		i++;
	/* //	printf("%c\n", c);
		if ((state = set_lexer_state(c, state)) == NORMAL)
			fill_token(vars, c, state); */
	}
}
