/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fschnorr <fschnorr@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 16:45:51 by fschnorr          #+#    #+#             */
/*   Updated: 2025/03/12 16:06:55 by fschnorr         ###   ########.fr       */
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
	free_null_token(vars);
	free_null((void **)&vars->line);
}

void	free_null_token(t_vars *vars)
{
	t_token	*tmp;

	free_null((void **)&vars->lexer->curr_token);

	while (vars->token)
	{
		free_null((void **)&vars->token->value);
		tmp = vars->token->next;
		free_null((void **)&vars->token);
		vars->token = tmp;
	}
}

void	free_all(t_vars *vars)
{
	close_all(vars);
	rl_clear_history();
	free_parser(vars);
	free_null_token(vars);
	free_null((void **)&vars->line);
	free_null((void **)&vars->lexer);
	free_null((void **)&vars->parser);
	free_null((void **)&vars->ast);
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
	_close(vars->prompt->fd_hostname);
}
