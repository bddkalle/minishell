/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fschnorr <fschnorr@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 12:28:44 by fschnorr          #+#    #+#             */
/*   Updated: 2025/03/11 16:36:01 by fschnorr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	*_malloc(size_t size, t_vars *vars)
{
	void	*ptr;

	ptr = NULL;
	if (!size)
		return (NULL);
	ptr = malloc(size);
	if (!ptr)
		error_exit(vars, "Could not allocate memory", EXIT_FAILURE);	
	return (ptr);
}
