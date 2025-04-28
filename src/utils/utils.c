/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fschnorr <fschnorr@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 12:28:44 by fschnorr          #+#    #+#             */
/*   Updated: 2025/04/24 15:19:41 by fschnorr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	*_malloc(size_t size, t_vars *vars)
{
	void	*ptr;

	ptr = NULL;
	if (!size)
		return (NULL);
	ptr = malloc(size);
	if (!ptr)
		error_exit(vars, "Could not allocate memory", EXIT_FAILURE);
	return (ptr);
}

int	build_path(char *input, char *path, char *home)
{
	if (*input == '/') // absolute path
		ft_strlcpy(path, input, ft_strlen(input) + 1);
	else if (*input == '~') // home path
	{
		ft_strlcpy(path, home, ft_strlen(home) + 1);
		input++;
		ft_strlcat(path, input, ft_strlen(path) + ft_strlen(input) + 1);
	}
	else //relative path
	{
		if (!getcwd(path, PATH_MAX))
		{
			chdir_error(input);
			return (-1);
		}
		//printf("path: %s\n", path);
		if (ft_strncmp(input, "..", 2) == 0) // path beginning with ../
		{
			ft_bzero(ft_strrchr(path, '/'), 1);
			input = input + 2;
		}
		else if (ft_strncmp(input, "./", 2) == 0) // path beginning with ./
			input = input + 2;
		if (ft_strcmp("/", path) != 0)
			ft_strlcat(path, "/", ft_strlen(path) + 2);
		ft_strlcat(path, input, ft_strlen(path) + ft_strlen(input) + 1);
	}
	return (0);
}

char	*_getenv(t_vars *vars, char *var)
{
	t_envp	*tmp;

	tmp = vars->envp_ll;
	while (tmp)
	{
		if (!ft_strcmp(tmp->var, var))
			break ;
		tmp = tmp->next;
	}
	if (tmp)
		return (tmp->value);
	return (NULL);
}
