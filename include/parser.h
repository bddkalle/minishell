/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fschnorr <fschnorr@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 13:26:20 by fschnorr          #+#    #+#             */
/*   Updated: 2025/04/29 23:44:06 by fschnorr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H
# define OPERATOR "|<>&()"
# define MULT_OP "|<>&"
# define CONSEC_OP "|&"
# define QUOTES "'\""
# define DEL " \t\n"


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
				t_size token_pos);
void			create_token(t_vars *vars);
t_size			is_whitespace(char c);
t_size			char_is(char *s, char c);
t_size			is_op(t_vars *vars);
t_size			is_mult_op(t_vars *vars);
t_size			is_valid_mult_op(char c, t_vars *vars);
t_token_type	token_identifier(t_vars *vars);
t_size			token_cof_digits(char *s);
void			handle_quoted_input(t_vars *vars);
void			handle_single_qt(t_vars *vars);
void			handle_double_qt(t_vars *vars);
t_size			is_parameter(t_vars *vars);
void			expand_parameter(t_vars *vars);
void			expand_exit_status(t_vars *vars);
t_size			is_valid_name(char c);
void			handle_operator(t_vars *vars);
void			handle_whitespace(t_vars *vars);
void			handle_quotes(t_vars *vars);
void			delimit_operator(t_vars *vars);
void			handle_eoi(t_vars *vars);
void			fill_token(t_vars *vars);

//Parser
void			parser(t_vars *vars);
t_ast_node		*parse_expression(t_vars *vars);
t_ast_node		*parse_factor(t_vars *vars);
t_ast_node		*parse_command(t_vars *vars);
t_size			current_token_is(char *s, t_vars *vars);
void			advance_token(t_vars *vars);
t_redir			*handle_redirs(t_vars *vars);
void			fill_cmd_argv(t_vars *vars);
void			reclassification(t_vars *vars);
void			remove_quotes(t_vars *vars);
void			check_syntax(t_vars *vars);
t_size			is_invalid_leading_op(t_token_type type);
t_size			is_consecutive_op(t_token_type type);



//Debugging
void			debug_lexer(t_vars *vars);
void			debug_parser(t_vars *vars);
int				print_ast_node(t_ast_node *curr_node, int nodenum);
int				print_subshell_node(t_ast_node *curr_node, int nodenum);

#endif