/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vboxuser <vboxuser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 10:51:56 by vboxuser          #+#    #+#             */
/*   Updated: 2025/04/28 19:42:33 by vboxuser         ###   ########.fr       */
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

void	update_oldpwd(t_vars *vars)
{
	t_envp	*temp;
	char	*old_pwd;

	temp = vars->envp_ll;
	while (temp)
	{
		if (ft_strcmp(temp->var, "OLDPWD") == 0)
			break;
		temp = temp->next;
	}
	if (temp)
	{
		old_pwd = _getenv(vars, "PWD");
		if (!old_pwd)
			return;
		free(temp->value);
		temp->value = ft_strdup(old_pwd);
	}
	return;
}

void	update_pwd(t_vars *vars)
{
	t_envp	*temp;
	char	pwd[PATH_MAX];

	temp = vars->envp_ll;
	while (temp)
	{
		if (ft_strcmp(temp->var, "PWD") == 0)
			break;
		temp = temp->next;
	}
	if (temp)
	{
		getcwd(pwd, (size_t)PATH_MAX);
		free(temp->value);
		temp->value = ft_strdup(pwd);
	}
}

int	build_pwd_path(t_vars *vars, char *input, char *pwd_path)
{
	if (*input == '/') // absolute path
		ft_strlcpy(pwd_path, input, ft_strlen(input) + 1);
	else if (*input == '~') // home path
	{
		ft_strlcpy(pwd_path, _getenv(vars, "HOME"), ft_strlen(_getenv(vars, "HOME")) + 1);
		input++;
		ft_strlcat(pwd_path, input, ft_strlen(pwd_path) + ft_strlen(input) + 1);
	}
	else //relative path
	{
		if (!getcwd(pwd_path, PATH_MAX))
			return (chdir_error(input, errno));
		if (ft_strncmp(input, "..", 2) == 0) // path beginning with ../
		{
			ft_bzero(ft_strrchr(pwd_path, '/'), 1);
			input = input + 2;
		}
		else if (ft_strncmp(input, "./", 2) == 0) // path beginning with ./
			input = input + 2;
		if (ft_strcmp("/", pwd_path) != 0)
			ft_strlcat(pwd_path, "/", ft_strlen(pwd_path) + 2);
		ft_strlcat(pwd_path, input, ft_strlen(pwd_path) + ft_strlen(input) + 1);
	}
	return (0);
}

int	run_cd(t_vars *vars, char **argv)
{
	int		argc;
	char	pwd_path[PATH_MAX];

	argc = 0;
	while (argv[argc] != NULL)
		argc++;
	if (argc == 1)
	{
		if (chdir(_getenv(vars, "HOME")) == -1)
			return (execution_error("cd", strerror(errno), 1));
	}
	else if (argc == 2)
	{
		if (build_pwd_path(vars, argv[1], pwd_path) == -1)
			return (chdir_error(argv[1], 1));
		if (chdir(pwd_path) == -1)
			return (chdir_error(argv[1], 1));
	}
	else
		return (execution_error("cd", "too many arguments\n", 1));
	update_oldpwd(vars);
	update_pwd(vars);
	update_prompt(vars, _getenv(vars, "PWD"));
	return (0);
}
