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

int	search_env_path(t_vars *vars, char *command, char *pathname)
{
	char	*env_p;
	char	**env_paths;
	int		i;

	env_p = _getenv(vars, "PATH");
	if (!env_p)
		return (-1);
	//env_paths = ft_split(env_p, ':');
	env_paths = NULL;
	if (!env_paths)
		return (-2);
	i = 0;
	while (env_paths[i])
	{
		ft_strlcpy(pathname, env_paths[i], ft_strlen(env_paths[i]) + 1);
		ft_strlcat(pathname, "/", ft_strlen(pathname) + 2);
		ft_strlcat(pathname, command, ft_strlen(pathname) + ft_strlen(command) + 1);
		if (access(pathname, F_OK) == 0)
			break;
		i++;
		ft_bzero(pathname, PATH_MAX);
	}
	free_env_paths(env_paths);
	return (0);
}
