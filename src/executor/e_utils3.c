/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e_utils3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdahne <cdahne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 17:52:24 by cdahne            #+#    #+#             */
/*   Updated: 2025/04/30 17:55:09 by cdahne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	free_close_tempfile(t_tempfile *tempfile)
{
	close(tempfile->fd);
	free(tempfile->name);
	free(tempfile);
}

t_tempfile	*create_tempfile(t_vars *vars)
{
	t_tempfile	*tempfile;

	tempfile = malloc(sizeof(t_tempfile));
	tempfile->name = ft_strdup("heredoc_temp");
	if (!tempfile)
	{
		free(tempfile);
		fatal_error(vars, "out of memory");
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
