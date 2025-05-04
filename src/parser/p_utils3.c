/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_utils3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fschnorr <fschnorr@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 14:55:34 by fschnorr          #+#    #+#             */
/*   Updated: 2025/05/04 20:22:50 by fschnorr         ###   ########.fr       */
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

t_size	remove_quotes_from_string(t_vars *vars, char **s, char c)
{
	char	result[LINE_MAX];
	t_size	i;
	t_size	j;
	t_size	count;

	i = 0;
	j = 0;
	count = 0;
	while ((*s)[i] && count < 2)
	{
		if ((*s)[i] != c)
			result[j++] = (*s)[i];
		else if ((*s)[i] == c)
			count++;
		i++;
	}
	count = i;
	while ((*s)[count])
		result[j++] = (*s)[count++];
	result[j] = '\0';
	free_null((void **)s);
	*s = ft_strdup(result);
	if (!*s)
		error_exit(vars, "strdup failed to recreate token", EXIT_FAILURE);
	return (i - 2);
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
			if (tmp->value[i] == '\'' && quote_is_closed(tmp->value, i))
			{
				i = remove_quotes_from_string(vars, &tmp->value, '\'');
				continue ;
			}
			if (tmp->value[i] == '"' && quote_is_closed(tmp->value, i))
			{
				i = remove_quotes_from_string(vars, &tmp->value, '"');
				continue ;
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
	if (type == TOKEN_PARENT_RIGHT)
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
