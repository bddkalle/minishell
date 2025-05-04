/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fschnorr <fschnorr@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 18:32:10 by cdahne            #+#    #+#             */
/*   Updated: 2025/05/04 13:53:13 by fschnorr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	heredoc_parent(int pid, t_tempfile *tempfile)
{
	int	status;

	(void)tempfile;
	signal_ignore_setup();
	waitpid(pid, &status, 0);
	signal_shell_setup();
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (-1);
}

int	analyse_line(t_vars *vars, char **line, t_tempfile *tempfile, char *del)
{
	if (g_received_signal == SIGINT)
	{
		write(STDOUT_FILENO, "\n", 1);
		g_received_signal = 0;
		unlink(tempfile->pathname);
		free_all(vars);
		free(*line);
		free_close_tempfile(tempfile);
		exit(SIGINT);
	}
	if (!line)
	{
		write(STDERR_FILENO, \
			"minishell: warning: here-document delimited by end-of-file (wanted '", 68);
		write(STDERR_FILENO, del, ft_strlen(del));
		write(STDERR_FILENO, "')\n", 3);
		return (1);
	}
	if (ft_strcmp(*line, del) == 0)
	{
		free_null((void **)line);
		return (1);
	}
	expand_variables(vars, line);
 	//printf("line = %s\n", *line);
	return (0);
}

void	heredoc_loop(t_vars *vars, char *delimiter, t_tempfile *tempfile)
{
	int		i;
	char	*line;

	signal_heredoc_setup();
	while (1)
	{
		disable_echotcl();
		line = custom_readline("> ");
		enable_echoctl();
		if (analyse_line(vars, &line, tempfile, delimiter) == 0)
		{
			i = 0;
			while (line[i])
				write(tempfile->fd, &line[i++], 1);
			write(tempfile->fd, "\n", 1);
		}
		else
			break ;
		free_null((void **)&line);
	}
	free_close_tempfile(tempfile);
	free_all(vars);
	exit (EXIT_SUCCESS);
}

t_tempfile	*open_heredoc_dialog(t_vars *vars, char *delimiter)
{
	t_tempfile	*tempfile;
	int			pid;

	//create tempfile: beware memory leaks get cleaned by fatal_error which calls free_all().
	//shouldnt it use a different error function by felix?
	tempfile = create_tempfile(vars);
	if (!tempfile)
		return (NULL);
	// if (old_in_fd != STDIN_FILENO)
	// 	close(old_in_fd);
	pid = fork();
	if (pid == -1)
		return (NULL);
	//	return (execution_error("fork", strerror(errno), -1));
	if (pid == 0)
		heredoc_loop(vars, delimiter, tempfile);
	else
		if (heredoc_parent(pid, tempfile) == EXIT_SUCCESS)
			return (tempfile);
	free_close_tempfile(tempfile);
	return (NULL);
}

void	heredoc_setup(t_vars *vars, t_token *target, char *redir_target)
{
	t_tempfile	*tempfile;

	if (g_received_signal == SIGINT)
	{
		free_null_readline(vars);
		g_received_signal = 0;
		return ;
	}
	signal_heredoc_setup();
	tempfile = open_heredoc_dialog(vars, target->value);
	if (tempfile)
	{
		ft_strlcpy(redir_target, tempfile->pathname, ft_strlen(tempfile->pathname) + 1);
		free_close_tempfile(tempfile);
		free(target->value);
		target->value = ft_strdup(redir_target);
	}
	else
		free_null((void **)&target->value);
}
