/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fschnorr <fschnorr@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 16:13:28 by fschnorr          #+#    #+#             */
/*   Updated: 2025/01/20 12:20:39 by fschnorr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

/* # ifdef BONUS
#  include "bonus/structs_bonus.h"
#  include "bonus/pipex_bonus.h"
# else
#  include "structs.h"
# endif */

# include "structs.h"
# include "../lib/libft/includes/libft.h"
# include <unistd.h>
# include <wait.h>
# include <stdio.h>
# include <errno.h>
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>

int		pipex(char **argv, char **envp);

//Validation, Handle errors & Free
int		error(char *str);
int		close_error(t_vars *vars, char *str);
void	no_exec(t_vars *vars);
int		no_infile(char *infile, char *str);
void	validate_open_files(t_vars *vars);
void	ft_free(t_vars *vars);
void	free_bin(t_vars *vars);
void	free_args(t_vars *vars);
void	close_and_wait(t_vars *vars);

//Initialisation
void	init_vars(t_vars *vars, char **argv, char **envp);
void	get_path_args(t_vars *vars, char *cmd);
char	*find_bin(t_vars *vars);

//Execution
void	child1(t_vars *vars);
void	child2(t_vars *vars);

#endif
