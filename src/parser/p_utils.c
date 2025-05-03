/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_utils.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fschnorr <fschnorr@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 14:55:34 by fschnorr          #+#    #+#             */
/*   Updated: 2025/05/03 22:36:32 by fschnorr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	fill_cmd_argv(t_vars *vars)
{
	t_token	*tmp_token;
	t_size	word_count;
	t_size	i;
	char	**argv;

	tmp_token = vars->parser->curr_tok;
	word_count = 0;
	argv = NULL;
	while (tmp_token && (tmp_token->type == TOKEN_WORD || \
	tmp_token->type == TOKEN_EXIT_STATUS))
	{
		word_count++;
		tmp_token = tmp_token->next;
	}
	i = 0;
	if (vars->parser->node->u_data.s_command.argv)
		i = continue_argv(vars, word_count, &argv);
	else
		argv = _malloc((word_count + 1) * sizeof(char *), vars);
	fill_argv(vars, argv, i);
}

t_redir	*handle_redirs(t_vars *vars)
{
	t_redir	*node;

	node = _malloc(sizeof(t_redir), vars);
	*node = (t_redir){};
	node->fd = -1;
	if (vars->parser->curr_tok->type == TOKEN_IO_NUMBER)
	{
		node->fd = ft_atoi(vars->parser->curr_tok->value);
		advance_token(vars);
	}
	if (vars->parser->curr_tok->type == TOKEN_REDIRECT_IN)
		node->type = REDIR_INPUT;
	else if (vars->parser->curr_tok->type == TOKEN_REDIRECT_OUT)
		node->type = REDIR_OUTPUT;
	else if (vars->parser->curr_tok->type == TOKEN_REDIRECT_APPEND)
		node->type = REDIR_APPEND;
	else if (vars->parser->curr_tok->type == TOKEN_HEREDOC)
		node->type = REDIR_HEREDOC;
	advance_token(vars);
	node->target = vars->parser->curr_tok->value;
	node->next = NULL;
	advance_token(vars);
	return (node);
}

t_size	current_token_is(char *s, t_vars *vars)
{
	if (strcmp(s, vars->parser->curr_tok->value) == 0)
		return (1);
	return (0);
}

void	advance_token(t_vars *vars)
{
	vars->parser->curr_tok = vars->parser->curr_tok->next;
}

t_size	char_is(char *s, char c)
{
	if (ft_strchr(s, c))
		return (1);
	return (0);
}
