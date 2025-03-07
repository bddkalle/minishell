/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vboxuser <vboxuser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 14:25:06 by fschnorr          #+#    #+#             */
/*   Updated: 2025/03/07 10:54:47 by vboxuser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# define DEL " \t\n"

# include "../lib/libft/includes/libft.h"
# include "structs.h"
# include <stdio.h>
# include <errno.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>


void	minishell(void);

//Initialisation
void	init_vars(t_vars *vars);
void	*_malloc(size_t size, t_vars *vars);


//Prompt
void	get_prompt(t_vars *vars);
void	get_hostname(t_vars *vars);
void	build_prompt(t_vars *vars, char *s);



//Validation, Handle errors & Free
void	error_exit(t_vars *vars, char *s, int exit_code);
void	error_main(char *s, char **argv);
void	free_all(t_vars *vars);
void	free_null(void **ptr);
void	free_null_token(t_vars	*vars);
void	free_null_readline(t_vars *vars);
void	close_all(t_vars *vars);
void	_close(int fd);



//Parser
void			lexer(t_vars *vars);
t_lexer_state	lexer_state(t_vars *vars, char c, t_lexer_state state, int token_pos);
t_token			*create_token(t_vars *vars);
int				is_whitespace(char c);
void			fill_token(t_vars *vars, t_lexer_state state);

//builtins
int	run_echo(int fd, char **argv);

//executor
void	executor(t_vars *vars);




#endif
