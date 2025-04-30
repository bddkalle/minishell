/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdahne <cdahne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 16:45:51 by fschnorr          #+#    #+#             */
/*   Updated: 2025/04/30 15:45:37 by cdahne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	free_null(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
	}
}

void	free_null_readline(t_vars *vars)
{
	free_parser(vars);
}

void	free_all(t_vars *vars)
{
	close_all(vars);
	rl_clear_history();
	free_parser(vars);
	free_envp(vars->envp_ll);
	if (vars->prompt)
	{
		free_null((void **)&vars->prompt->hostname);
		free_null((void **)&vars->prompt->prompt);
		free_null((void **)&vars->prompt);
	}
}

void	_close(int fd)
{
	if (fd)
		close (fd);
}

void	close_all(t_vars *vars)
{
	close_parser(vars);
}
