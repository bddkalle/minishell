/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_utils9.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fschnorr <fschnorr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 14:55:34 by fschnorr          #+#    #+#             */
/*   Updated: 2025/05/05 11:04:52 by fschnorr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	syntax_error_double_quote(t_vars *vars)
{
	ft_putstr_fd(\
	"minishell: syntax error: unexpected end of file in double-quote\n"\
	, 2);
	vars->exit_status = 2;
	free_null_readline(vars);
}

void	handle_syntax_error(t_vars *vars, t_token *tok)
{
	ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
	if (tok)
		ft_putstr_fd(tok->value, 2);
	else
		ft_putstr_fd("newline", 2);
	ft_putstr_fd("'\n", 2);
	vars->exit_status = 2;
}

void	start_substitution(t_vars *vars, char **substitute, char *parameter)
{
	if (!ft_strcmp(parameter, "PWD"))
		*substitute = vars->pwd;
	else if (!ft_strcmp(parameter, "OLDPWD"))
		*substitute = vars->oldpwd;
	else
		*substitute = _getenv(vars, parameter);
}

t_size	is_var_included(char **pline)
{
	t_size	i;

	i = 0;
	while ((*pline)[i] && (*pline)[i] != '$')
		i++;
	if ((*pline)[i] == '$')
		i++;
	if ((*pline)[i] && is_valid_name((*pline)[i]))
		return (1);
	return (0);
}
