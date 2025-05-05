/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_utils7.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdahne <cdahne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 14:55:34 by fschnorr          #+#    #+#             */
/*   Updated: 2025/05/05 13:17:07 by cdahne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	handle_consecutive_op(t_vars *vars, t_token *curr_tok)
{
	ft_putstr_fd("minishell: syntax error near unexpected token »", \
	2);
	ft_putstr_fd(curr_tok->next->value, 2);
	ft_putstr_fd("«\n", 2);
	vars->exit_status = 2;
	free_null_token(vars);
}

t_node_type	set_op_type(t_token_type type)
{
	if (type == TOKEN_PIPE)
		return (AST_PIPE);
	else if (type == TOKEN_AND)
		return (AST_AND);
	else
		return (AST_OR);
}

int	continue_argv(t_vars *vars, int word_count, char ***argv)
{
	int	i;

	i = 0;
	while (vars->parser->node->u_data.s_command.argv[i++])
		word_count++;
	*argv = _malloc((word_count + 1) * sizeof(char *), vars);
	i = 0;
	while (vars->parser->node->u_data.s_command.argv[i])
	{
		(*argv)[i] = ft_strdup(vars->parser->node->u_data.s_command.argv[i]);
		if (!(*argv)[i++])
		{
			free_tmp_argv(argv);
			error_exit(vars, "strdup failed to fill nodes argv", EXIT_FAILURE);
		}
	}
	i = 0;
	while (vars->parser->node->u_data.s_command.argv[i])
		free_null((void **)&vars->parser->node->u_data.s_command.argv[i++]);
	free_null((void **)&vars->parser->node->u_data.s_command.argv);
	return (i);
}

void	fill_argv(t_vars *vars, char **argv, t_size i)
{
	while (vars->parser->curr_tok && (vars->parser->curr_tok->type == \
	TOKEN_WORD || vars->parser->curr_tok->type == TOKEN_EXIT_STATUS))
	{
		argv[i] = ft_strdup(vars->parser->curr_tok->value);
		if (!argv[i++])
		{
			free_tmp_argv(&argv);
			error_exit(vars, "strdup failed to fill nodes argv", EXIT_FAILURE);
		}
		advance_token(vars);
	}
	argv[i] = NULL;
	vars->parser->node->u_data.s_command.argv = argv;
}

int	quote_is_closed(char *s, int i)
{
	if (ft_strchr(s + i + 1, s[i]))
		return (1);
	return (0);
}
