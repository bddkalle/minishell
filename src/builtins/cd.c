/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vboxuser <vboxuser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 10:51:56 by vboxuser          #+#    #+#             */
/*   Updated: 2025/03/13 17:47:02 by vboxuser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
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

int	run_cd(t_vars *vars)
{
	char	path[PATH_MAX];
	//char	**argv;
	int		argc;
	char	*tmp;

	argc = 0;
	//argv = vars->ast->u_data.s_command.argv;
	//tmp = vars->ast->u_data.s_command.argv + 1;
	while (*vars->ast->u_data.s_command.argv)
	{
		argc++;
		vars->ast->u_data.s_command.argv++;
	}
	if (argc == 1)
	{
		chdir(vars->prompt->home); // does it need to be error pretected?
		return (0);
	}
	else if (argc > 2)
	{
		write(STDERR_FILENO, "minishell: cd: too many arguments\n", 34); // eleganter in eine errorfunktion integrieren?
		return (-1);
	}
	tmp = *(vars->ast->u_data.s_command.argv);
	if (*tmp == '/')
		ft_strlcpy(path, tmp, ft_strlen(tmp) + 1);
	else if (*tmp == '~')
	{
		ft_strlcpy(path, vars->prompt->home, ft_strlen(vars->prompt->home) + 1);
		tmp++;
		if (*tmp)
			ft_strlcat(path, tmp, ft_strlen(tmp));
	}
	else
	{
		if (!getcwd(path, PATH_MAX))
		{
			chdir_error(tmp);
			return (-1);
		}
		ft_strlcat(path, tmp, ft_strlen(tmp) + 1);
	}
	if (chdir(path) == -1)
		{
			chdir_error(tmp);
			return (-1);
		}
	return (0);
}
