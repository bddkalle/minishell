/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vboxuser <vboxuser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 11:54:32 by vboxuser          #+#    #+#             */
/*   Updated: 2025/05/04 21:12:05 by vboxuser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_envp	*find_node(t_vars *vars, char *var)
{
	t_envp	*temp;

	temp = vars->envp_ll;
	while (temp)
	{
		if (ft_strcmp(temp->var, var) == 0)
			break ;
		temp = temp->next;
	}
	return (temp);
}

void	free_envp(t_envp *envp)
{
	t_envp	*temp;

	while (envp)
	{
		temp = envp->next;
		free(envp->var);
		free(envp->value);
		free(envp);
		envp = temp;
	}
}

void	free_envp_array(char **envp)
{
	char	**temp;

	temp = envp;
	while (*temp)
		free(*temp++);
	free(envp);
}

void	swap_envp(char **s1, char **s2)
{
	char	*temp;

	temp = *s1;
	*s1 = *s2;
	*s2 = temp;
}

void	sort_envp(char **envp)
{
	int	sorted;
	int	i;

	i = 0;
	sorted = 0;
	while (!sorted)
	{
		sorted = 1;
		i = 0;
		while (envp[i + 1])
		{
			if (ft_strcmp(envp[i], envp[i + 1]) > 0)
			{
				swap_envp(&envp[i], &envp[i + 1]);
				sorted = 0;
			}
			i++;
		}
	}
}
