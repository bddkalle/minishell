/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_utils2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fschnorr <fschnorr@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 14:55:34 by fschnorr          #+#    #+#             */
/*   Updated: 2025/04/01 16:57:05 by fschnorr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_size	is_whitespace(char c)
{
	if (ft_strchr(DEL, c))
		return (1);
	return (0);
}

t_size	is_valid_mult_op(char c, t_vars *vars)
{
	if (c == vars->lexer->curr_token[vars->lexer->token_pos - 1])
		return (1);
	return (0);
}

t_size	token_cof_digits(char *s)
{
	t_size	i;

	i = 0;
	while (s[i])
	{
		if (!ft_isdigit(s[i++]))
			return (0);
	}
	return (1);
}

void	reclassification(t_vars *vars)
{
	t_token	*tmp;

	tmp = vars->token;
	while (tmp)
	{
		// #1 if reserved cmd name (if, then, else, fi,...) [OUT OF SCOPE] else TOKEN -> TOKEN_WORD
		if (tmp->type == TOKEN)
			tmp->type = TOKEN_WORD;
		
		// #2 redirection to or from filename
		//HIER WEITER MIT HEREDOC REDIRCTION

		// #3 redirection from here-document

		// #4 case statement termination [OUT OF SCOPE]

		// #5 NAME in FOR [OUT OF SCOPE]

		// #6 Third word of FOR and CASE [OUT OF SCOPE]

		// #7 Assignment preceding command name [OUT OF SCOPE]

		// #8 NAME in function [OUT OF SCOPE]

		// #9 Body of function [OUT OF SCOPE]
		
		tmp = tmp->next;
	}
}

/* int	last_token_type_is(t_token_type type, t_vars *vars)
{
	t_token	*tmp;

	tmp = vars->token;
	if (tmp)
	{
		if (tmp->next)
		{
			while (tmp->next->next)
				tmp = tmp->next;
		}
	}
	if (tmp->type == type)
		return (1);
	return (0);
} */
