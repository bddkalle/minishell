/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdahne <cdahne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 14:20:17 by fschnorr          #+#    #+#             */
/*   Updated: 2025/04/30 19:27:27 by cdahne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

volatile sig_atomic_t	g_received_signal = 0;

void	minishell(char **envp)
{
	t_vars		vars;

	signal_readline_setup();
	init_vars(&vars);
	get_prompt(&vars);
	init_pwd_oldpwd(&vars);
	vars.exit_status = 0;
	init_envp(&vars, envp);
	while (1)
	{
		vars.line = readline(vars.prompt->prompt);
		if (!vars.line)
		{
			printf("exit\n");
			break ;
		}
		signal_shell_setup();
		add_history(vars.line);
		lexer(&vars);
		parser(&vars);
		executor(&vars);
		free_null_readline(&vars);
		if (g_received_signal == SIGINT)
			g_received_signal = 0;
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
