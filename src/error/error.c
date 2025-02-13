/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fschnorr <fschnorr@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 14:40:30 by fschnorr          #+#    #+#             */
/*   Updated: 2025/02/13 14:55:19 by fschnorr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	 error(char *s)
{
	if (errno == 0)
	{
		write(2, s, ft_strlen(s));
		write(2, "\n", 1);
	}
	else
	 	perror(s);
	return (1);
}