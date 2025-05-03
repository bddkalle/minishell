/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_utils2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fschnorr <fschnorr@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 14:55:34 by fschnorr          #+#    #+#             */
/*   Updated: 2025/05/02 20:59:11 by fschnorr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_size	is_whitespace(char c)
{
	if (ft_strchr(DEL, c))
		return (1);
	return (0);
}

t_size	is_valid_mult_op(char c, t_vars *vars)
{
	if (c == vars->lexer->curr_token[vars->lexer->token_pos - 1])
		return (1);
	return (0);
}

t_size	token_cof_digits(char *s)
{
	t_size	i;

	i = 0;
	while (s[i])
	{
		if (!ft_isdigit(s[i++]))
			return (0);
	}
	return (1);
}

void	reclassification(t_vars *vars)
{
	t_token	*tmp;
	char	redir_target[PATH_MAX];

	tmp = vars->token;
	while (tmp)
	{
		if (tmp->type == TOKEN)
			tmp->type = TOKEN_WORD;
		if (tmp->next && *tmp->next->value == '~' && \
		(tmp->type == TOKEN_REDIRECT_IN || tmp->type == TOKEN_REDIRECT_OUT \
		|| tmp->type == TOKEN_REDIRECT_APPEND))
		{
			ft_strlcpy(redir_target, vars->prompt->home, \
			ft_strlen(vars->prompt->home) + 1);
			ft_strlcat(redir_target, tmp->next->value + 1, \
			ft_strlen(redir_target) + ft_strlen(tmp->next->value));
			free_null((void **)&tmp->next->value);
			tmp->next->value = NULL;
			//tmp->next->value = ft_strdup(redir_target);
			if (!tmp->next->value)
				error_exit(vars, "strdup failed to expand ~", EXIT_FAILURE);
		}
		// #3 redirection from here-document
		tmp = tmp->next;
	}
}

void	expand_parameter(t_vars *vars)
{
	char	parameter[256];
	char	*substitute;

	vars->lexer->c = vars->line[++vars->lexer->line_pos];
	if (char_is("?", vars->lexer->c))
		return (expand_exit_status(vars));
	else if (char_is("{", vars->lexer->c))
	{
		vars->lexer->curr_token[vars->lexer->token_pos++] = \
		vars->line[vars->lexer->line_pos - 1];
		return ;
	}
	else if (vars->lexer->c)
		get_parameter(vars, parameter);
	if (!ft_strcmp(parameter, "PWD"))
		substitute = vars->pwd;
	else if (!ft_strcmp(parameter, "OLDPWD"))
		substitute = vars->oldpwd;
	else
		substitute = _getenv(vars, parameter);
	if (substitute)
		substitute_parameter(vars, substitute);
}
