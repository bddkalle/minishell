/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fschnorr <fschnorr@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 14:25:06 by fschnorr          #+#    #+#             */
/*   Updated: 2025/02/27 12:21:11 by fschnorr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# define DEL " \t\n"

# include "../lib/libft/includes/libft.h"
# include "structs.h"
# include <stdio.h>
# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>


void	minishell(void);

//Initialisation
void	init_vars(t_vars *vars);
void	*Malloc(size_t size, t_vars *vars);


//Prompt
void	get_prompt(t_vars *vars);
void	build_prompt(t_vars *vars, char *s);



//Validation, Handle errors & Free
void	error_exit(t_vars *vars, char *s, int exit_code);
void	error_main(char *s, char **argv);
void	free_all(t_vars *vars);
void	free_null(void *ptr);


//Parser
void	lexer(t_vars *vars);
t_token	*create_token(t_token_type type, t_vars *vars);
int		is_whitespace(char c);
void	fill_token(t_vars *vars, t_lexer_state state);




#endif