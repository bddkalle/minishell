#include "../../include/minishell.h"
#include <unistd.h>

int	input_redirection(char *target, int old_in_fd)
{
	int	new_in_fd;

	new_in_fd = open(target, O_RDONLY);
	if (new_in_fd == -1)
		return(execution_error(target, strerror(errno)));
	if (old_in_fd != STDIN_FILENO)
		close(old_in_fd);
	// dup2(new_in_fd, old_in_fd);
	// close(new_in_fd);
	return (new_in_fd);
}

int	parse_redirections(t_vars *vars, struct s_command *curr_command_node, int in_fd, int out_fd)
{
	//int	i;
	t_redir	*curr_redir;

	(void)vars;
	(void)in_fd;
	(void)out_fd;
	curr_redir = curr_command_node->redirs;
	//i = 0;
	while (curr_redir != NULL)
	{
		ft_printf("redirection of type %i found.\n", curr_redir->type);
		if (curr_redir->type == REDIR_INPUT)
			input_redirection(curr_redir->target, in_fd);
		curr_redir = curr_redir->next;
	}
	return (0);
}
