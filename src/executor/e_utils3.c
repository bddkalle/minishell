/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e_utils3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vboxuser <vboxuser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 17:52:24 by cdahne            #+#    #+#             */
/*   Updated: 2025/05/03 23:21:32 by vboxuser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include <linux/limits.h>
#include <string.h>
#include <unistd.h>

void	free_close_tempfile(t_tempfile *tempfile)
{
	close(tempfile->fd);
	free(tempfile->name);
	free(tempfile);
}

char	*unique_filename(t_vars *vars)
{
	int		i;
	char	*suffix;
	char	filename[PATH_MAX];
	char	*ret;

	i = 0;
	while (i < 100)
	{
		ft_strlcpy(filename, "/tmp/heredoc_temp_", 19);
		suffix = ft_itoa(i);
		ft_strlcat(filename, suffix, 47 + ft_strlen(suffix) + 1);
		free(suffix);
		if (access(filename, F_OK) == -1)
			break;
		i++;
	}
	if (i == 100)
		return (NULL);
	ret = ft_strdup(filename);
	if (!ret)
		fatal_error(vars, "out of memory");
	return (ret);
}

t_tempfile	*create_tempfile(t_vars *vars)
{
	t_tempfile	*tempfile;

	tempfile = malloc(sizeof(t_tempfile));
	if (!tempfile)
		fatal_error(vars, "out of memory");
	tempfile->name = unique_filename(vars);
	if (!tempfile->name)
	{
		free(tempfile);
		fatal_error(vars, "could not create temporary file");
	}
	tempfile->fd = open(tempfile->name, O_CREAT | O_EXCL | O_WRONLY, 0600);
	if (tempfile->fd == -1)
	{
		execution_error(tempfile->name, strerror(errno), -1);
		free(tempfile->name);
		free(tempfile);
		return (NULL);
	}
	return (tempfile);
}
