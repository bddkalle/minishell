#include "../../include/minishell.h"

int	append_redirection(char *target, int old_out_fd)
{
	int	new_out_fd;

	new_out_fd = open(target, O_WRONLY | O_CREAT | O_APPEND, 0664);
	if (new_out_fd == -1)
		return(execution_error(target, strerror(errno)));
	//ft_printf("opened fd: %i to append to.\n", new_out_fd);
	if (old_out_fd != STDOUT_FILENO)
		close(old_out_fd);
	return (new_out_fd);
}

int	output_redirection(char *target, int old_out_fd)
{
	int	new_out_fd;

	new_out_fd = open(target, O_WRONLY | O_CREAT | O_TRUNC, 0664);
	if (new_out_fd == -1)
		return(execution_error(target, strerror(errno)));
	if (old_out_fd != STDOUT_FILENO)
		close(old_out_fd);
	return (new_out_fd);
}

int	input_redirection(char *target, int old_in_fd)
{
	int	new_in_fd;

	new_in_fd = open(target, O_RDONLY);
	if (new_in_fd == -1)
		return(execution_error(target, strerror(errno)));
	if (old_in_fd != STDIN_FILENO)
		close(old_in_fd);
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
		curr_redir = curr_redir->next;
	}
	return (0);
}
