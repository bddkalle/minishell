/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vboxuser <vboxuser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 10:51:42 by vboxuser          #+#    #+#             */
/*   Updated: 2025/03/13 15:44:16 by vboxuser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include <linux/limits.h>

int	run_pwd(int fd, char **argv)
{
	char	*pwd;
	//char	*buf;
	char	buf[PATH_MAX];

	(void)argv;
	//buf = (char *)malloc((size_t)PATH_MAX); //error protection??
	//if (!buf)
	//	return (-1); // ...
	pwd = getcwd(buf, (size_t)PATH_MAX);
	if (!pwd)
	{
		write(STDERR_FILENO, "minishell: pwd: ", 16);
		write(STDERR_FILENO, strerror(errno), ft_strlen(strerror(errno)));
		write(STDERR_FILENO, "\n", 1);
		return (-1);
	}
	else
	{
		write(fd, pwd, ft_strlen(pwd));
		write(fd, "\n", 1);
	}
	//free(pwd);
	// pwd = getenv("PWD");
	// if (!pwd)
	// 	return (-1);
	// write (fd, pwd, ft_strlen(pwd));
	return (0);
}
