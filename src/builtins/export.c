#include "../../include/minishell.h"

int		export_error(char *identifier, char *errmsg, int errornumber)
{
	write(STDERR_FILENO, "minishell: ", 11);
	write(STDERR_FILENO, "export: ", 8);
	write(STDERR_FILENO, identifier, ft_strlen(identifier));
	write(STDERR_FILENO, ": ", 2);
	write(STDERR_FILENO, errmsg, ft_strlen(errmsg));
	write(STDERR_FILENO, "\n", 1);
	return (errornumber);
}

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

int	is_valid_identifier(char *identifier)
{
	while (*identifier)
	{
		if (!is_valid_name(*identifier) && !ft_isdigit(*identifier))
			return (0);
		identifier++;
	}
	return (1);
}

int	parse_export_command(t_vars *vars, char **argv)
{
	int	i;
	t_envp	*new_envp_node;

	i = 1;
	while (argv[i])
	{
		if (!is_valid_name(argv[i][0]))
			return (1);
		new_envp_node = create_envp_node(argv[i]);
		if (!is_valid_identifier(new_envp_node->var))
			return (i);
		if (!new_envp_node)
			fatal_error(vars, "malloc: Cannot allocate memory");
		add_or_replace_envp(vars, new_envp_node);
		i++;
	}
	return (0);
}

int	run_export(t_vars *vars, char **argv, int fd)
{
	char	**envp;
	int		invalid;

	invalid = parse_export_command(vars, argv);
	if (invalid != 0)
		return (export_error(argv[invalid], "not a valid identifier", 1));
	if (!argv[1])
	{
		envp = envp_to_array(vars->envp_ll);
		sort_envp(envp);
		print_export(fd, envp);
		free_envp_array(envp);
	}
	//update prompt??
	return (0);
}
