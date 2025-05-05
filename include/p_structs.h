/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_structs.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fschnorr <fschnorr@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 13:26:20 by fschnorr          #+#    #+#             */
/*   Updated: 2025/05/05 01:07:44 by fschnorr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef P_STRUCTS_H

# define P_STRUCTS_H

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
	TOKEN_OR,
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

#endif