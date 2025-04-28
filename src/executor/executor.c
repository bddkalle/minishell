/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vboxuser <vboxuser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 10:51:49 by vboxuser          #+#    #+#             */
/*   Updated: 2025/04/28 15:14:00 by vboxuser         ###   ########.fr       */
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
	if (global_received_signal == 0)
	{
		if (ft_strcmp(curr_command_node->argv[0], "echo") == 0)
			exit_code = run_echo(out_fd, curr_command_node->argv);
		else if (ft_strcmp(curr_command_node->argv[0], "pwd") == 0)
			exit_code = run_pwd(out_fd, curr_command_node->argv);
		else if (ft_strcmp(curr_command_node->argv[0], "cd") == 0)
			exit_code = run_cd(vars, curr_command_node->argv);
		else if (ft_strcmp(curr_command_node->argv[0], "export") == 0)
			exit_code = run_export(vars, curr_command_node->argv, out_fd);
		else if (ft_strcmp(curr_command_node->argv[0], "unset") == 0)
			exit_code = run_unset(vars, curr_command_node->argv);
		else if (ft_strcmp(curr_command_node->argv[0], "env") == 0)
			exit_code = run_env(vars, curr_command_node->argv, out_fd);
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
	printf("\n###################### MINISHELL OUTPUT ######################\n");
	//printf("last exit code: %i\n", vars->exit_status);
	execute_ast(vars, vars->ast, STDIN_FILENO, STDOUT_FILENO);
	//free(env_p);
	return ;
}
