/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vboxuser <vboxuser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 10:51:56 by vboxuser          #+#    #+#             */
/*   Updated: 2025/03/13 11:02:08 by vboxuser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include <string.h>
#include <unistd.h>

void	chdir_error(char *path)
{
	write(STDERR_FILENO, "minishell: cd: ", 15);
	write(STDERR_FILENO, path, ft_strlen(path));
	write(STDERR_FILENO, ": ", 2);
	write(STDERR_FILENO, strerror(errno), ft_strlen(strerror(errno)));
	write(STDERR_FILENO, "\n", 1);
	// error_msg = ft_strjoin("minishell: cd:", *path);
	// perror(error_msg);
	// free(error_msg);
	return ;
}

int	run_cd(int fd, char **argv)
{
	(void)fd;
	if (*(argv + 2) != NULL)
		write(STDERR_FILENO, "minishell: cd: too many arguments", 33); // ungetestet. zuerst parser und executor verbinden
	argv++;
	if (**argv == '/')
	{
		if (chdir(*argv) == -1)
		{
			chdir_error(*argv);
			return (-1);
		}
	}
	return (0);
}
