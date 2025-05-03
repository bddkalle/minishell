/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e_utils2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdahne <cdahne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 18:38:15 by cdahne            #+#    #+#             */
/*   Updated: 2025/04/30 18:39:29 by cdahne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	free_env_paths(char **env_paths)
{
	int	i;

	i = 0;
	while (env_paths[i])
	{
		free(env_paths[i]);
		i++;
	}
	free(env_paths);
	return ;
}

int	search_env_path(t_vars *vars, char *command)
{
	char	*env_p;
	char	**env_paths;
	int		i;

	env_p = _getenv(vars, "PATH");
	if (!env_p)
		return (-1);
	env_paths = ft_split(env_p, ':');
	if (!env_paths)
		fatal_error(vars, "out of memory");
	i = 0;
	while (env_paths[i])
	{
		ft_strlcpy(vars->pathname, env_paths[i], ft_strlen(env_paths[i]) + 1);
		ft_strlcat(vars->pathname, "/", ft_strlen(vars->pathname) + 2);
		ft_strlcat(vars->pathname, command, \
			ft_strlen(vars->pathname) + ft_strlen(command) + 1);
		if (access(vars->pathname, F_OK) == 0)
			break ;
		i++;
		ft_bzero(vars->pathname, PATH_MAX);
	}
	free_env_paths(env_paths);
	return (0);
}
