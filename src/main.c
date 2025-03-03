/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fschnorr <fschnorr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 14:20:17 by fschnorr          #+#    #+#             */
/*   Updated: 2025/03/03 12:54:31 by fschnorr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include <readline/history.h>

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
			printf("%s\n", tmp->value);
			tmp = tmp->next;
		}
		free_null(vars.line);
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