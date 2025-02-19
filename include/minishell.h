/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fschnorr <fschnorr@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 14:25:06 by fschnorr          #+#    #+#             */
/*   Updated: 2025/02/19 17:03:38 by fschnorr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../lib/libft/includes/libft.h"
# include "structs.h"
# include <stdio.h>
# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>


void	minishell(void);

//Initialisation
void	init_vars(t_vars *vars);

//Prompt
void	get_prompt(t_vars *vars);
void	build_prompt(t_vars *vars, char *s);



//Validation, Handle errors & Free
void	error_exit(t_vars *vars, char *s, int exit_code);
void	error_main(char *s, char **argv);
void	free_all(t_vars *vars);
void	free_null(void *ptr);



#endif