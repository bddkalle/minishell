/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_utils3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fschnorr <fschnorr@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 14:55:34 by fschnorr          #+#    #+#             */
/*   Updated: 2025/05/02 22:54:07 by fschnorr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_size	is_valid_name(char c)
{
	if (ft_isdigit(c))
		return (0);
	if (!char_is("_", c) && !ft_isdigit(c) && !ft_isalpha(c))
		return (0);
	return (1);
}

char	*remove_quotes_from_string(t_vars *vars, const char *s, char c)
{
	size_t	len;
	char	*result;
	size_t	i;
	size_t	j;

	len = ft_strlen(s);
	result = _malloc(len + 1, vars);
	i = 0;
	j = 0;
	while (s[i])
	{
		if (s[i] != c)
			result[j++] = s[i];
		i++;
	}
	result[j] = '\0';
	free_null((void **)&s);
	return (result);
}

void	remove_quotes(t_vars *vars)
{
	t_token	*tmp;
	size_t	i;

	tmp = vars->token;
	while (tmp)
	{
		i = 0;
		while (tmp->value[i])
		{
			if (tmp->value[i] == '\'')
			{
				tmp->value = remove_quotes_from_string(vars, tmp->value, '\'');
				break ;
			}
			if (tmp->value[i] == '"')
			{
				tmp->value = remove_quotes_from_string(vars, tmp->value, '"');
				break ;
			}
			i++;
		}
		tmp = tmp->next;
	}
}

t_size	is_invalid_leading_op(t_token_type type)
{
	if (type == TOKEN_PIPE)
		return (1);
	if (type == TOKEN_AND)
		return (1);
	if (type == TOKEN_OR)
		return (1);
	return (0);
}

t_size	is_consecutive_op(t_token_type type)
{
	if (type == TOKEN_PIPE)
		return (1);
	if (type == TOKEN_AND)
		return (1);
	if (type == TOKEN_OR)
		return (1);
	return (0);
}
