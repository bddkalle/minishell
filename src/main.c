/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fschnorr <fschnorr@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 14:20:17 by fschnorr          #+#    #+#             */
/*   Updated: 2025/03/12 16:54:51 by fschnorr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	minishell(void)
{
	t_vars		vars;
	t_token		*tmp;

	init_vars(&vars);
	get_prompt(&vars);
	while (1)
	{
		vars.line = readline(vars.prompt->prompt);
		if (!vars.line || !ft_strcmp(vars.line, "exit"))
		{
			printf("exit\n");
			break ;
		}
		add_history(vars.line);
		//do_stuff
		lexer(&vars);
		tmp = vars.token;
		while (tmp)
		{
			printf(">>Token<<\n");
			printf("value: %s - ", tmp->value);
			printf("type: %d\n", tmp->type);
			tmp = tmp->next;
		}
		parser(&vars);
		for (int i = 0; vars.ast && vars.ast->u_data.s_command.argv[i]; i++)
		{	
			printf("\n>>AST<<\n");
			printf("command.argv[%d] = %s\n", i, vars.ast->u_data.s_command.argv[i]);
		}
		free_null_readline(&vars);
	}
	free_all(&vars);
}

int	main(int argc, char **argv)
{
	if (argc == 1)
		minishell();
	else
		error_main("Invalid argument count: ", argv);
	return (0);
}