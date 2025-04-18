/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vboxuser <vboxuser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 14:20:17 by fschnorr          #+#    #+#             */
/*   Updated: 2025/04/18 15:58:23 by vboxuser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

volatile sig_atomic_t	global_received_signal = 0;

void	minishell(char **envp)
{
	t_vars		vars;

	//signal(SIGINT, sigint_handler);
	//signal(SIGQUIT, SIG_IGN);
	init_vars(&vars);
	get_prompt(&vars);
	vars.envp = envp;
	while (1)
	{
		//global_received_signal = 0;
		vars.line = readline(vars.prompt->prompt);
		if (!vars.line || !ft_strcmp(vars.line, "exit"))
		{
			printf("exit\n");
			break ;
		}
		add_history(vars.line);
		// if(global_received_signal == SIGINT)
		// {
		// 	write(STDOUT_FILENO, "\n", 1);
		// 	continue;
		// }
		// else if (global_received_signal == SIGQUIT)
		// {
		// 	write(STDOUT_FILENO, "Quit (core dumped)\n", 19);
		// 	continue;
		// }
		lexer(&vars);
		parser(&vars);
 		executor(&vars);
		free_null_readline(&vars);
	}
	free_all(&vars);
}

int	main(int argc, char **argv, char **envp)
{
	if (argc == 1)
		minishell(envp);
	else
		error_main("Invalid argument count: ", argv);
	return (0);
}
