/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fschnorr <fschnorr@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 10:51:49 by vboxuser          #+#    #+#             */
/*   Updated: 2025/04/24 12:17:17 by fschnorr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	execute_command(t_vars *vars, struct s_command *curr_command_node, int in_fd, int out_fd)
{
	int	exit_code;
	if (parse_redirections(vars, curr_command_node, &in_fd, &out_fd) == -1)
	{
		close_fds(in_fd, out_fd);
		return (-1);
	}
	//sleep(2);
	if (global_received_signal == 0)
	{
		if (ft_strcmp(curr_command_node->argv[0], "echo") == 0)
			exit_code = run_echo(out_fd, curr_command_node->argv);
		else if (ft_strcmp(curr_command_node->argv[0], "pwd") == 0)
			exit_code = run_pwd(out_fd, curr_command_node->argv);
		else if (ft_strcmp(curr_command_node->argv[0], "cd") == 0)
			exit_code = run_cd(vars);
		else if (ft_strcmp(curr_command_node->argv[0], "export") == 0)
			exit_code = 666;
		else if (ft_strcmp(curr_command_node->argv[0], "unset") == 0)
			exit_code = 666;
		else if (ft_strcmp(curr_command_node->argv[0], "env") == 0)
			exit_code = 666;
		else if (ft_strcmp(curr_command_node->argv[0], "exit") == 0)
			exit_code = 666;
		else
			exit_code = run_executable(vars, curr_command_node, in_fd, out_fd);
	}
	else if (global_received_signal == SIGINT)
		global_received_signal = 0;
	close_fds(in_fd, out_fd);
	vars->exit_status = exit_code;
	return (exit_code);
}
/*
int	execute_command(t_vars *vars, struct s_command *curr_command_node, int in_fd, int out_fd)
{
	ft_printf("in_fd before redir: %i\n", in_fd);
	ft_printf("out_fd before redir: %i\n", out_fd);

	if (parse_redirections(vars, curr_command_node, &in_fd, &out_fd) == -1)
		return (-1);
	ft_printf("in_fd after redir: %i\n", in_fd);
	ft_printf("out_fd after redir: %i\n", out_fd);

	if (ft_strcmp(curr_command_node->argv[0], "echo") == 0)
		return (run_echo(out_fd, curr_command_node->argv));
	else if (ft_strcmp(curr_command_node->argv[0], "pwd") == 0)
		return (run_pwd(out_fd, curr_command_node->argv));
	else if (ft_strcmp(curr_command_node->argv[0], "cd") == 0)
		return (run_cd(vars));
	else if (ft_strcmp(curr_command_node->argv[0], "export") == 0)
		return (1);
	else if (ft_strcmp(curr_command_node->argv[0], "unset") == 0)
		return (1);
	else if (ft_strcmp(curr_command_node->argv[0], "env") == 0)
		return (1);
	else if (ft_strcmp(curr_command_node->argv[0], "exit") == 0)
		return (1);
	else
		return (run_executable(vars, curr_command_node, in_fd, out_fd));
	return (-1);
}
*/

int	execute_ast(t_vars *vars, t_ast_node *current_node, int in_fd, int out_fd)
{
	if (current_node == NULL)
		return (0);
	if (current_node->type == AST_COMMAND)
		return (execute_command(vars, &current_node->u_data.s_command,\
			in_fd, out_fd));
	else if (current_node->type == AST_PIPE)
		return (operator_pipe(vars, current_node,\
			in_fd, out_fd));
	else if (current_node->type == AST_AND)
		return (operator_and(vars, current_node,\
			STDIN_FILENO, STDOUT_FILENO));
	else if (current_node->type == AST_OR)
		return (operator_and(vars, current_node,\
			STDIN_FILENO, STDOUT_FILENO));
	else if (current_node->type == AST_SUBSHELL)
		return (1);
	return (-1);
}

void	executor(t_vars *vars)
{
	if(global_received_signal == SIGINT)
	{
		free_null_readline(vars);
		global_received_signal = 0;
	}
	//env_p;
	//printf("\n###################### MINISHELL OUTPUT ######################\n");
	//printf("last exit code: %i\n", vars->exit_status);
	execute_ast(vars, vars->ast, STDIN_FILENO, STDOUT_FILENO);
	//free(env_p);
	return ;
}
