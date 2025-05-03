/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vboxuser <vboxuser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 11:54:32 by vboxuser          #+#    #+#             */
/*   Updated: 2025/05/03 11:54:33 by vboxuser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	free_envp(t_envp *envp)
{
	t_envp	*temp;

	while (envp)
	{
		temp = envp->next;
		free(envp->var);
		free(envp->value);
		free(envp);
		envp = temp;
	}
}
