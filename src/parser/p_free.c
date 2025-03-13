/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_free.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fschnorr <fschnorr@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 15:13:48 by fschnorr          #+#    #+#             */
/*   Updated: 2025/03/12 17:04:57 by fschnorr         ###   ########.fr       */
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
	}
	//free_null((void **)&vars->ast);
	else if (vars->parser->node && vars->parser->node->type == AST_COMMAND)
	{
		i = 0;
		while (vars->parser->node->u_data.s_command.argv[i])
			free_null((void **)&vars->parser->node->u_data.s_command.argv[i++]);
		free_null((void **)&vars->parser->node->u_data.s_command.argv);
		free_null((void **)&vars->parser->node);
	}
	
}
