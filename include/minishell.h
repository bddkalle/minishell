/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fschnorr <fschnorr@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 14:25:06 by fschnorr          #+#    #+#             */
/*   Updated: 2025/04/29 23:55:16 by fschnorr         ###   ########.fr       */
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
void			init_envp(t_vars *vars, char **param);
void			init_pwd_oldpwd(t_vars *vars);

//Prompt
void			get_prompt(t_vars *vars);
void			get_hostname(t_vars *vars);
void			build_prompt(t_vars *vars, char *s);
void			update_prompt(t_vars *vars);

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
void	signal_readline_setup(void);
void	signal_shell_setup(void);
void	signal_heredoc_setup(void);
void	sigint_shell_handler(int signum);
void	signal_executable_setup(void);
void	signal_pipe_setup(void);
void	signal_ignore_setup(void);

//Utils
void			*_malloc(size_t size, t_vars *vars);
int				build_path(char *input, char *path, char *home);
t_envp			*create_envp_node(char *varvalue); //delete one of these
void			split_envp(t_envp *envp, char *param); //delete one of these
void			add_envp(t_envp *envp, char *varvalue);
void			add_or_replace_envp(t_vars *vars, t_envp *envp_node);
void			replace_value(t_envp *old, t_envp *new);
char			**envp_to_array(t_envp *envp_ll);
void			free_envp_array(char **envp);
int				count_nodes(t_envp *envp_ll);
void			swap_envp(char **s1, char **s2);
void			sort_envp(char **envp);
char			*_getenv(t_vars *vars, char *var);


#endif
