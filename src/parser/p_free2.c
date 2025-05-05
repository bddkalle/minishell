/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_free2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fschnorr <fschnorr@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 15:13:48 by fschnorr          #+#    #+#             */
/*   Updated: 2025/05/05 00:20:49 by fschnorr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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

void	free_tmp_argv(char ***argv)
{
	t_size	i;

	i = 0;
	while (*argv[i])
		free_null((void **)&(*argv[i++]));
	free_null((void **)&(*argv));
}

void	free_parser_cmd_node(t_vars *vars)
{
	t_size	i;
	t_redir	*tmp;

	i = 0;
	while (vars->parser->node->u_data.s_command.argv && \
	vars->parser->node->u_data.s_command.argv[i])
		free_null((void **)&vars->parser->node->\
					u_data.s_command.argv[i++]);
	free_null((void **)&vars->parser->node->u_data.s_command.argv);
	while (vars->parser->node->u_data.s_command.redirs)
	{
		tmp = vars->parser->node->u_data.s_command.redirs->next;
		free_null((void **)&vars->parser->node->\
					u_data.s_command.redirs);
		vars->parser->node->u_data.s_command.redirs = tmp;
	}
	free_null((void **)&vars->parser->node);
}
