/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_structs.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fschnorr <fschnorr@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 13:26:20 by fschnorr          #+#    #+#             */
/*   Updated: 2025/04/08 11:52:03 by fschnorr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef T_AST_NODE_FWD

typedef struct s_ast_node	t_ast_node;
typedef struct s_redir 		t_redir;

# define T_AST_NODE_FWD
#endif

#ifndef P_STRUCTS_H
# define P_STRUCTS_H

# include "minishell.h"
# include "structs.h"

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
	TOKEN_REDIRECT_APPEND,
	TOKEN_HEREDOC,
	TOKEN_AND,
	TOKEN_AND_SYNER,
	TOKEN_OR,
	TOKEN_OR_SYNER,
	TOKEN_QUOTE,
	TOKEN_PARENT_LEFT,
	TOKEN_PARENT_RIGHT,
	TOKEN_VAR,
	TOKEN_IO_NUMBER,
	TOKEN_EXIT_STATUS,
	TOKEN,
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
	t_size			token_pos;
	t_size			line_pos;
}					t_lexer;

											//	PARSER	//

typedef struct s_parser
{
	t_token		*curr_tok;
	t_ast_node	*node;
	t_redir		**next_redir_node;
	t_size			tok_pos;
}	t_parser;

#endif