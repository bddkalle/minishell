/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fschnorr <fschnorr@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 16:35:38 by fschnorr          #+#    #+#             */
/*   Updated: 2025/03/05 17:05:21 by fschnorr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

											//	AST	//

typedef enum e_node_type
{
	NODE_COMMAND,
	NODE_PIPE,
	NODE_AND,
	NODE_OR,
	NODE_SUBSHELL,
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

											//	PARSER	//

typedef struct s_parser
{
	t_token	curr_tok;
}	t_parser;

										//	LEXER	//

typedef enum e_lexer_state
{
	NORMAL,
	IN_SINGLE_QUOTE,
	IN_DOUBLE_QUOTE,
	IN_VARIABLE,
}	t_lexer_state;

typedef enum e_token_type
{
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_REDIRECT_IN,
	TOKEN_REDIRECT_OUT,
	TOKEN_RIDIRECT_APPEND,
	TOKEN_HEREDOC,
	TOKEN_AND,
	TOKEN_OR,
	TOKEN_QUOTE,
	TOKEN_PARENT_LEFT,
	TOKEN_PARENT_RIGHT,
	TOKEN_VAR,
}	t_token_type;

typedef struct s_token
{
	t_token_type	type;
	char			*value;
	struct s_token	*next;
}					t_token;

typedef struct s_lexer
{
	t_lexer_state	state;
	t_token_type	curr_token_type;
	t_token			**next_node;
	char			*curr_token;
	char			c;
	int				token_pos;
	int				line_pos;
}					t_lexer;

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
	t_prompt	*prompt;
	t_lexer		*lexer;
	t_token		*token;
	t_parser	*parser;
	char		*line;
} 				t_vars;

#endif