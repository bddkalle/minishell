#include "../../include/minishell.h"

void	print_export(int fd, char **envp)
{
	while (*envp)
	{
		write(fd, "declare -x ", 11);
		write(fd, *envp, ft_strlen(*envp));
		write(fd, "\n", 1);
		envp++;
	}
}

int	parse_export_command(t_vars *vars, char **argv)
{
	int	i;
	t_envp	*new_envp_node;

	i = 1;
	while (argv[i])
	{
		if (!is_valid_name(argv[i][0]))
			return (execution_error("export", strerror(errno)));
		new_envp_node = create_envp_node(argv[i]);
		if (!new_envp_node)
			return (execution_error("export", strerror(errno)));
		add_or_replace_envp(vars, new_envp_node);
		i++;
	}
	return (0);
}

int	run_export(t_vars *vars, char **argv, int fd)
{
	char	**envp;

	parse_export_command(vars, argv);
	if (!argv[1])
	{
		envp = envp_to_array(vars->envp_ll);
		sort_envp(envp);
		print_export(fd, envp);
		free_envp_array(envp);
	}
	return (0);
}
