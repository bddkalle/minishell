/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vboxuser <vboxuser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 14:25:06 by fschnorr          #+#    #+#             */
/*   Updated: 2025/04/23 12:16:36 by vboxuser         ###   ########.fr       */
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

//global variable
extern volatile sig_atomic_t	global_received_signal;

//minishell
void			minishell(char **envp);

//Initialisation
void			init_vars(t_vars *vars);
t_envp			*init_envp(char **param);

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
void			free_envp(t_envp *envp);

//signals
void	signal_handler_global(int signum);
void	signal_shell_setup(void);
void	signal_heredoc_setup(void);
void	sigint_shell_handler(int signum);
void	signal_executable_setup(void);
void	signal_pipe_setup(void);
void	signal_ignore_setup(void);

//Utils
void			*_malloc(size_t size, t_vars *vars);
int				build_path(char *input, char *path, char *home);
void			split_envp(t_envp *envp, char *param);
void			add_envp(t_envp *envp, char *varvalue);

#endif
