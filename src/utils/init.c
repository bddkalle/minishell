/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vboxuser <vboxuser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 16:46:33 by fschnorr          #+#    #+#             */
/*   Updated: 2025/04/24 21:32:23 by vboxuser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	init_vars(t_vars *vars)
{
	*vars = (t_vars){};
	vars->prompt = _malloc(sizeof(*vars->prompt), vars);
	*vars->prompt = (t_prompt){};
}

void	init_envp(t_vars *vars, char **param)
{
	t_envp	*envp;
	t_envp	*temp;
	t_envp	*last;
	int	count;

	count = 0;
	envp = NULL;
	while (param[count])
	{
		temp = create_envp_node(param[count]);
		if (!temp)
			error_exit(vars, strerror(errno), errno); // double checl with felix
		temp->next = NULL;
		if (!envp)
			envp = temp;
		else
		 	last->next = temp;
		last = temp;
		count++;
	}
	vars->envp_ll = envp;
}
