/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs_pipex.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fschnorr <fschnorr@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2025/02/13 16:35:16 by fschnorr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef STRUCTS_H
# define STRUCTS_H

typedef struct s_vars
{
	char	*infile;
	char	*cmd1;
	char	*cmd2;
	char	*outfile;
	char	*bin1;
	char	*bin2;
	char	**envp;
	char	**path;
	char	**args;
	int		fd_in;
	int		fd_out;
	int		fd_pipe[2];
	int		pid1;
	int		pid2;
	int		i;
	int		exit_status;
	int		last_exit_code;
	int		error_print;
}		t_vars;

#endif