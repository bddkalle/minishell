/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdahne <cdahne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 18:32:10 by cdahne            #+#    #+#             */
/*   Updated: 2025/05/05 14:27:05 by cdahne           ###   ########.fr       */
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
		write_sigint();
		g_received_signal = 0;
		unlink(tempfile->pathname);
		free_all(vars);
		free(*line);
		free_close_tempfile(tempfile);
		exit(128 + SIGINT);
	}
	if (!*line)
	{
		write_eof_heredoc(del);
		return (1);
	}
	if (ft_strcmp(*line, del) == 0)
	{
		free_null((void **)line);
		return (1);
	}
	expand_variables(vars, line);
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
			free_null((void **)&line);
		}
		else
			break ;
	}
	free_close_tempfile(tempfile);
	free_all(vars);
	exit (EXIT_SUCCESS);
}

t_tempfile	*open_heredoc_dialog(t_vars *vars, char *delimiter)
{
	t_tempfile	*tempfile;
	int			pid;
	int			exit_code;

	tempfile = create_tempfile(vars);
	if (!tempfile)
		return (NULL);
	pid = fork();
	if (pid == -1)
		return (NULL);
	if (pid == 0)
		heredoc_loop(vars, delimiter, tempfile);
	else
	{
		exit_code = heredoc_parent(pid, tempfile);
		if (exit_code == EXIT_SUCCESS)
			return (tempfile);
		else if (exit_code == 130)
			free_null_readline(vars);
	}
	free_close_tempfile(tempfile);
	return (NULL);
}

int	heredoc_setup(t_vars *vars, t_token *target, char *redir_target)
{
	t_tempfile	*tempfile;

	if (g_received_signal == SIGINT)
	{
		free_null_readline(vars);
		g_received_signal = 0;
		return (1);
	}
	signal_heredoc_setup();
	tempfile = open_heredoc_dialog(vars, target->value);
	if (tempfile)
	{
		ft_strlcpy(redir_target, tempfile->pathname, \
			ft_strlen(tempfile->pathname) + 1);
		free_close_tempfile(tempfile);
		free(target->value);
		target->value = ft_strdup(redir_target);
		return (0);
	}
	else if (!tempfile && !vars->parser)
		return (1);
	free_null((void **)&target->value);
	return (0);
}
