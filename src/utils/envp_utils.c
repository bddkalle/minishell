#include "../../include/minishell.h"
#include <string.h>

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

void	add_or_replace_envp(t_vars *vars, t_envp *envp_node)
{
	t_envp	*temp;
	int		var_exists;

	var_exists = 0;
	temp = vars->envp_ll;
	while(temp)
	{
		if (temp->var == envp_node->var)
		{
			var_exists = 1;
			break;
		}
		temp = temp->next;
	}
	if (var_exists)
	{
		free(temp->value);
		temp->value = envp_node->value;
		free(envp_node->var);
		free(envp_node);
	}
	else
		temp->next = envp_node;
}

// void	add_envp(t_envp *envp, char *varvalue)
// {
// 	t_envp *new;

// 	new = malloc(sizeof(t_envp));
// 	split_envp(new, varvalue);
// 	new->next = NULL;
// 	while (envp->next)
// 		envp = envp->next;
// 	envp->next = new;
// }

// void	split_envp(t_envp *envp, char *param)
// {
// 	char	*equal;

// 	equal = ft_strchr(param, '=');
// 	if (equal)
// 	{
// 		envp->var = malloc(sizeof(char) * (equal - param + 1));
// 		ft_strlcpy(envp->var, param, equal - param + 1);
// 		envp->value = malloc(sizeof(char) * (ft_strlen(equal + 1) + 1));
// 		ft_strlcpy(envp->value, equal + 1, ft_strlen(equal + 1) + 1);
// 		envp->exported = 1;
// 	}
// 	else
// 	{
// 		envp->var = malloc(sizeof(char) * (ft_strlen(param) + 1));
// 		envp->value = NULL;
// 		envp->exported = 1;
// 	}
// }

t_envp	*create_envp_node(t_vars *vars, char *varvalue)
{
	t_envp	*envp_node;
	char	*equal;

	(void)vars;
	envp_node = malloc(sizeof(t_envp));
	if (!envp_node)
		return (NULL);
	equal = ft_strchr(varvalue, '=');
	if (equal)
	{
		envp_node->var = malloc(sizeof(char) * (equal - varvalue + 1));
		if (!envp_node->var)
			return (NULL);
		ft_strlcpy(envp_node->var, varvalue, equal - varvalue + 1);
		envp_node->value = malloc(sizeof(char) * (ft_strlen(equal + 1) + 1));
		if (!envp_node->value)
			return (NULL);
		ft_strlcpy(envp_node->value, equal + 1, ft_strlen(equal + 1) + 1);
		envp_node->exported = 1;
	}
	else
	{
		envp_node->var = malloc(sizeof(char) * (ft_strlen(varvalue) + 1));
		envp_node->value = NULL;
		envp_node->exported = 1;
	}
	return (envp_node);
}

void	init_envp(t_vars *vars, char **param)
{
	t_envp	*envp;
	t_envp	*temp;
	t_envp	*last;
	int	count;

	count = 0;
	envp = NULL;
	while (param[count])
	{
		temp = create_envp_node(vars, param[count]);
		if (!temp)
			error_exit(vars, strerror(errno), errno); // double checl with felix
		temp->next = NULL;
		if (!envp)
			envp = temp;
		else
		 	last->next = temp;
		last = temp;
		count++;
	}
	vars->envp_ll = envp;
}

// t_envp	*init_envp(char **param)
// {
// 	t_envp	*envp;
// 	t_envp	*temp;
// 	t_envp	*last;
// 	int	count;

// 	count = 0;
// 	envp = NULL;
// 	while (param[count])
// 	{
// 		temp = malloc(sizeof(t_envp));
// 		if (!temp)
// 		{
// 			execution_error("export", strerror(errno));
// 			return (NULL);
// 		}
// 		split_envp(temp, param[count]);
// 		temp->next = NULL;
// 		if (!envp)
// 			envp = temp;
// 		else
// 		 	last->next = temp;
// 		last = temp;
// 		count++;
// 	}
// 	return (envp);
// }
