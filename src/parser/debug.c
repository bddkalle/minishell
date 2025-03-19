/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fschnorr <fschnorr@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 16:18:32 by fschnorr          #+#    #+#             */
/*   Updated: 2025/03/19 16:57:13 by fschnorr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	debug_lexer(t_vars *vars)
{
	t_token	*tmp;
	int		i;

	printf("\n###################### DEBUG LEXER ######################\n");
	i = 0;
	tmp = vars->token;
	while (tmp)
	{
		printf("\n>>Token %d<<\n", i++);
		printf("value: %s - ", tmp->value);
		if (tmp->type == TOKEN_WORD)
			printf("type: TOKEN_WORD\n");
		else if (tmp->type == TOKEN_PIPE)
			printf("type: TOKEN_PIPE\n");
		else if (tmp->type == TOKEN_REDIRECT_IN)
			printf("type: TOKEN_REDIRECT_IN\n");
		else if (tmp->type == TOKEN_REDIRECT_OUT)
			printf("type: TOKEN_REDIRECT_OUT\n");
		else if (tmp->type == TOKEN_REDIRECT_APPEND)
			printf("type: TOKEN_REDIRECT_APPEND\n");
		else if (tmp->type == TOKEN_HEREDOC)
			printf("type: TOKEN_HEREDOC\n");
		else if (tmp->type == TOKEN_AND)
			printf("type: TOKEN_AND\n");
		else if (tmp->type == TOKEN_OR)
			printf("type: TOKEN_OR\n");
		else if (tmp->type == TOKEN_QUOTE)
			printf("type: TOKEN_QUOTE\n");
		else if (tmp->type == TOKEN_PARENT_LEFT)
			printf("type: TOKEN_PARENT_LEFT\n");
		else if (tmp->type == TOKEN_PARENT_RIGHT)
			printf("type: TOKEN_PARENT_RIGHT\n");
		else if (tmp->type == TOKEN_VAR)
			printf("type: TOKEN_VAR\n");
		tmp = tmp->next;
	}
}

void	debug_parser(t_vars *vars)
{
	printf("\n###################### DEBUG PARSER ######################\n");
	printf("\n>>AST NODE 0<<\n");
	for (int i = 0; vars->ast && vars->ast->u_data.s_command.argv[i]; i++)
	{
		printf("command.argv[%d] = %s\n", i, vars->ast->u_data.s_command.argv[i]);
		if (vars->ast->u_data.s_command.redirs)
		{
			int j = 0;
			for (t_redir *tmp = vars->ast->u_data.s_command.redirs; tmp; tmp = tmp->next)
			{
				if (tmp->type == REDIR_INPUT)
					printf("command.redir_node%d.type = REDIR_INPUT\n", j);
				if (tmp->type == REDIR_OUTPUT)
					printf("command.redir_node%d.type = REDIR_OUTPUT\n", j);
				if (tmp->type == REDIR_APPEND)
					printf("command.redir_node%d.type = REDIR_APPEND\n", j);
				if (tmp->type == REDIR_HEREDOC)
					printf("command.redir_node%d.type = REDIR_HEREDOC\n", j);
				printf("command.redir_node%d.target = %s\n\n", j++, tmp->target);
			}
		}
	}
}
