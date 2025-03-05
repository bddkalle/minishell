/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fschnorr <fschnorr@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 16:45:51 by fschnorr          #+#    #+#             */
/*   Updated: 2025/03/04 12:27:52 by fschnorr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	free_null_readline(t_vars *vars)
{
	free_null_token(vars);
	free_null(vars->line);
}

void	free_null_token(t_vars	*vars)
{
	t_token	*tmp;

	free_null(vars->curr_token);
	while (vars->token)
	{
		free_null(vars->token->value);
		tmp = vars->token->next;
		free_null(vars->token);
		vars->token = tmp;
	}
	free_null(vars->token);
}

void	free_null(void *ptr)
{
	if (ptr)
	{
		free(ptr);
		ptr = NULL;
	}
}

void	free_all(t_vars *vars)
{
	close_all(vars);
	rl_clear_history();
	//free_null(vars->curr_token);
	free_null_token(vars);
	free_null(vars->line);
	free_null(vars->prompt->hostname);
	if (!vars->prompt)
		return ;
	free_null(vars->prompt->prompt);
	free_null(vars->prompt);
}

void	_close(int fd)
{
	if (fd)
		close (fd);
}

void	close_all(t_vars *vars)
{
	_close(vars->prompt->fd_hostname);
}
