/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vboxuser <vboxuser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 10:51:49 by vboxuser          #+#    #+#             */
/*   Updated: 2025/04/30 09:45:30 by vboxuser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	execute_command(t_vars *vars, struct s_command *curr_command_node, int in_fd, int out_fd)
{
	if (parse_redirections(vars, curr_command_node, &in_fd, &out_fd) == -1)
	{
		close_fds(in_fd, out_fd);
		return (1);
	}
	if (global_received_signal == 0)
	{
		if (ft_strcmp(curr_command_node->argv[0], "echo") == 0)
			return (run_echo(out_fd, curr_command_node->argv));
		else if (ft_strcmp(curr_command_node->argv[0], "pwd") == 0)
			return (run_pwd(out_fd, curr_command_node->argv));
		else if (ft_strcmp(curr_command_node->argv[0], "cd") == 0)
			return (run_cd(vars, curr_command_node->argv));
		else if (ft_strcmp(curr_command_node->argv[0], "export") == 0)
			return (run_export(vars, curr_command_node->argv, out_fd));
		else if (ft_strcmp(curr_command_node->argv[0], "unset") == 0)
			return (run_unset(vars, curr_command_node->argv));
		else if (ft_strcmp(curr_command_node->argv[0], "env") == 0)
			return (run_env(vars, curr_command_node->argv, out_fd));
		else if (ft_strcmp(curr_command_node->argv[0], "exit") == 0)
			return (run_exit(vars, curr_command_node->argv, in_fd, out_fd, 0));
		else
			return (run_executable(vars, curr_command_node, in_fd, out_fd));
	}
	else if (global_received_signal == SIGINT)
		global_received_signal = 0;
	return (-1);
}

int	execute_ast(t_vars *vars, t_ast_node *current_node, int in_fd, int out_fd)
{
	int	exit_code;

	exit_code = vars->exit_status;
	if (current_node == NULL)
		return (exit_code);
	else if (current_node->type == AST_COMMAND)
		exit_code = execute_command(vars, &current_node->u_data.s_command,\
			in_fd, out_fd);
	else if (current_node->type == AST_PIPE)
		exit_code = operator_pipe(vars, current_node,\
			in_fd, out_fd);
	else if (current_node->type == AST_AND)
		exit_code = operator_and(vars, current_node,\
			in_fd, out_fd);
	else if (current_node->type == AST_OR)
		exit_code = operator_or(vars, current_node,\
			in_fd, out_fd);
	else if (current_node->type == AST_SUBSHELL)
		exit_code = operator_subshell(vars, current_node,\
			in_fd, out_fd);
	vars->exit_status = exit_code;
	close_fds(in_fd, out_fd);
	return (exit_code);
}

void	executor(t_vars *vars)
{
	if(global_received_signal == SIGINT)
	{
		free_null_readline(vars);
		global_received_signal = 0;
	}
	//printf("\n###################### MINISHELL OUTPUT ######################\n");
	if (!check_exit_parent(vars))
		execute_ast(vars, vars->ast, STDIN_FILENO, STDOUT_FILENO);
	return ;
}
