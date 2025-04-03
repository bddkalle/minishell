#include "../../include/minishell.h"
#include <stdlib.h>

void	executable_error(char *command, char *errmsg)
{
	write(STDERR_FILENO, "minishell: ", 11);
	write(STDERR_FILENO, command, ft_strlen(command));
	write(STDERR_FILENO, ": ", 2);
	write(STDERR_FILENO, errmsg, ft_strlen(errmsg));
	write(STDERR_FILENO, "\n", 1);
	return ;
}

void	fatal_error(t_vars *vars, char *errmsg)
{
	write(STDERR_FILENO, "minishell: ", 11);
	write(STDERR_FILENO, errmsg, ft_strlen(errmsg));
	write(STDERR_FILENO, "\n", 1);
	free_all(vars);
	exit(EXIT_FAILURE);
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
	free(env_paths);
	return (0);
}

int	search_executable(t_vars *vars, char *command, char *pathname)
{
	int		found;

	//command = vars->ast->u_data.s_command.argv[0];
	if (ft_strchr(command, '/') != NULL)
		ft_strlcpy(pathname, command, ft_strlen(command) + 1);
	else
	{
		found = search_env_path(command, pathname);
		if (found == -1)
		{
			executable_error(command, "No such file or directory");
			return (-1);
		}
		else if (found == -2)
			fatal_error(vars, "cannot allocate memory");
	}
	if (access(pathname, X_OK) != 0)
	{
		executable_error(command, strerror(errno));
		return (-1);
	}
	return (0);
}

int	run_executable(t_vars *vars, struct s_command *curr_command_node)
{
	char	pathname[PATH_MAX];
	pid_t	pid;
	int		status;

	if (search_executable(vars, curr_command_node->argv[0], pathname) != 0)
		return (-1);
	pid = fork();
	if (pid == -1)
	{
		executable_error(curr_command_node->argv[0], strerror(errno));
		return (-1);
	}
	if (pid == 0)
	{
		// if (vars->ast->u_data.s_command.redirs != NULL)
		// {
		// 	fd = open(vars->ast->u_data.s_command.redirs->target);
		// 	if (fd == -1)
		// 		return (-1);
		// 	if (vars->ast->u_data.s_command.redirs->type == REDIR_OUTPUT)
		// 	{
		// 		dup2(fd, STDOUT_FILENO);
		// 		close(fd);
		// 	}
		// }
		execve(pathname, curr_command_node->argv, vars->envp);
		executable_error(curr_command_node->argv[0], strerror(errno));
		return (EXIT_FAILURE);
	}
	else
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
		{
			ft_printf("Child process terminated normally with exit code %d.\n", WEXITSTATUS(status));
			return (WEXITSTATUS(status));
		}
		else if (WIFSIGNALED(status))
		{
			ft_printf("Child process was terminated by signal %d.\n", WTERMSIG(status));
			return (WIFSIGNALED(status));
		}
		else
		{
			ft_printf("Child process terminated abnormaly.\n");
			return (WIFEXITED(status));
		}
	}
	return (-1);
}
