#include "../../include/minishell.h"

void	print_export(int fd, t_envp *envp)
{
	while(envp)
	{
		write(fd, "declare -x ", 11);
		write(fd, envp->var, ft_strlen(envp->var));
		write(fd, "=\"", 2);
		write(fd, envp->value, ft_strlen(envp->value));
		write(fd, "\"\n", 2);
		envp = envp->next;
	}
}

// void	sort_envp(t_envp *envp)
// {

// }

int	run_export(int fd, t_vars *vars)
{
	//envp = init_envp(vars->envp);
	print_export(fd, vars->envp_ll);
	//free_envp(envp);
	return (0);
}
