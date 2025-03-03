/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fschnorr <fschnorr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 16:46:33 by fschnorr          #+#    #+#             */
/*   Updated: 2025/03/03 12:50:58 by fschnorr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	init_vars(t_vars *vars)
{
		*vars = (t_vars) {};
		vars->prompt = _malloc(sizeof(*vars->prompt), vars);
		*vars->prompt = (t_prompt){};
}