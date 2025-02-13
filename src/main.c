/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fschnorr <fschnorr@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 14:20:17 by fschnorr          #+#    #+#             */
/*   Updated: 2025/02/13 16:54:08 by fschnorr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	minishell(char **envp)
{
	t_prompt	prompt;
	
	init_vars(&prompt);
	get_prompt(&prompt, envp);
	ft_printf("Correct argc.");
}

int	main(int argc, char **argv, char **envp)
{
	if (argc == 1)
	{
		minishell(envp);
		return (0);
	}
	else
		return (error("Invalid argument count."));
}