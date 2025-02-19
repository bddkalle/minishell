/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fschnorr <fschnorr@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 14:20:17 by fschnorr          #+#    #+#             */
/*   Updated: 2025/02/19 13:08:56 by fschnorr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	minishell()
{
	t_vars		vars;
	
	init_vars(&vars);
	get_prompt(&vars);
	ft_printf("USER = %s\n", vars.prompt->user);
	ft_printf("HOSTNAME = %s\n", vars.prompt->hostname);
	ft_printf("PWD = %s\n", vars.prompt->pwd);
	ft_printf("HOME = %s\n", vars.prompt->home);
	ft_printf("CWD = %s\n", vars.prompt->cwd);
	ft_printf("PROMPT = %s\n", vars.prompt->prompt);
	free_all(&vars);
}

int	main(int argc, char **argv)
{
	if (argc == 1)
		minishell();
	else
		perror("Invalid argument count.");
	return (0);
}