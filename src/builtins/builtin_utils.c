/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vboxuser <vboxuser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 09:57:39 by vboxuser          #+#    #+#             */
/*   Updated: 2025/05/04 12:50:15 by vboxuser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*get_home(t_vars *vars)
{
	char	*home;

	home = _getenv(vars, "HOME");
	if (!home)
		home = getenv("HOME");
	return (home);
}

void	update_oldpwd(t_vars *vars)
{
	t_envp	*temp;
	char	*old_pwd;

	ft_bzero(vars->oldpwd, PATH_MAX);
	ft_strlcpy(vars->oldpwd, vars->pwd, ft_strlen(vars->pwd) + 1);
	temp = vars->envp_ll;
	while (temp)
	{
		if (ft_strcmp(temp->var, "OLDPWD") == 0)
			break ;
		temp = temp->next;
	}
	if (temp)
	{
		old_pwd = ft_strdup(vars->pwd);
		if (!old_pwd)
			fatal_error(vars, "malloc: Cannot allocate memory");
		free(temp->value);
		temp->value = old_pwd;
	}
}

void	update_pwd(t_vars *vars)
{
	t_envp	*temp;
	char	pwd[PATH_MAX];

	getcwd(pwd, (size_t)PATH_MAX);
	ft_bzero(vars->pwd, PATH_MAX);
	ft_strlcpy(vars->pwd, pwd, ft_strlen(pwd) + 1);
	temp = vars->envp_ll;
	while (temp)
	{
		if (ft_strcmp(temp->var, "PWD") == 0)
			break ;
		temp = temp->next;
	}
	if (temp)
	{
		free(temp->value);
		temp->value = ft_strdup(pwd);
	}
}
