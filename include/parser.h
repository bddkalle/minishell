/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdahne <cdahne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 13:26:20 by fschnorr          #+#    #+#             */
/*   Updated: 2025/05/05 14:33:25 by cdahne           ###   ########.fr       */
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
void			free_tmp_argv(char ***argv);
void			free_parser_cmd_node(t_vars *vars);

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
void			syntax_error_double_quote(t_vars *vars);
t_size			is_parameter(t_vars *vars);
void			get_parameter(t_vars *vars, char *parameter);
void			expand_parameter(t_vars *vars);
void			expand_exit_status(t_vars *vars);
void			substitute_parameter(t_vars *vars, char *substitute);
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
t_ast_node		*parse_or_and(t_vars *vars);
t_ast_node		*parse_factor(t_vars *vars);
t_ast_node		*parse_command(t_vars *vars);
t_node_type		set_op_type(t_token_type type);
t_size			current_token_is(char *s, t_vars *vars);
void			advance_token(t_vars *vars);
t_redir			*handle_redirs(t_vars *vars);
void			fill_cmd_argv(t_vars *vars);
void			fill_argv(t_vars *vars, char **argv, t_size i);
int				continue_argv(t_vars *vars, int word_count, char ***argv);
void			reclassification(t_vars *vars);
void			remove_quotes(t_vars *vars);
t_size			remove_quotes_from_string(t_vars *vars, char **s, char c);
int				quote_is_closed(char *s, int i);
void			check_syntax(t_vars *vars);
void			check_redir_syntax(t_vars *vars);
void			handle_consecutive_op(t_vars *vars, t_token *curr_tok);
t_size			is_invalid_leading_op(t_token_type type);
t_size			is_consecutive_op(t_token_type type);
void			handle_syntax_error(t_vars *vars, t_token *tok);
int				closing_par(t_vars *vars, t_token *curr_tok);
t_size			is_op2(t_token_type type);
t_size			is_redir_op(t_token_type type);
t_size			is_redirexh_op(t_token_type type);

//Heredoc
int				heredoc_setup(t_vars *vars, t_token *target, \
				char *redir_target);
t_tempfile		*open_heredoc_dialog(t_vars *vars, char *delimiter);
void			start_substitution(t_vars *vars, char **substitute, \
				char *parameter);
t_size			is_var_included(char **pline);

//Debugging
void			debug_lexer(t_vars *vars);
void			debug_parser(t_vars *vars);
int				print_ast_node(t_ast_node *curr_node, int nodenum);
int				print_subshell_node(t_ast_node *curr_node, int nodenum);

#endif
