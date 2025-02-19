/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fschnorr <fschnorr@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 16:44:49 by fschnorr          #+#    #+#             */
/*   Updated: 2025/02/19 14:14:10 by fschnorr         ###   ########.fr       */
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

void	get_prompt(t_vars *vars)
{
	vars->prompt->user = getenv("USER");
	if (!vars->prompt->user)
		error_exit(vars, "Could not get $USER", EXIT_FAILURE);
	vars->prompt->hostname = getenv("HOSTNAME");
	if (!vars->prompt->hostname)
		vars->prompt->hostname = "NO_HOSTNAME_IN_ENV"; // check if HOSTNAME is set in env on campus, if! -> trello/waiting prompt
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
	build_prompt(vars, "$");
}