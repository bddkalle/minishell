/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vboxuser <vboxuser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 10:51:49 by vboxuser          #+#    #+#             */
/*   Updated: 2025/05/02 14:33:07 by vboxuser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	builtin_or_executable(t_vars *vars, struct s_command *curr_command_node, \
	int in_fd, int out_fd)
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
		return (run_exit_child(vars, curr_command_node->argv, in_fd, out_fd));
	else
		return (run_executable(vars, curr_command_node, in_fd, out_fd));
}

int	execute_command(t_vars *vars, struct s_command *curr_command_node, \
	int in_fd, int out_fd)
{
	int	exit_code;

	exit_code = -1;
	if (parse_redirections(vars, curr_command_node, &in_fd, &out_fd) == -1)
		return (close_fds(in_fd, out_fd));
	if (g_received_signal == 0)
		exit_code = builtin_or_executable(vars, curr_command_node, \
			in_fd, out_fd);
	else if (g_received_signal == SIGINT)
		g_received_signal = 0;
	close_fds(in_fd, out_fd);
	return (exit_code);
}

int	execute_ast(t_vars *vars, t_ast_node *current_node, int in_fd, int out_fd)
{
	int	exit_code;

	exit_code = vars->exit_status;
	if (current_node == NULL)
		return (exit_code);
	else if (current_node->type == AST_COMMAND)
		exit_code = execute_command(vars, &current_node->u_data.s_command, \
			in_fd, out_fd);
	else if (current_node->type == AST_PIPE)
		exit_code = operator_pipe(vars, current_node, \
			in_fd, out_fd);
	else if (current_node->type == AST_AND)
		exit_code = operator_and(vars, current_node, \
			in_fd, out_fd);
	else if (current_node->type == AST_OR)
		exit_code = operator_or(vars, current_node, \
			in_fd, out_fd);
	else if (current_node->type == AST_SUBSHELL)
		exit_code = operator_subshell(vars, current_node, \
			in_fd, out_fd);
	vars->exit_status = exit_code;
	return (exit_code);
}

void	executor(t_vars *vars)
{
	if (g_received_signal == SIGINT)
	{
		ft_printf("SIGINT found resetting now.\n");
		free_null_readline(vars);
		g_received_signal = 0;
	}
	if (vars->ast != NULL && vars->ast->type == AST_COMMAND)
	{
		if (ft_strcmp(vars->ast->u_data.s_command.argv[0], "exit") == 0)
		{
			run_exit_parent(vars, vars->ast->u_data.s_command.argv, \
			STDIN_FILENO, STDOUT_FILENO);
			vars->exit_status = 1;
			return ;
		}
	}
	execute_ast(vars, vars->ast, STDIN_FILENO, STDOUT_FILENO);
	return ;
}
