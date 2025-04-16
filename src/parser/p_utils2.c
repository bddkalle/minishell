/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_utils2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fschnorr <fschnorr@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 14:55:34 by fschnorr          #+#    #+#             */
/*   Updated: 2025/04/16 14:32:59 by fschnorr         ###   ########.fr       */
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
		// #1 if reserved cmd name (if, then, else, fi,...) [OUT OF SCOPE] else TOKEN -> TOKEN_WORD
		if (tmp->type == TOKEN)
			tmp->type = TOKEN_WORD;
		
		// #2 redirection to or from filename
			//tilde expansion
		if (tmp->next && *tmp->next->value == '~' && (tmp->type == TOKEN_REDIRECT_IN || tmp->type == TOKEN_REDIRECT_OUT \
		|| tmp->type == TOKEN_REDIRECT_APPEND))
		{
			ft_strlcpy(redir_target, vars->prompt->home, ft_strlen(vars->prompt->home) + 1);
			ft_strlcat(redir_target, tmp->next->value + 1, ft_strlen(redir_target) + ft_strlen(tmp->next->value));
			free_null((void **)&tmp->next->value);
			tmp->next->value = ft_strdup(redir_target);
		}

		// #3 redirection from here-document

		// #4 case statement termination [OUT OF SCOPE]

		// #5 NAME in FOR [OUT OF SCOPE]

		// #6 Third word of FOR and CASE [OUT OF SCOPE]

		// #7 Assignment preceding command name [OUT OF SCOPE]

		// #8 NAME in function [OUT OF SCOPE]

		// #9 Body of function [OUT OF SCOPE]
		
		tmp = tmp->next;
	}
}

/* int	last_token_type_is(t_token_type type, t_vars *vars)
{
	t_token	*tmp;

	tmp = vars->token;
	if (tmp)
	{
		if (tmp->next)
		{
			while (tmp->next->next)
				tmp = tmp->next;
		}
	}	if (vars->lexer->state != IN_DOUBLE_QUOTE)
		{
			vars->lexer->token_pos = ft_strlen(substitute);
			create_token(vars);
			vars->lexer->next_node = &(*vars->lexer->next_node)->next;
			vars->lexer->token_pos = 0;
			vars->lexer->curr_token[0] = '\0';
		}
		else
	if (tmp->type == type)
		return (1);
	return (0);
} */

void	expand_parameter(t_vars *vars)
{
	size_t	brace;
	size_t	i;
	char	parameter[99];
	char	*substitute;

	vars->lexer->c = vars->line[++vars->lexer->line_pos];
	i = 0;
	if (char_is("?", vars->lexer->c))
	{
		vars->lexer->curr_token[vars->lexer->token_pos++] = '$';
		vars->lexer->curr_token[vars->lexer->token_pos++] = vars->lexer->c;
		vars->lexer->curr_token[vars->lexer->token_pos] = '\0';
		ft_strlcat(vars->lexer->curr_token, "[SPECIAL]", ft_strlen(vars->lexer->curr_token) + 10);
		vars->lexer->token_pos += 9;
		vars->lexer->c = vars->line[++vars->lexer->line_pos];
		return ;
	}
	else if (char_is("{", vars->lexer->c))
	{
		brace = 1;
		vars->lexer->c = vars->line[++vars->lexer->line_pos];
		while (1)
		{
			if (char_is("{", vars->lexer->c))
				brace++;
			else if (char_is("}", vars->lexer->c))
				brace--;
			if (!brace)
			{
				vars->lexer->line_pos++;
				break ;
			}
			parameter[i++] = vars->lexer->c;
			vars->lexer->c = vars->line[++vars->lexer->line_pos];
		}
		parameter[i] = '\0';
	}
	else if (vars->lexer->c)
	{
		while (vars->lexer->c && is_valid_name(vars->lexer->c))
		{
			parameter[i++] = vars->lexer->c;
			vars->lexer->c = vars->line[++vars->lexer->line_pos];
			parameter[i] = '\0';
			//printf("is valid name: %s\n", parameter);
		}
	//	if (!is_valid_name(vars->lexer->c))
			//printf("is invalid name: %c\n", vars->lexer->c);
		parameter[i] = '\0';
	}
	substitute = getenv(parameter);
	//printf("parameter = %s\n", parameter);
	//printf("substitution = %s\n", substitute);
	if (substitute)
	{
		ft_strlcpy(vars->lexer->curr_token + vars->lexer->token_pos, substitute, ft_strlen(substitute) + 1);
	/* 	if (vars->lexer->state != IN_DOUBLE_QUOTE)
		{
			vars->lexer->token_pos = ft_strlen(substitute);
			create_token(vars);
			vars->lexer->next_node = &(*vars->lexer->next_node)->next;
			vars->lexer->token_pos = 0;
			vars->lexer->curr_token[0] = '\0';
		}
		else */
		vars->lexer->token_pos += ft_strlen(substitute);
	}
}
