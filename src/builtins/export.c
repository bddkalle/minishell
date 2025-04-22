#include "../../include/minishell.h"

typedef struct	s_envp
{
	char	*param;
	char	*value;
	struct s_envp	*next;
}	t_envp;

void	free_envp(t_envp *envp)
{
	t_envp	*temp;

	while (envp)
	{
		temp = envp->next;
		free(envp->param);
		free(envp->value);
		free(envp);
		envp = temp;
	}
}

void	print_envp(int fd, t_envp *envp)
{
	while(envp)
	{
		write(fd, "declare -x ", 11);
		write(fd, envp->param, ft_strlen(envp->param));
		write(fd, "=\"", 2);
		write(fd, envp->value, ft_strlen(envp->value));
		write(fd, "\"\n", 2);
		envp = envp->next;
	}
}

void	sort_envp(t_envp *envp)
{

}

void	split_envp(t_envp *envp, char *param)
{
	char	*equal;

	equal = ft_strchr(param, '=');
	if (equal)
	{
		envp->param = malloc(sizeof(char) * (equal - param + 1));
		ft_strlcpy(envp->param, param, equal - param + 1);
		envp->value = malloc(sizeof(char) * ft_strlen(equal + 1) + 1);
		ft_strlcpy(envp->value, equal + 1, ft_strlen(equal + 1) + 1);
	}
	else
	{
		envp->param = malloc(sizeof(char) * (equal - param + 1));

	}
}

t_envp	*init_envp(char **param)
{
	t_envp	*envp;
	t_envp	*temp;
	t_envp	*last;
	int	count;

	count = 0;
	envp = NULL;
	while (param[count])
	{
		temp = malloc(sizeof(t_envp));
		if (!temp)
		{
			execution_error("export", strerror(errno));
			return (NULL);
		}
		split_envp(temp, param[count]);
		temp->next = NULL;
		if (!envp)
			envp = temp;
		else
		 	last->next = temp;
		last = temp;
		count++;
	}
	return (envp);
}

int	run_export(int fd, t_vars *vars)
{
	t_envp	*envp;

	envp = init_envp(vars->envp);
	print_envp(fd, envp);
	free_envp(envp);
	return (0);
}
