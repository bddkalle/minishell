/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_utils3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vboxuser <vboxuser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 15:03:14 by cdahne            #+#    #+#             */
/*   Updated: 2025/05/04 21:16:37 by vboxuser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	to_array_quoted(t_vars *vars, char **envp)
{
	int		i;
	t_envp	*temp;

	temp = vars->envp_ll;
	i = 0;
	while (temp)
	{
		envp[i] = malloc(ft_strlen(temp->var) + ft_strlen(temp->value) + 4);
		if (!envp[i])
		{
			free_envp_array(envp);
			fatal_error(vars, "malloc: Cannot allocate memory");
		}
		ft_strlcpy(envp[i], temp->var, ft_strlen(temp->var) + 1);
		if (temp->val_set)
		{
			ft_strlcat(envp[i], "=", ft_strlen(envp[i]) + 2);
			ft_strlcat(envp[i], "\"", ft_strlen(envp[i]) + 2);
			ft_strlcat(envp[i], temp->value, \
				ft_strlen(envp[i]) + ft_strlen(temp->value) + 1);
			ft_strlcat(envp[i], "\"", ft_strlen(envp[i]) + 2);
		}
		i++;
		temp = temp->next;
	}
}

int	to_array_unquoted(t_vars *vars, char **envp)
{
	int		i;
	t_envp	*temp;

	temp = vars->envp_ll;
	i = 0;
	while (temp)
	{
		envp[i] = malloc(ft_strlen(temp->var) + ft_strlen(temp->value) + 2);
		if (!envp[i])
		{
			free_envp_array(envp);
			fatal_error(vars, "malloc: Cannot allocate memory");
		}
		ft_strlcpy(envp[i], temp->var, ft_strlen(temp->var) + 1);
		if (temp->val_set)
		{
			ft_strlcat(envp[i], "=", ft_strlen(envp[i]) + 2);
			ft_strlcat(envp[i], temp->value, \
				ft_strlen(envp[i]) + ft_strlen(temp->value) + 1);
		}
		i++;
		temp = temp->next;
	}
	return (0);
}

char	**envp_to_array(t_vars *vars, int vals_quoted)
{
	char	**envp;
	int		count;

	count = count_nodes(vars->envp_ll);
	envp = malloc((count + 1) * sizeof(char *));
	if (!envp)
		fatal_error(vars, "malloc: Cannot allocate memory");
	if (vals_quoted)
		to_array_quoted(vars, envp);
	else
		to_array_unquoted(vars, envp);
	envp[count] = NULL;
	return (envp);
}
