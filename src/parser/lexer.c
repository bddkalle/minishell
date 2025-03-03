/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fschnorr <fschnorr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 10:47:17 by fschnorr          #+#    #+#             */
/*   Updated: 2025/03/03 12:50:30 by fschnorr         ###   ########.fr       */
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

/* t_lexer_state	set_lexer_state(char c, t_lexer_state state)
{
	switch (state)
		{
			case NORMAL:
				if (c == '\'')
					state = IN_SINGLE_QUOTE;
				else if (c == '"')
					state = IN_DOUBLE_QUOTE;
				else if (c == '$')
					state = IN_VARIABLE;
			//;//finish token, if any
				else
					//add char to token
					fill_token(vars, state);
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
	node->value = strdup(vars->curr_token);
	if (!node->value)
		error_exit(vars, "strdup failed to create new token", EXIT_FAILURE);
	node->next = NULL;
	return (node);
	
}


void	lexer(t_vars *vars)
{
	t_lexer_state	state;
	char			c;
	int				i;
	int				token_pos;
	t_token			**last_ptr;

	state = NORMAL;
	last_ptr = &vars->token;
	vars->curr_token = _malloc((ft_strlen(vars->line) + 1) * sizeof(vars->curr_token), vars);
	i = 0;
	token_pos = 0;
	while (1)
	{
		c = vars->line[i];
		// End of input condition
		if (c == '\0')
		{
			if (token_pos > 0)
			{
				vars->curr_token[token_pos] = '\0';
				*last_ptr = create_token(TOKEN_WORD, vars);
				last_ptr = &vars->token->next;
			}
			break;
		}
		if (is_whitespace(c))
		{
			//if curr token (finish token)
			if (token_pos > 0)
			{
				vars->curr_token[token_pos] = '\0';
				*last_ptr = create_token(TOKEN_WORD, vars);
				last_ptr = &vars->token->next;
				token_pos = 0;
			}
			i++;
			continue;
		}
		vars->curr_token[token_pos++] = c;
		i++;
	/* //	printf("%c\n", c);
		if ((state = set_lexer_state(c, state)) == NORMAL)
			fill_token(vars, c, state); */
	}
	free_null(vars->curr_token);
}
