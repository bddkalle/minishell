/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vboxuser <vboxuser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 09:57:39 by vboxuser          #+#    #+#             */
/*   Updated: 2025/05/03 09:57:39 by vboxuser         ###   ########.fr       */
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
			return ;
		//that enougherror protection?
		free(temp->value);
		temp->value = old_pwd;
	}
	return ;
}

void	update_pwd(t_vars *vars)
{
	t_envp	*temp;
	char	pwd[PATH_MAX];

	temp = vars->envp_ll;
	while (temp)
	{
		if (ft_strcmp(temp->var, "PWD") == 0)
			break ;
		temp = temp->next;
	}
	if (temp)
	{
		getcwd(pwd, (size_t)PATH_MAX);
		free(temp->value);
		temp->value = ft_strdup(pwd);
		ft_strlcpy(vars->pwd, pwd, PATH_MAX);
	}
}
