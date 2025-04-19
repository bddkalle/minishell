#include "../../include/minishell.h"
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int	heredoc_redirection(t_vars *vars, char *delimiter, int old_in_fd)
{
	int		temp_fd;
	char	*line;
	int		i;
	int		pid;
	int		status;
	int		w;

	temp_fd = open("heredoc_temp", O_CREAT | O_EXCL | O_WRONLY, 0600);
	if (temp_fd == -1)
		return (execution_error("heredoc_temp", strerror(errno)));
	if (old_in_fd != STDIN_FILENO)
		close(old_in_fd);
	pid = fork();
	if (pid == -1)
		return (execution_error("fork", strerror(errno)));
	if (pid == 0)
	{
		signal_heredoc_setup();
		while(1)
		{
			global_received_signal = 0;
			line = readline("> ");
			if (global_received_signal == SIGINT)
			{
				global_received_signal = 0;
				free_all(vars);
				free(line);
				close(temp_fd);
				unlink("heredoc_temp");
				ft_printf("signal received and exiting heredoc child.\n");
				exit(130);
			}
			if (!line)
			{
				ft_putstr_fd("bash: warning: here-document delimited by end-of-file (wanted '", STDERR_FILENO);
				ft_putstr_fd(delimiter, STDERR_FILENO);
				ft_putstr_fd("')\n", STDERR_FILENO);
				break;
			}
			add_history(line);
			if (ft_strcmp(line, delimiter) == 0)
			{
				free(line);
				break;
			}
			i = 0;
			while(line[i])
				write(temp_fd, &line[i++], 1);
			write(temp_fd, "\n", 1);
			free(line);
		}
		close(temp_fd);
		free_all(vars);
		exit (EXIT_SUCCESS);
	}
	else
	{
		w = -1;
		while (w == -1)
			w = waitpid(pid, &status, 0);
		if (WIFEXITED(status))
		{
			ft_printf("Child process for heredoc terminated normally with exit code %d.\n", WEXITSTATUS(status));
			close(temp_fd);
			temp_fd = open("heredoc_temp", O_RDONLY);
			unlink("heredoc_temp");
			return (temp_fd);
		}
		// else if (WIFSIGNALED(status))
		// {
		// 	ft_printf("child for heredoc killed by signal with code %d\n.", WTERMSIG(status));
		// 	return(WTERMSIG(status));
		// }

		// if (waitpid(pid, &status, 0) == -1)
		// {
		// 	ft_printf("waitpid interrupted.\n");
		// 	unlink("heredoc_temp");
		// 	close(temp_fd);
		// 	return (-1);
		// }
		// else
		// {
		// 	if (WIFEXITED(status))
		// 	{
		// 		ft_printf("Child process for heredoc terminated normally with exit code %d.\n", WEXITSTATUS(status));
		// 		close(temp_fd);
		// 		temp_fd = open("heredoc_temp", O_RDONLY);
		// 		unlink("heredoc_temp");
		// 		return (temp_fd);
		// 	}
		// 	else if (WIFSIGNALED(status))
		// 	{
		// 		ft_printf("child for heredoc killed by signal with code %d\n.", WTERMSIG(status));
		// 		return(WTERMSIG(status));
		// 	}
		// }
		close(temp_fd);
		//temp_fd = open("heredoc_temp", O_RDONLY);
		unlink("heredoc_temp");
	}
	return (-1);
}

int	append_redirection(char *target, int old_out_fd)
{
	int	new_out_fd;

	new_out_fd = open(target, O_WRONLY | O_CREAT | O_APPEND, 0664);
	if (old_out_fd != STDOUT_FILENO)
		close(old_out_fd);
	if (new_out_fd == -1)
		return(execution_error(target, strerror(errno)));
	//ft_printf("opened fd: %i to append to.\n", new_out_fd);
	return (new_out_fd);
}

int	output_redirection(char *target, int old_out_fd)
{
	int	new_out_fd;

	new_out_fd = open(target, O_WRONLY | O_CREAT | O_TRUNC, 0664);
	if (old_out_fd != STDOUT_FILENO)
		close(old_out_fd);
	if (new_out_fd == -1)
		return(execution_error(target, strerror(errno)));
	return (new_out_fd);
}

int	input_redirection(char *target, int old_in_fd)
{
	int	new_in_fd;

	new_in_fd = open(target, O_RDONLY);
	if (old_in_fd != STDIN_FILENO)
		close(old_in_fd);
	if (new_in_fd == -1)
		return(execution_error(target, strerror(errno)));
	return (new_in_fd);
}

int	parse_redirections(t_vars *vars, struct s_command *curr_command_node, int *in_fd, int *out_fd)
{
	t_redir	*curr_redir;

	(void)vars;
	curr_redir = curr_command_node->redirs;
	while (curr_redir != NULL)
	{
		//ft_printf("redirection of type %i found.\n", curr_redir->type);
		if (curr_redir->type == REDIR_INPUT)
			*in_fd = input_redirection(curr_redir->target, *in_fd);
		else if (curr_redir->type == REDIR_OUTPUT)
			*out_fd = output_redirection(curr_redir->target, *out_fd);
		else if(curr_redir->type == REDIR_APPEND)
			*out_fd = append_redirection(curr_redir->target, *out_fd);
		else if (curr_redir->type == REDIR_HEREDOC)
			*in_fd = heredoc_redirection(vars, curr_redir->target, *in_fd);
		if (*in_fd == -1 || *out_fd == -1)
			return (-1);
		curr_redir = curr_redir->next;
	}
	return (0);
}
