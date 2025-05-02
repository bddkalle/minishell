#include "../../include/minishell.h"

int		count_nodes(t_envp *envp_ll)
{
	int	count;

	count = 0;
	while (envp_ll)
	{
		count++;
		envp_ll = envp_ll->next;
	}
	return (count);
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

void	replace_value(t_envp *old, t_envp *new)
{
	free(old->value);
	old->value = new->value;
	free(new->var);
	free(new);
}

void	add_or_replace_envp(t_vars *vars, t_envp *new_envp_node)
{
	t_envp	*temp;
	int		var_exists;

	var_exists = 0;
	temp = vars->envp_ll;
	while(temp->next)
	{
		if (ft_strcmp(temp->var, new_envp_node->var) == 0)
		{
			var_exists = 1;
			break;
		}
		temp = temp->next;
	}
	if (var_exists)
		replace_value(temp, new_envp_node);
	else
	{
		new_envp_node->next = NULL;
		temp->next = new_envp_node;
	}
}

t_envp	*create_envp_node(char *varvalue)
{
	t_envp	*envp_node;
	char	*equal;

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
		envp_node->val_set = 1;
	}
	else
	{
		envp_node->var = ft_strdup(varvalue);
		envp_node->value = ft_strdup("");
		envp_node->val_set = 0;
	}
	envp_node->exported = 1;
	return (envp_node);
}
