/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vboxuser <vboxuser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 16:16:04 by cdahne            #+#    #+#             */
/*   Updated: 2025/05/03 22:04:20 by vboxuser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include <unistd.h>

int	append_redirection(char *target, int old_out_fd)
{
	int	new_out_fd;

	new_out_fd = open(target, O_WRONLY | O_CREAT | O_APPEND, 0664);
	if (old_out_fd != STDOUT_FILENO)
		close(old_out_fd);
	if (new_out_fd == -1)
		return (execution_error(target, strerror(errno), -1));
	return (new_out_fd);
}

int	output_redirection(char *target, int old_out_fd)
{
	int	new_out_fd;

	new_out_fd = open(target, O_WRONLY | O_CREAT | O_TRUNC, 0664);
	if (old_out_fd != STDOUT_FILENO)
		close(old_out_fd);
	if (new_out_fd == -1)
		return (execution_error(target, strerror(errno), -1));
	return (new_out_fd);
}

int	input_redirection(char *target, int old_in_fd)
{
	int	new_in_fd;

	new_in_fd = open(target, O_RDONLY);
	if (old_in_fd != STDIN_FILENO)
		close(old_in_fd);
	if (new_in_fd == -1)
		return (execution_error(target, strerror(errno), -1));
	return (new_in_fd);
}

int	heredoc_redirection(char *target, int old_in_fd)
{
	int	new_in_fd;

	new_in_fd = open(target, O_RDONLY);
	unlink(target);
	if (old_in_fd != STDIN_FILENO)
		close(old_in_fd);
	if (new_in_fd == -1)
		return (execution_error(target, strerror(errno), -1));
	return (new_in_fd);
}

int	parse_redirections(t_vars *vars, struct s_command *curr_command_node, \
	int *in_fd, int *out_fd)
{
	t_redir	*curr_redir;

	(void)vars;
	curr_redir = curr_command_node->redirs;
	while (curr_redir != NULL)
	{
		if (curr_redir->type == REDIR_INPUT)
			*in_fd = input_redirection(curr_redir->target, *in_fd);
		else if (curr_redir->type == REDIR_OUTPUT)
			*out_fd = output_redirection(curr_redir->target, *out_fd);
		else if (curr_redir->type == REDIR_APPEND)
			*out_fd = append_redirection(curr_redir->target, *out_fd);
		else if (curr_redir->type == REDIR_HEREDOC)
			*in_fd = heredoc_redirection(curr_redir->target, *in_fd);
		if (*in_fd == -1 || *out_fd == -1)
			return (-1);
		curr_redir = curr_redir->next;
	}
	return (0);
}
