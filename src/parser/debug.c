/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fschnorr <fschnorr@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 16:18:32 by fschnorr          #+#    #+#             */
/*   Updated: 2025/03/13 16:37:43 by fschnorr         ###   ########.fr       */
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
		printf("type: %d\n", tmp->type);
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
	}
}
