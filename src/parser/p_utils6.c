/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_utils6.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fschnorr <fschnorr@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 14:55:34 by fschnorr          #+#    #+#             */
/*   Updated: 2025/04/29 23:45:53 by fschnorr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	handle_double_qt(t_vars *vars)
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
		else if (char_is("$", vars->lexer->c) && !char_is(" ", \
		vars->line[vars->lexer->line_pos + 1]) \
		&& !char_is("\"", vars->line[vars->lexer->line_pos + 1]))
		{
			expand_parameter(vars);
			continue ;
		}
		vars->lexer->curr_token[vars->lexer->token_pos++] = vars->lexer->c;
		vars->lexer->c = vars->line[++vars->lexer->line_pos];
	}
}

void	expand_exit_status(t_vars *vars)
{
	char	*substitute;

	substitute = ft_itoa(vars->exit_status);
	ft_strlcpy(vars->lexer->curr_token + vars->lexer->token_pos, \
				substitute, ft_strlen(substitute) + 1);
	vars->lexer->token_pos += ft_strlen(substitute);
	free_null((void **)&substitute);
	vars->lexer->c = vars->line[++vars->lexer->line_pos];
}
