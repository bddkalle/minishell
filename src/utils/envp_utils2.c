/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vboxuser <vboxuser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 15:03:14 by cdahne            #+#    #+#             */
/*   Updated: 2025/05/02 19:47:25 by vboxuser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	**envp_to_array(t_envp *envp_ll)
{
	char	**envp;
	int		count;
	int		i;

	i = 0;
	count = count_nodes(envp_ll);
	envp = malloc((count + 1) * sizeof(char *));
	if (!envp)
		return (NULL); // genauer prüfen.
	while (envp_ll)
	{
		envp[i] = malloc(ft_strlen(envp_ll->var) + ft_strlen(envp_ll->value) + 2);
		if (!envp[i])
			return (NULL); // ebenfalls genauer prüfen.
		ft_strlcpy(envp[i], envp_ll->var, ft_strlen(envp_ll->var) + 1);
		if (envp_ll->val_set == 1)
		{
			ft_strlcat(envp[i], "=", ft_strlen(envp_ll->var) + 2);
			ft_strlcat(envp[i], envp_ll->value, ft_strlen(envp[i]) + ft_strlen(envp_ll->value) + 1);
		}
		i++;
		envp_ll = envp_ll->next;
	}
	envp[count] = NULL;
	return (envp);
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
	char *temp;

	temp = *s1;
	*s1 = *s2;
	*s2 = temp;
}

void	sort_envp(char **envp)
{
	int	sorted;
	int i;

	i = 0;
	sorted = 0;
	while(!sorted)
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
