/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vboxuser <vboxuser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 10:51:56 by vboxuser          #+#    #+#             */
/*   Updated: 2025/05/02 20:25:09 by vboxuser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	chdir_error(char *path, int errornumber)
{
	write(STDERR_FILENO, "minishell: cd: ", 15);
	write(STDERR_FILENO, path, ft_strlen(path));
	write(STDERR_FILENO, ": ", 2);
	write(STDERR_FILENO, strerror(errno), ft_strlen(strerror(errno)));
	write(STDERR_FILENO, "\n", 1);
	return (errornumber);
}

int	build_pwd_path(char *input, char *pwd_path, char *home)
{
	if (*input == '/')
		ft_strlcpy(pwd_path, input, ft_strlen(input) + 1);
	else if (*input == '~')
	{
		ft_strlcpy(pwd_path, home, \
			ft_strlen(home) + 1);
		input++;
		ft_strlcat(pwd_path, input, ft_strlen(pwd_path) + ft_strlen(input) + 1);
	}
	else
	{
		if (!getcwd(pwd_path, PATH_MAX))
			return (chdir_error(input, errno));
		if (ft_strncmp(input, "..", 2) == 0)
		{
			ft_bzero(ft_strrchr(pwd_path, '/'), 1);
			input = input + 2;
		}
		else if (ft_strncmp(input, "./", 2) == 0)
			input = input + 2;
		if (ft_strcmp("/", pwd_path) != 0)
			ft_strlcat(pwd_path, "/", ft_strlen(pwd_path) + 2);
		ft_strlcat(pwd_path, input, ft_strlen(pwd_path) + ft_strlen(input) + 1);
	}
	return (0);
}

void	update(t_vars *vars)
{
	update_oldpwd(vars);
	update_pwd(vars);
	update_prompt(vars);
}

int	run_cd(t_vars *vars, char **argv)
{
	int		argc;
	char	pwd_path[PATH_MAX];
	char	*home;

	home = get_home(vars);
	argc = 0;
	while (argv[argc] != NULL)
		argc++;
	if (argc == 1)
	{
		if (chdir(home) == -1)
			return (execution_error("cd", strerror(errno), 1));
	}
	else if (argc == 2)
	{
		if (build_pwd_path(argv[1], pwd_path, home) == -1)
			return (chdir_error(argv[1], 1));
		if (chdir(pwd_path) == -1)
			return (chdir_error(argv[1], 1));
	}
	else
		return (execution_error("cd", "too many arguments", 1));
	return (0);
}
