/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_utils.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fschnorr <fschnorr@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 14:55:34 by fschnorr          #+#    #+#             */
/*   Updated: 2025/03/12 13:59:43 by fschnorr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	current_token_is(char *s, t_vars *vars)
{
	if (strcmp(s, vars->parser->curr_tok->value) == 0)
		return (1);
	return (0);
}

void	advance_token(t_vars *vars)
{
	vars->parser->curr_tok = vars->parser->curr_tok->next;
}
