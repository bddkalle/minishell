/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vboxuser <vboxuser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 18:43:31 by cdahne            #+#    #+#             */
/*   Updated: 2025/05/04 10:59:55 by vboxuser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	exit_error(char *arg, char *errmsg)
{
	write(STDERR_FILENO, "minishell: ", 11);
	write(STDERR_FILENO, arg, ft_strlen(arg));
	write(STDERR_FILENO, ": ", 2);
	write(STDERR_FILENO, errmsg, ft_strlen(errmsg));
	write(STDERR_FILENO, "\n", 1);
}

int	string_is_numeric(char *s)
{
	while (*s && (*s == '+' || *s == '-'))
		s++;
	while (*s)
	{
		if (!ft_isdigit(*s))
			return (0);
		s++;
	}
	return (1);
}

int	run_exit_parent(t_vars *vars, char **argv, int in_fd, int out_fd)
{
	int	argc;
	int	exit_code;

	argc = 0;
	while (argv[argc])
		argc++;
	if (argc == 1)
		exit_code = 0;
	else if (argc == 2)
	{
		if (!string_is_numeric(argv[1]) || !within_long_long(argv[1]))
			exit_code = 2;
		else
			exit_code = ft_atoi(argv[1]);
	}
	else
		return (execution_error("exit", "too many arguments", 1));
	write(STDOUT_FILENO, "exit\n", 5);
	if (exit_code == 2)
		exit_error(argv[1], "numeric argument required");
	close_fds(in_fd, out_fd);
	free_all(vars);
	exit(exit_code % 256);
}

int	run_exit_child(t_vars *vars, char **argv, int in_fd, int out_fd)
{
	int	argc;
	int	exit_code;

	argc = 0;
	while (argv[argc])
		argc++;
	if (argc == 1)
		exit_code = 0;
	else if (argc == 2)
	{
		if (!string_is_numeric(argv[1]))
			exit_code = 2;
		else
			exit_code = ft_atoi(argv[1]);
	}
	else
		return (execution_error("exit", "too many arguments", 1));
	if (exit_code == 2)
		exit_error(argv[1], "numeric argument required");
	close_fds(in_fd, out_fd);
	free_all(vars);
	exit(exit_code % 256);
}
