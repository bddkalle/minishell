/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fschnorr <fschnorr@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 10:47:17 by fschnorr          #+#    #+#             */
/*   Updated: 2025/02/27 10:25:13 by fschnorr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include <stdio.h>

void	fill_token(t_vars *vars, char c, t_lexer_state state)
{
	if (!vars->token)
		vars->token->value = ft_strjoin("", (char *) c);

	
	
	//printf("%s\n", vars->token[0]->value);
}

int		is_whitespace(char c)
{
	if (ft_strchr(DEL, c))
		return (1);
	return (0);
}

t_lexer_state	set_lexer_state(char c, t_lexer_state state)
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

void	lexer(t_vars *vars)
{
	t_lexer_state	state;
	char			c;
	int				i;
	int				j;

	state = NORMAL;
	vars->curr_token = Malloc((ft_strlen(vars->line) + 1) * sizeof(vars->curr_token), vars);
	i = -1;
	j = 0;
	while (vars->line[++i])
	{
		c = vars->line[i];
		if (is_whitespace(c))
			//if curr token (finish token)
			continue;
	//	printf("%c\n", c);
		if ((state = set_lexer_state(c, state)) == NORMAL)
			fill_token(vars, c, state);
		}
}
