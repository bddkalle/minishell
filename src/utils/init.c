/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fschnorr <fschnorr@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 16:46:33 by fschnorr          #+#    #+#             */
/*   Updated: 2025/03/05 12:02:04 by fschnorr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	init_vars(t_vars *vars)
{
		*vars = (t_vars) {};
		vars->prompt = _malloc(sizeof(*vars->prompt), vars);
		*vars->prompt = (t_prompt){};
		vars->lexer = _malloc(sizeof(*vars->lexer), vars);
		*vars->lexer = (t_lexer){};
		vars->lexer->state = NORMAL;

}