/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fschnorr <fschnorr@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 16:45:51 by fschnorr          #+#    #+#             */
/*   Updated: 2025/02/20 15:18:02 by fschnorr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	free_null(void *ptr)
{
	free(ptr);
	ptr = NULL;
}

void	free_all(t_vars *vars)
{
	rl_clear_history();
	if (vars->line)
		free_null(vars->line);
	if (!vars->prompt)
		return ;
	if (vars->prompt->prompt)
		free_null(vars->prompt->prompt);
	if (vars->prompt)
		free_null(vars->prompt);
}