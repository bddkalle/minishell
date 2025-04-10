#include "../../include/minishell.h"

// void	input_redirection(t_size new_fd, char *target, int old_fd)
// {
// 	//dup2()
// 	return ;
// }

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

		curr_redir = curr_redir->next;
	}
	return (0);
}
