/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fschnorr <fschnorr@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 16:44:49 by fschnorr          #+#    #+#             */
/*   Updated: 2025/03/03 13:55:20 by fschnorr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	build_prompt(t_vars *vars, char *s)
{
	char	*tmp;

	tmp = vars->prompt->prompt;
	if (!tmp)
		vars->prompt->prompt = ft_strjoin("", s);
	else
		vars->prompt->prompt = ft_strjoin(tmp, s);
	if (tmp)
		free_null(tmp);
	if (!vars->prompt->prompt)
		error_exit(vars, "Could not join strings for prompt creation", EXIT_FAILURE);
}

void	get_hostname(t_vars *vars)
{
	char	*hostname_end;

	vars->prompt->fd_hostname = open("/etc/hostname", O_RDONLY);
	if (vars->prompt->fd_hostname == -1)
		error_exit(vars, "Could not open /etc/hostname", EXIT_FAILURE);
	vars->prompt->hostname = get_next_line(vars->prompt->fd_hostname);
	if (!vars->prompt->hostname)
		error_exit(vars, "Could not read from /etc/hostname", EXIT_FAILURE);
	if (ft_strchr(vars->prompt->hostname, '.'))
	{
		hostname_end = ft_strchr(vars->prompt->hostname, '.');
		*hostname_end = '\0';
	}
	if (vars->prompt->hostname[ft_strlen(vars->prompt->hostname) - 1] == '\n')
		vars->prompt->hostname[ft_strlen(vars->prompt->hostname) - 1] = '\0';
}

void	get_prompt(t_vars *vars)
{
	vars->prompt->user = getenv("USER");
	if (!vars->prompt->user)
		error_exit(vars, "Could not get $USER", EXIT_FAILURE);
	vars->prompt->hostname = getenv("HOSTNAME");
	if (!vars->prompt->hostname)
		get_hostname(vars);
		/* if (!vars->prompt->hostname)
			vars->prompt->hostname = "NO_HOSTNAME_IN_ENV"; // check if HOSTNAME is set in env on campus, if! -> trello/waiting prompt */
	vars->prompt->pwd = getenv("PWD");
	if (!vars->prompt->pwd)
		error_exit(vars, "Could not get $PWD", EXIT_FAILURE);
	vars->prompt->home = getenv("HOME");
	if (!vars->prompt->home)
		error_exit(vars, "Could not get $HOME", EXIT_FAILURE);
	vars->prompt->cwd = vars->prompt->pwd + (ft_strlen(vars->prompt->home));
	build_prompt(vars, vars->prompt->user);
	build_prompt(vars, "@");
	build_prompt(vars, vars->prompt->hostname);
	build_prompt(vars, ":~");
	build_prompt(vars, vars->prompt->cwd);
	build_prompt(vars, "$ ");
}