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

int	search_env_path(char *command, char *pathname)
{
	char	*env_p;
	char	**env_paths;
	int		i;

	env_p = getenv("PATH");
	if (!env_p)
		return (-1);
	env_paths = ft_split(env_p, ':');
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

int	search_executable(t_vars *vars, char *command, char *pathname)
{
	int		found;

	if (ft_strchr(command, '/') != NULL)
		ft_strlcpy(pathname, command, ft_strlen(command) + 1);
	else
	{
		found = search_env_path(command, pathname);
		if (found == -1)
			return (execution_error(command, "No such file or directory"));
		else if (found == -2)
			fatal_error(vars, "cannot allocate memory");
	}
	if (access(pathname, X_OK) != 0)
		return (execution_error(command, strerror(errno)));
	return (0);
}

int	run_executable(t_vars *vars, struct s_command *curr_command_node, int in_fd, int out_fd)
{
	char	pathname[PATH_MAX];
	pid_t	pid;
	int		status;

	if (search_executable(vars, curr_command_node->argv[0], pathname) != 0)
		return (-1);
	pid = fork();
	if (pid == -1)
		return (execution_error(curr_command_node->argv[0], strerror(errno)));
	if (pid == 0)
	{
		//ft_printf("calling executable %s reading from fd: %i and writing to fd: %i\n", curr_command_node->argv[0], in_fd, out_fd);
		if (out_fd != STDOUT_FILENO)
		{
			//ft_printf("dup2 of fd: %i\n", out_fd);
			dup2(out_fd, STDOUT_FILENO);
			close(out_fd);
		}
		if (in_fd != STDIN_FILENO)
		{
			//ft_printf("dup2 of fd: %i\n", in_fd);
			dup2(in_fd, STDIN_FILENO);
			close(in_fd);
		}
		execve(pathname, curr_command_node->argv, vars->envp);
		execution_error(curr_command_node->argv[0], strerror(errno));
		free_all(vars);
		exit (EXIT_FAILURE);
	}
	else
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
		{
			//ft_printf("Child process terminated normally with exit code %d.\n", WEXITSTATUS(status));
			return (WEXITSTATUS(status));
		}
		else if (WIFSIGNALED(status))
		{
			//ft_printf("Child process was terminated by signal %d.\n", WTERMSIG(status));
			return (WIFSIGNALED(status));
		}
		else
		{
			//ft_printf("Child process terminated abnormaly.\n");
			return (WIFEXITED(status));
		}
	}
	return (-1);
}
