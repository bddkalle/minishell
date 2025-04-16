/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vboxuser <vboxuser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 16:35:38 by fschnorr          #+#    #+#             */
/*   Updated: 2025/04/16 14:22:44 by vboxuser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include "minishell.h"
# include "p_structs.h"
# include <linux/limits.h>


											//	AST	//

typedef enum e_node_type
{
	AST_COMMAND,
	AST_PIPE,
	AST_AND,
	AST_OR,
	AST_SUBSHELL,
}	t_node_type;

typedef enum e_redir_type
{
	REDIR_INPUT,
	REDIR_OUTPUT,
	REDIR_APPEND,
	REDIR_HEREDOC,
}	t_redir_type;

typedef struct s_redir
{
	int				fd;
	t_redir_type	type;
	char			*target;						//filename or heredoc delimiter
	struct s_redir	*next;							//next redirection in list if any
}					t_redir;

typedef struct s_ast_node
{
	t_node_type					type;
	union u_data
	{
		struct s_command
		{
			char				**argv;				//array of command/args strings (At this stage, the tokens have been processed so that single/double quotes are respected, and environment variables or wildcards might be marked for expansion)
			t_redir				*redirs;			//linked list of redirections
		} 	s_command;
		struct s_operator
		{
			struct s_ast_node	*left;
			struct s_ast_node	*right;
		}	s_operator;								//for operators "|" , "&&" and "||"
		struct s_subshell
		{
			struct s_ast_node	*child;
		} 	s_subshell;								//for parenthesized commands
	} u_data;
}								t_ast_node;

												//	MAIN  //
typedef struct s_prompt
{
	char		*user;
	char		*hostname;
	char		*pwd;
	char		*home;
	char		*cwd;
	char		*prompt;
	int			fd_hostname;
}				t_prompt;

typedef struct s_vars
{
	int			exit_status;
	t_prompt	*prompt;
	t_lexer		*lexer;
	t_token		*token;
	t_parser	*parser;
	t_ast_node	*ast;
	char		path[PATH_MAX];
	char		*line;
	char		**envp;
}				t_vars;


#endif
