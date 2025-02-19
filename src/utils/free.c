/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fschnorr <fschnorr@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 16:45:51 by fschnorr          #+#    #+#             */
/*   Updated: 2025/02/19 13:08:21 by fschnorr         ###   ########.fr       */
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
	if (!vars->prompt)
		return ;
	if (vars->prompt->prompt)
		free_null(vars->prompt->prompt);
	if (vars->prompt)
		free_null(vars->prompt);
}