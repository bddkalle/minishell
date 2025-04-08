/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_utils3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fschnorr <fschnorr@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 14:55:34 by fschnorr          #+#    #+#             */
/*   Updated: 2025/04/08 11:07:56 by fschnorr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/* size_t	is_valid_name(char *s, size_t i)
{
	if (ft_isdigit(*s))
		return (0);
	if (!char_is("_", s[i]) && !ft_isdigit(s[i]) && !ft_isalpha(s[i]))
		return (0);
	return (1);
}
 */size_t	is_valid_name(char c)
{
	if (ft_isdigit(c))
		return (0);
	if (!char_is("_", c) && !ft_isdigit(c) && !ft_isalpha(c))
		return (0);
	return (1);
}
