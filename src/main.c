/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vboxuser <vboxuser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 14:20:17 by fschnorr          #+#    #+#             */
/*   Updated: 2025/04/23 09:19:49 by vboxuser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

volatile sig_atomic_t	global_received_signal = 0;

void	minishell(char **envp)
{
	t_vars		vars;

	signal_shell_setup();
	init_vars(&vars);
	get_prompt(&vars);
	vars.envp = envp; // keep only one of these
	vars.envp_ll = init_envp(envp); // keep only one of these
	while (1)
	{
		vars.line = readline(vars.prompt->prompt);
		if (!vars.line || !ft_strcmp(vars.line, "exit"))
		{
			printf("exit\n");
			break ;
		}
		add_history(vars.line);
		lexer(&vars);
		parser(&vars);
 		executor(&vars);
		free_null_readline(&vars);
		if(global_received_signal == SIGINT)
			global_received_signal = 0;
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
