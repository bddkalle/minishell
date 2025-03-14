/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_free.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fschnorr <fschnorr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 15:13:48 by fschnorr          #+#    #+#             */
/*   Updated: 2025/03/14 13:17:30 by fschnorr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	free_parser(t_vars *vars)
{
	int	i;

	if (vars->ast && vars->ast->type == AST_COMMAND)
	{
		i = 0;
		while (vars->ast->u_data.s_command.argv[i])
			free_null((void **)&vars->ast->u_data.s_command.argv[i++]);
		free_null((void **)&vars->ast->u_data.s_command.argv);
		free_null((void **)&vars->ast);
		vars->parser->node = NULL;
	}
	else if (vars->parser)
	{
		if (vars->parser->node && vars->parser->node->type == AST_COMMAND)
		{
			i = 0;
			while (vars->parser->node->u_data.s_command.argv[i])
				free_null((void **)&vars->parser->node->u_data.s_command.argv[i++]);
			free_null((void **)&vars->parser->node->u_data.s_command.argv);
			free_null((void **)&vars->parser->node);
		}
	}
	free_null_token(vars);
	free_null((void **)&vars->line);
	free_null((void **)&vars->lexer);
	free_null((void **)&vars->parser);
}

void	free_null_token(t_vars *vars)
{
	t_token	*tmp;

	if (vars->lexer)
		free_null((void **)&vars->lexer->curr_token);

	while (vars->token)
	{
		free_null((void **)&vars->token->value);
		tmp = vars->token->next;
		free_null((void **)&vars->token);
		vars->token = tmp;
	}
}

void	close_parser(t_vars *vars)
{
	_close(vars->prompt->fd_hostname);
}
