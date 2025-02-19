/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fschnorr <fschnorr@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 14:20:17 by fschnorr          #+#    #+#             */
/*   Updated: 2025/02/19 17:01:28 by fschnorr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	minishell(void)
{
	t_vars		vars;
	char		*line;
	
	init_vars(&vars);
	get_prompt(&vars);
	ft_printf("USER = %s\n", vars.prompt->user);
	ft_printf("HOSTNAME = %s\n", vars.prompt->hostname);
	ft_printf("PWD = %s\n", vars.prompt->pwd);
	ft_printf("HOME = %s\n", vars.prompt->home);
	ft_printf("CWD = %s\n", vars.prompt->cwd);
	ft_printf("PROMPT = %s\n", vars.prompt->prompt);
	/* line = NULL;
	line = readline(vars.prompt->prompt); */
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