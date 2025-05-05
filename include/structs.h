/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fschnorr <fschnorr@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 16:35:38 by fschnorr          #+#    #+#             */
/*   Updated: 2025/05/05 01:28:33 by fschnorr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include "minishell.h"
# include "p_structs.h"
# include "e_structs.h"
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
	char			*target;
	struct s_redir	*next;
}					t_redir;

typedef struct s_ast_node
{
	t_node_type					type;
	union u_data
	{
		struct s_command
		{
			char				**argv;
			t_redir				*redirs;
		}	s_command;
		struct s_operator
		{
			struct s_ast_node	*left;
			struct s_ast_node	*right;
		}	s_operator;
		struct s_subshell
		{
			struct s_ast_node	*child;
		}	s_subshell;
	} u_data;
}								t_ast_node;

											//	PARSER	//

typedef struct s_parser
{
	t_token		*curr_tok;
	t_ast_node	*node;
	t_redir		**next_redir_node;
	t_size		tok_pos;
}	t_parser;

												//	MAIN  //

typedef struct s_envp
{
	char			*var;
	char			*value;
	int				exported;
	int				val_set;
	struct s_envp	*next;
}					t_envp;

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
	char		pwd[PATH_MAX];
	char		oldpwd[PATH_MAX];
	char		pathname[PATH_MAX];
	char		*line;
	t_envp		*envp_ll;
}				t_vars;

#endif
