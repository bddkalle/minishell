/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fschnorr <fschnorr@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 10:47:17 by fschnorr          #+#    #+#             */
/*   Updated: 2025/02/25 13:21:56 by fschnorr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	fill_token(t_vars *vars, t_lexer_state state)
{
	if (!vars->token)
		vars->token[0]->value = ft_strdup("");
	
	
	//printf("%s\n", vars->token[0]->value);
}

void	lexer(t_vars *vars)
{
	t_lexer_state	state;
	char			c;
	int				i;
	int				j;

	state = NORMAL;
	i = 0;
	j = 0;
	while (vars->line[i])
	{
		while (is_whitespace(vars->line[i]))
			i++;
		c = vars->line[i];
// HIER WEITER: set_lexer_state()
		switch (state)
		{
			case NORMAL:
				if (c == '\'')
					state = IN_SINGLE_QUOTE;
				else if (c == '"')
					state = IN_DOUBLE_QUOTE;
				else if (c == '$')
					state = IN_VARIABLE;
			//	else if (is_whitespace(c))
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

	}
}
