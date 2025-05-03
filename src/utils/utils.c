/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fschnorr <fschnorr@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 12:28:44 by fschnorr          #+#    #+#             */
/*   Updated: 2025/05/03 22:49:57 by fschnorr         ###   ########.fr       */
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

char	*_getenv(t_vars *vars, char *var)
{
	t_envp	*tmp;

	tmp = vars->envp_ll;
	while (tmp)
	{
		if (!ft_strcmp(tmp->var, var))
			break ;
		tmp = tmp->next;
	}
	if (tmp)
		return (tmp->value);
	return (NULL);
}

void	create_cwd(t_vars *vars)
{
	vars->prompt->cwd = vars->prompt->pwd + (ft_strlen(vars->prompt->home));
	build_prompt(vars, ":~");
}
