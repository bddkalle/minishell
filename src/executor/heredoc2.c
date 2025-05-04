/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fschnorr <fschnorr@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 18:32:10 by cdahne            #+#    #+#             */
/*   Updated: 2025/05/04 11:01:22 by fschnorr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	expand_variables(t_vars *vars, char **pline, char *del)
{
	char	*s;
	char	parameter[LINE_MAX];
	char	buffer[LINE_MAX];
	char	*substitute;
	char	*var;
	char	*ret;
	char	*cont;
	char	*tmp;
	t_size	i;
	t_size	j;

/* 	if (!del_is_quoted(del))							//handle quoted DEL
	{
		printf("del is not quoted -> expand");
		//get_parameter(vars, parameter);
		return ;
	}
 */	
	s = *pline;
	i = 0;
	
	//printf("line = %s\n", s);
	
	while (s[i])
	{
		j = 0;
		while (s[i] && s[i] != '$')
			i++;
		if (s[i] == '$')
			i++;
		ft_bzero(parameter, LINE_MAX);
		while (s[i] && is_valid_name(s[i]))
			parameter[j++] = s[i++];
		parameter[j] = '\0';
		//printf("parameter = %s\n", parameter);
		if (!ft_strcmp(parameter, "PWD"))
			substitute = vars->pwd;
		else if (!ft_strcmp(parameter, "OLDPWD"))
			substitute = vars->oldpwd;
		else
			substitute = _getenv(vars, parameter);
		//printf("substitute = %s\n", substitute);
		if (substitute)			//replace $VAR
		{
			ft_bzero(buffer, LINE_MAX);
			ft_strlcpy(buffer, s, ft_strlen(s) + 1);
			//printf("buffer = %s\n", buffer);
			var = ft_strjoin("$", parameter);		//free!!!
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
		}
		if (s[i])
			i++;
	}
	if (ret)
	{
		free_null((void **)pline);
		*pline = ret;
	}
}

int	del_is_quoted(char *del)
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
