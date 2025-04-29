/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fschnorr <fschnorr@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 10:51:49 by vboxuser          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2025/04/28 22:34:00 by vboxuser         ###   ########.fr       */
=======
/*   Updated: 2025/04/28 22:42:38 by fschnorr         ###   ########.fr       */
>>>>>>> parsing
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	execute_command(t_vars *vars, struct s_command *curr_command_node, int in_fd, int out_fd)
{
	if (parse_redirections(vars, curr_command_node, &in_fd, &out_fd) == -1)
	{
		close_fds(in_fd, out_fd);
		return (-1);
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
			return (run_exit(vars, curr_command_node->argv, in_fd, out_fd));
		else
			return (run_executable(vars, curr_command_node, in_fd, out_fd));
	}
	else if (global_received_signal == SIGINT)
		global_received_signal = 0;
	close_fds(in_fd, out_fd);
	return (-1);
}

int	execute_ast(t_vars *vars, t_ast_node *current_node, int in_fd, int out_fd)
{
	int	exit_code;

	if (current_node == NULL)
		return (vars->exit_status);
	else if (current_node->type == AST_COMMAND)
		exit_code = execute_command(vars, &current_node->u_data.s_command,\
			in_fd, out_fd);
	else if (current_node->type == AST_PIPE)
		exit_code = operator_pipe(vars, current_node,\
			in_fd, out_fd);
	else if (current_node->type == AST_AND)
		exit_code = operator_and(vars, current_node,\
			STDIN_FILENO, STDOUT_FILENO);
	else if (current_node->type == AST_OR)
		exit_code = operator_and(vars, current_node,\
			STDIN_FILENO, STDOUT_FILENO);
	else if (current_node->type == AST_SUBSHELL)
		exit_code = 1;
	vars->exit_status = exit_code;
	return (exit_code);
}

void	executor(t_vars *vars)
{
	if(global_received_signal == SIGINT)
	{
		free_null_readline(vars);
		global_received_signal = 0;
	}
<<<<<<< HEAD
	printf("\n###################### MINISHELL OUTPUT ######################\n");
	//exit handler
=======
	//printf("\n###################### MINISHELL OUTPUT ######################\n");
>>>>>>> parsing
	execute_ast(vars, vars->ast, STDIN_FILENO, STDOUT_FILENO);
	return ;
}
