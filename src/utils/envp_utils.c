#include "../../include/minishell.h"
#include <stdlib.h>

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

void	add_envp(t_envp *envp, char *varvalue)
{
	t_envp *new;

	new = malloc(sizeof(t_envp));
	split_envp(new, varvalue);
	new->next = NULL;
	// new->exported = 1;
	// new->var = var;
	// new->value = value;
	while (envp->next)
		envp = envp->next;
	envp->next = new;
}

void	split_envp(t_envp *envp, char *param)
{
	char	*equal;

	equal = ft_strchr(param, '=');
	if (equal)
	{
		envp->var = malloc(sizeof(char) * (equal - param + 1));
		ft_strlcpy(envp->var, param, equal - param + 1);
		envp->value = malloc(sizeof(char) * (ft_strlen(equal + 1) + 1));
		ft_strlcpy(envp->value, equal + 1, ft_strlen(equal + 1) + 1);
		envp->exported = 1;
	}
	else
	{
		envp->var = malloc(sizeof(char) * (ft_strlen(param) + 1));
		envp->value = NULL;
		envp->exported = 1;
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
