/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vboxuser <vboxuser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 10:51:52 by vboxuser          #+#    #+#             */
/*   Updated: 2025/05/04 20:53:41 by vboxuser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	run_echo(int fd, char **argv)
{
	int		linebreak;
	char	*s;

	linebreak = 1;
	while (*++argv && ft_strcmp(*argv, "-n") == 0)
		linebreak = 0;
	while (*argv)
	{
		s = *argv;
		while (*s)
			if (write (fd, s++, 1) == -1)
				return (execution_error("echo", strerror(errno), 1));
		argv++;
		if (*argv)
			write (fd, " ", 1);
	}
	if (linebreak)
		write(fd, "\n", 1);
	return (0);
}
