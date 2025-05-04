/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_utils6.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fschnorr <fschnorr@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 14:55:34 by fschnorr          #+#    #+#             */
/*   Updated: 2025/05/04 21:07:57 by fschnorr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	handle_double_qt(t_vars *vars)
{
	while (1)
	{
		if (vars->lexer->c && char_is("\"", vars->lexer->c))
		{
			vars->lexer->curr_token[vars->lexer->token_pos++] = vars->lexer->c;
			vars->lexer->line_pos++;	
			break ;
		}
		if (!vars->lexer->c)
			break ;
		/* {
			vars->lexer->curr_token[vars->lexer->token_pos++] = '\n';
			free_null((void **)&vars->line);
			vars->lexer->line_pos = 0;
			vars->line = readline("> ");
			add_history(vars->line);
			vars->lexer->c = vars->line[vars->lexer->line_pos];
			continue ;
		} */
		else if (char_is("$", vars->lexer->c) && !char_is(" ", \
		vars->line[vars->lexer->line_pos + 1]) \
		&& !char_is("\"", vars->line[vars->lexer->line_pos + 1]))
		{
			expand_parameter(vars);
			continue ;
		}
		vars->lexer->curr_token[vars->lexer->token_pos++] = vars->lexer->c;
		vars->lexer->c = vars->line[++vars->lexer->line_pos];
	}
}

void	expand_exit_status(t_vars *vars)
{
	char	*substitute;

	substitute = ft_itoa(vars->exit_status);
	if (!substitute)
		error_exit(vars, "ft_itoa failed to convert exit_status", EXIT_FAILURE);
	ft_strlcpy(vars->lexer->curr_token + vars->lexer->token_pos, \
				substitute, ft_strlen(substitute) + 1);
	vars->lexer->token_pos += ft_strlen(substitute);
	free_null((void **)&substitute);
	vars->lexer->c = vars->line[++vars->lexer->line_pos];
}

void	get_parameter(t_vars *vars, char *parameter)
{
	size_t	i;

	i = 0;
	vars->exit_status = 0;
	while (vars->lexer->c && is_valid_name(vars->lexer->c))
	{
		parameter[i++] = vars->lexer->c;
		vars->lexer->c = vars->line[++vars->lexer->line_pos];
		parameter[i] = '\0';
	}
	parameter[i] = '\0';
}

void	substitute_parameter(t_vars *vars, char *substitute)
{
	ft_strlcpy(vars->lexer->curr_token + vars->lexer->token_pos, \
		substitute, ft_strlen(substitute) + 1);
	vars->lexer->token_pos += ft_strlen(substitute);
}

void	check_redir_syntax(t_vars *vars)
{
	t_token	*curr_tok;

	curr_tok = vars->token;
	while (curr_tok)										//check redir syntax
	{
		if (curr_tok->type == TOKEN_REDIRECT_IN || \
			curr_tok->type == TOKEN_REDIRECT_OUT || \
			curr_tok->type == TOKEN_REDIRECT_APPEND || \
			curr_tok->type == TOKEN_HEREDOC)
		{
			if (curr_tok->next && curr_tok->next->type != TOKEN)
			{
				ft_putstr_fd("minishell: syntax error near unexpected token »", \
				2);
				ft_putstr_fd(curr_tok->next->value, 2);
				ft_putstr_fd("«\n", 2);
				vars->exit_status = 2;
				free_null_token(vars);
				return ;
			}
			if (!curr_tok->next)
			{
				ft_putstr_fd("minishell: syntax error near unexpected token \
				»newline«\n", 2);
				vars->exit_status = 2;
				free_null_token(vars);
				return ;
			}
		}
		if (curr_tok && curr_tok->next) //handle consecutive operator
		{
			if (is_consecutive_op(curr_tok->type) && \
				is_consecutive_op(curr_tok->next->type))
			{
				handle_consecutive_op(vars, curr_tok);
				return ;
			}
		}
		if (curr_tok->type == TOKEN_PIPE ||
			curr_tok->type == TOKEN_AND ||
			curr_tok->type == TOKEN_OR)
						if (!curr_tok->next)
		{
			ft_putstr_fd("minishell: syntax error near unexpected token \
			»newline«\n", 2);
			vars->exit_status = 2;
			free_null_token(vars);
			return ;
		}
		if (curr_tok->type == TOKEN_PARENT_LEFT)
		{
			if (!closing_par(vars, curr_tok))
				return ;
		}
		curr_tok = curr_tok->next;
	}
}
