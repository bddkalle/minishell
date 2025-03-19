/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_init.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fschnorr <fschnorr@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 16:40:39 by fschnorr          #+#    #+#             */
/*   Updated: 2025/03/19 12:31:57 by fschnorr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	init_lexer(t_vars *vars)
{
	vars->lexer = _malloc(sizeof(*vars->lexer), vars);
	*vars->lexer = (t_lexer){};
	vars->lexer->state = NORMAL;
	vars->lexer->line_pos = 0;
	vars->lexer->token_pos = 0;
	vars->lexer->next_node = &vars->token;
	vars->lexer->curr_token = _malloc((ft_strlen(vars->line) + 1) * sizeof(vars->lexer->curr_token), vars);
}

void	init_parser(t_vars *vars)
{
	vars->parser = _malloc(sizeof(*vars->parser), vars);
	*vars->parser = (t_parser){};
	vars->parser->curr_tok = vars->token;
}
