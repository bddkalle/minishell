/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fschnorr <fschnorr@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 14:25:06 by fschnorr          #+#    #+#             */
/*   Updated: 2025/04/03 13:19:59 by fschnorr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# define OPEN_MAX 1024

# include "../lib/libft/includes/libft.h"
# include "structs.h"
# include "parser.h"
# include "p_structs.h"
# include "execution.h"
# include <stdio.h>
# include <stdlib.h>
# include <errno.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>


void			minishell(char **envp);

//Initialisation
void			init_vars(t_vars *vars);

//Prompt
void			get_prompt(t_vars *vars);
void			get_hostname(t_vars *vars);
void			build_prompt(t_vars *vars, char *s);
void			update_prompt(t_vars *varsm, char *path);

//Validation, Handle errors & Free
void			error_exit(t_vars *vars, char *s, int exit_code);
void			error_main(char *s, char **argv);
void			free_all(t_vars *vars);
void			free_null(void **ptr);
void			free_null_readline(t_vars *vars);
void			close_all(t_vars *vars);
void			_close(int fd);

//Utils
void			*_malloc(size_t size, t_vars *vars);
int				build_path(char *input, char *path, char *home);

#endif
