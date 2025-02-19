/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fschnorr <fschnorr@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 14:40:30 by fschnorr          #+#    #+#             */
/*   Updated: 2025/02/19 16:27:46 by fschnorr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	error_exit(t_vars *vars, char *s, int exit_code)
{
	if (errno == 0)
	{
		write(2, "Error: ", 7);
		write(2, s, ft_strlen(s));
		write(2, "\n", 1);
	}
	else
	 	perror(s);
 	free_all(vars);
	exit (exit_code);
}

void	error_main(char *s, char **argv)
{
	int	i;
	
	write(2, "Error: ", 7);
	write(2, s, ft_strlen(s));
	i = 0;
	while (argv[++i])
	{
		write(2, argv[i], ft_strlen(argv[i]));
		if (argv[i + 1])
			write(2, " ", 1);
	}
	write(2, "\n", 1);
}