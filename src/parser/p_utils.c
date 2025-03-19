/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_utils.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fschnorr <fschnorr@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 14:55:34 by fschnorr          #+#    #+#             */
/*   Updated: 2025/03/19 13:10:02 by fschnorr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include <fcntl.h>

/* t_redir	*create_redir_node(t_vars *vars)
{
	t_redir	*node;

	node = _malloc(sizeof(t_redir), vars);

	return (node);
} */

t_redir	*handle_redirs(t_vars *vars)
{
	t_redir	*node;

	//vars->parser->node->u_data.s_command.redirs = create_redir_node(vars);
	node = _malloc(sizeof(t_redir), vars);
	if (vars->parser->curr_tok->type == TOKEN_REDIRECT_IN)
		node->type = REDIR_INPUT;
	else if (vars->parser->curr_tok->type == TOKEN_REDIRECT_OUT)
		node->type = REDIR_OUTPUT;
	else if (vars->parser->curr_tok->type == TOKEN_REDIRECT_APPEND)
		node->type = REDIR_APPEND;
	advance_token(vars);
	node->target = vars->parser->curr_tok->value;
	node->next = NULL;
	advance_token(vars);
	return (node);
}

int		current_token_is(char *s, t_vars *vars)
{
	if (strcmp(s, vars->parser->curr_tok->value) == 0)
		return (1);
	return (0);
}

void	advance_token(t_vars *vars)
{
	vars->parser->curr_tok = vars->parser->curr_tok->next;
}
