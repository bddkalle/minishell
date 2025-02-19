/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fschnorr <fschnorr@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 16:35:38 by fschnorr          #+#    #+#             */
/*   Updated: 2025/02/19 12:15:32 by fschnorr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

typedef struct s_prompt
{
	char		*user;
	char		*hostname;
	char		*pwd;
	char		*home;
	char		*cwd;
	char		*prompt;
}				t_prompt;

typedef struct s_vars
{
	t_prompt	*prompt;
} 				t_vars;

#endif