/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fschnorr <fschnorr@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 13:26:20 by fschnorr          #+#    #+#             */
/*   Updated: 2025/03/25 16:41:03 by fschnorr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H
# define OPERATOR "|<>&()$"
# define QUOTES "'\""

# include "minishell.h"
# include "structs.h"

//Init
void			init_lexer(t_vars *vars);
void			init_parser(t_vars *vars);
void			init_parse_command(t_vars *vars);

//Free & Close
void			free_null_token(t_vars	*vars);
void			free_parser(t_vars *vars);
void			close_parser(t_vars *vars);
void			free_ast_node(t_ast_node **curr_node);

//Lexer
void			lexer(t_vars *vars);
t_lexer_state	lexer_state(t_vars *vars, char c, t_lexer_state state, \
							int token_pos);
void			create_token(t_vars *vars);
int				is_whitespace(char c);
int				char_is(char *s, char c);
int				is_valid_op(char c, t_vars *vars);
int				is_quo_char(char c);

//Parser
void			parser(t_vars *vars);
t_ast_node		*parse_expression(t_vars *vars);
t_ast_node		*parse_command(t_vars *vars);
int				current_token_is(char *s, t_vars *vars);
void			advance_token(t_vars *vars);
t_redir			*handle_redirs(t_vars *vars);
void			fill_cmd_argv(t_vars *vars);

//Debugging
void			debug_lexer(t_vars *vars);
void			debug_parser(t_vars *vars);
int				print_ast_node(t_ast_node *curr_node, int nodenum);

#endif