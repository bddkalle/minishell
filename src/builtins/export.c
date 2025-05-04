/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vboxuser <vboxuser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 18:40:19 by cdahne            #+#    #+#             */
/*   Updated: 2025/05/04 09:54:58 by vboxuser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	export_error(char *identifier, char *errmsg, int errornumber)
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

void	export_append(t_vars *vars, t_envp *envp_node, char *varvalue)
{
	char	*plus;
	char	*join;
	t_envp	*tempenvp;
	char	*noplus;

	plus = ft_strchr(envp_node->var, '+');
	if (plus && *(plus + 1) == '\0' && ft_strchr(varvalue, '='))
	{
		noplus = ft_substr(envp_node->var, 0, plus - envp_node->var);
		if (!noplus)
			fatal_error(vars, "malloc: Cannot allocate memory");
		free(envp_node->var);
		envp_node->var = noplus;
		tempenvp = find_node(vars, envp_node->var);
		if (tempenvp)
		{
			join = ft_strjoin(tempenvp->value, envp_node->value);
			if (!join)
				fatal_error(vars, "malloc: Cannot allocate memory");
			free(envp_node->value);
			envp_node->value = join;
		}
	}
}

int	parse_export_command(t_vars *vars, char **argv)
{
	int		i;
	t_envp	*new_envp_node;
	int		exit_code;

	exit_code = 0;
	i = 1;
	while (argv[i])
	{
		new_envp_node = create_envp_node(argv[i]);
		if (!new_envp_node)
			fatal_error(vars, "malloc: Cannot allocate memory");
		export_append(vars, new_envp_node, argv[i]);
		if (!is_valid_name(argv[i][0]) || !is_valid_identifier(new_envp_node->var))
		{
			free(new_envp_node->var);
			free(new_envp_node->value);
			free(new_envp_node);
			exit_code = execution_error(argv[i], "not a valid identifier", 1);
			i++;
			continue;
		}
		add_or_replace_envp(vars, new_envp_node);
		i++;
	}
	return (exit_code);
}

int	run_export(t_vars *vars, char **argv, int fd)
{
	char	**envp;
	int		invalid;

	invalid = parse_export_command(vars, argv);
	if (invalid != 0)
		return (invalid);
	if (!argv[1])
	{
		envp = envp_to_array(vars, 1);
		sort_envp(envp);
		print_export(fd, envp);
		free_envp_array(envp);
	}
	update_prompt(vars);
	return (0);
}
