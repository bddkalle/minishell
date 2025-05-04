/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fschnorr <fschnorr@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 18:32:10 by cdahne            #+#    #+#             */
/*   Updated: 2025/05/04 23:53:05 by fschnorr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	fill_line(char **pline, char *ret)
{
	free_null((void **)pline);
	*pline = ret;
}

char	*substitute_heredoc_var(char *s, char *substitute, char *parameter)
{
	char	buffer[LINE_MAX];
	char	*var;
	char	*ret;
	char	*cont;
	char	*tmp;

	ft_bzero(buffer, LINE_MAX);
	ft_strlcpy(buffer, s, ft_strlen(s) + 1);
	//printf("buffer = %s\n", buffer);
	var = ft_strjoin("$", parameter);
	//printf("var = %s\n", var);
	ret = ft_strnstr(buffer, var, ft_strlen(buffer));
	cont = ret + ft_strlen(var);
	free_null((void **)&var);
	*ret = '\0';
	ret = ft_strjoin(buffer, substitute);
	//printf("ret = %s\n", ret);
	//printf("cont = %s\n", cont);
	tmp = ret;
	ret = ft_strjoin(tmp, cont);
	free_null((void**)&tmp);
	//printf("ret = %s\n", ret);
	return (ret);
}

void	expand_variables(t_vars *vars, char **pline)
{
	char	parameter[LINE_MAX];
	char	*substitute;
	char	*ret;
	t_size	i;
	t_size	j;

/* 	if (!del_is_quoted(del))							//handle quoted DEL
	{
		printf("del is not quoted -> expand");
		//get_parameter(vars, parameter);
		return ;
	} */
	ret = NULL;
	i = 0;
	while ((*pline)[i])
	{
		j = 0;
		while ((*pline)[i] && (*pline)[i] != '$')
			i++;
		if ((*pline)[i] == '$')
			i++;
		ft_bzero(parameter, LINE_MAX);
		while ((*pline)[i] && is_valid_name((*pline)[i]))
			parameter[j++] = (*pline)[i++];
		parameter[j] = '\0';
		if (!ft_strcmp(parameter, "PWD"))
			substitute = vars->pwd;
		else if (!ft_strcmp(parameter, "OLDPWD"))
			substitute = vars->oldpwd;
		else
			substitute = _getenv(vars, parameter);
		if (substitute)
			ret = substitute_heredoc_var(*pline, substitute, parameter);
		if ((*pline)[i])
			i++;
	}
	if (ret)
		fill_line(pline, ret);
}

/* int	del_is_quoted(char *del)
{
	if (del[0] == '\'' && del[ft_strlen(del)] == '\'')
		{
			printf("is quoted with ''");
			return (1);
		}
	if (del[0] == '"' && del[ft_strlen(del)] == '"')
		{
			printf("is quoted with \"\"");
			return (1);
		}
	return (0);
}
 */