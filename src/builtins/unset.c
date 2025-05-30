/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdahne <cdahne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 18:39:58 by cdahne            #+#    #+#             */
/*   Updated: 2025/04/30 18:40:07 by cdahne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	unset_error(char *command, char *var, char *errmsg)
{
	write(STDERR_FILENO, "minishell: ", 11);
	write(STDERR_FILENO, command, ft_strlen(command));
	write(STDERR_FILENO, ": ", 2);
	write(STDERR_FILENO, var, ft_strlen(var));
	write(STDERR_FILENO, ": ", 2);
	write(STDERR_FILENO, errmsg, ft_strlen(errmsg));
	return (-1);
}

void	delete_envp_node(t_vars *vars, char *var)
{
	t_envp	*temp;
	t_envp	*prev;

	temp = vars->envp_ll;
	prev = NULL;
	while (temp)
	{
		if (ft_strcmp(temp->var, var) == 0)
		{
			if (!prev)
				vars->envp_ll = temp->next;
			else
				prev->next = temp->next;
			free(temp->var);
			free(temp->value);
			free(temp);
			break ;
		}
		prev = temp;
		temp = temp->next;
	}
}

int	run_unset(t_vars *vars, char **argv)
{
	int	i;

	i = 1;
	while (argv[i])
	{
		delete_envp_node(vars, argv[i]);
		if (ft_strcmp(argv[i], "PWD") == 0)
			ft_bzero(vars->pwd, PATH_MAX);
		if (ft_strcmp(argv[i], "OLDPWD") == 0)
			ft_bzero(vars->oldpwd, PATH_MAX);
		i++;
	}
	update_prompt(vars);
	return (0);
}
