/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fschnorr <fschnorr@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 10:51:56 by vboxuser          #+#    #+#             */
/*   Updated: 2025/04/03 15:37:49 by fschnorr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include <stdio.h>
#include <string.h>

void	chdir_error(char *path)
{
	write(STDERR_FILENO, "minishell: cd: ", 15);
	write(STDERR_FILENO, path, ft_strlen(path));
	write(STDERR_FILENO, ": ", 2);
	write(STDERR_FILENO, strerror(errno), ft_strlen(strerror(errno)));
	write(STDERR_FILENO, "\n", 1);
	return ;
}

/* int	build_path(char *input, char *path, char *home)
{
	if (*input == '/') // absolute path
		ft_strlcpy(path, input, ft_strlen(input) + 1);
	else if (*input == '~') // home path
	{
		ft_strlcpy(path, home, ft_strlen(home) + 1);
		input++;
		ft_strlcat(path, input, ft_strlen(path) + ft_strlen(input) + 1);
	}
	else //relative path
	{
		if (!getcwd(path, PATH_MAX))
		{
			chdir_error(input);
			return (-1);
		}
		printf("path: %s\n", path);
		if (ft_strncmp(input, "..", 2) == 0) // path beginning with ../
		{
			ft_bzero(ft_strrchr(path, '/'), 1);
			input = input + 2;
		}
		else if (ft_strncmp(input, "./", 2) == 0) // path beginning with ./
			input = input + 2;
		ft_strlcat(path, "/", ft_strlen(path) + 2);
		ft_strlcat(path, input, ft_strlen(path) + ft_strlen(input) + 1);
	}
	return (0);
} */

int	run_cd(t_vars *vars)
{
	int		argc;

	argc = 0;
	while (vars->ast->u_data.s_command.argv[argc] != NULL)
		argc++;
	if (argc == 1)
	{
		build_path("~", vars->path, vars->prompt->home);
		chdir(vars->prompt->home); // does it need to be error pretected?
		update_prompt(vars, vars->path);
		return (0);
	}
	else if (argc > 2)
	{
		write(STDERR_FILENO, "minishell: cd: too many arguments\n", 34); // eleganter in eine errorfunktion integrieren?
		return (-1);
	}
	if (build_path(vars->ast->u_data.s_command.argv[1], vars->path, vars->prompt->home) == -1)
	{
		chdir_error(vars->ast->u_data.s_command.argv[1]);
		return (-1);
	}
	if (chdir(vars->path) == -1)
		{
			chdir_error(vars->ast->u_data.s_command.argv[1]);
			return (-1);
		}
	update_prompt(vars, vars->path);
	return (0);
}
