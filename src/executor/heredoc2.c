/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fschnorr <fschnorr@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 18:32:10 by cdahne            #+#    #+#             */
/*   Updated: 2025/05/04 05:11:59 by fschnorr         ###   ########.fr       */
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
	
	printf("line = %s\n", s);
	
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
		printf("parameter = %s\n", parameter);
		if (!ft_strcmp(parameter, "PWD"))
			substitute = vars->pwd;
		else if (!ft_strcmp(parameter, "OLDPWD"))
			substitute = vars->oldpwd;
		else
			substitute = _getenv(vars, parameter);
		printf("substitute = %s\n", substitute);
		if (substitute)			//replace $VAR
		{
			ft_bzero(buffer, LINE_MAX);
			ft_strlcpy(buffer, s, ft_strlen(s) + 1);
			printf("buffer = %s\n", buffer);
			var = ft_strjoin("$", parameter);		//free!!!
			printf("var = %s\n", var);
			ret = ft_strnstr(buffer, var, ft_strlen(buffer));
			cont = ret + ft_strlen(var);
			*ret = '\0';
			ret = ft_strjoin(buffer, substitute);
			printf("ret = %s\n", ret);
			printf("cont = %s\n", cont);
			ret = ft_strjoin(ret, cont);
			printf("ret = %s\n", ret);
		}
		if (s[i])
			i++;
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

/* void expand_variables(char **pline, t_vars *vars)
{
    size_t alloc = strlen(*pline) + 1;
    char *src  = *pline;
    char *dst  = malloc(alloc), *d = dst;
    char *s    = src;

    while (*s)
    {
        if (*s == '$' && is_valid_name(s[1]))  // simple $VAR
        {
            char name[64];
            size_t ni = 0, skip = 1;
            while (is_valid_name(s[skip]))
                name[ni++] = s[skip++];
            name[ni] = '\0';

            char *val = (!strcmp(name, "?"))
                         ? ft_itoa(vars->exit_status)
                         : _getenv(vars, name);
            size_t vlen = val ? strlen(val) : 0;
            size_t needed = (d - dst) + vlen + strlen(s + skip) + 1;
            if (needed > alloc)
            {
                alloc = needed * 2;
                dst   = realloc(dst, alloc);
                d     = dst + (d - dst);
            }
            if (val)
            {
                memcpy(d, val, vlen);
                d += vlen;
            }
            s += skip;
        }
        else
        {
            *d++ = *s++;
        }
    }
    *d = '\0';
    free(src);
    *pline = dst;
}
 */