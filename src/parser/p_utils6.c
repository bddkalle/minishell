/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_utils6.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fschnorr <fschnorr@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 14:55:34 by fschnorr          #+#    #+#             */
/*   Updated: 2025/05/05 02:17:51 by fschnorr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	handle_double_qt(t_vars *vars)
{
	while (1)
	{
		if (vars->lexer->c && char_is("\"", vars->lexer->c))
		{
			vars->lexer->curr_token[vars->lexer->token_pos++] = vars->lexer->c;
			vars->lexer->line_pos++;
			break ;
		}
		if (!vars->lexer->c)
		{
			syntax_error_double_quote(vars);
			return ;
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
	if (!substitute)
		error_exit(vars, "ft_itoa failed to convert exit_status", EXIT_FAILURE);
	ft_strlcpy(vars->lexer->curr_token + vars->lexer->token_pos, \
				substitute, ft_strlen(substitute) + 1);
	vars->lexer->token_pos += ft_strlen(substitute);
	free_null((void **)&substitute);
	vars->lexer->c = vars->line[++vars->lexer->line_pos];
}

void	get_parameter(t_vars *vars, char *parameter)
{
	size_t	i;

	i = 0;
	vars->exit_status = 0;
	while (vars->lexer->c && is_valid_name(vars->lexer->c))
	{
		parameter[i++] = vars->lexer->c;
		vars->lexer->c = vars->line[++vars->lexer->line_pos];
		parameter[i] = '\0';
	}
	parameter[i] = '\0';
}

void	substitute_parameter(t_vars *vars, char *substitute)
{
	ft_strlcpy(vars->lexer->curr_token + vars->lexer->token_pos, \
		substitute, ft_strlen(substitute) + 1);
	vars->lexer->token_pos += ft_strlen(substitute);
}
