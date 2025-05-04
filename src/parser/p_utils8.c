/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_utils8.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fschnorr <fschnorr@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 14:55:34 by fschnorr          #+#    #+#             */
/*   Updated: 2025/05/04 21:06:22 by fschnorr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	closing_par(t_vars *vars, t_token *curr_tok)
{
	curr_tok = curr_tok->next;
	while (curr_tok)
	{
		if (curr_tok->type == TOKEN_PARENT_RIGHT)
			break ;
		curr_tok = curr_tok->next;
	}
	if (!curr_tok)
	{
		ft_putstr_fd("minishell: syntax error: missing »)«\n", 2);
		vars->exit_status = 2;
		free_null_token(vars);
		return (0);
	}
	return (1);
}
