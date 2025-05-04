#ifndef T_VARS_FWD_H

typedef struct s_vars	t_vars;
typedef struct s_ast_node	t_ast_node;

#define T_VARS_FWD_H
#endif

#ifndef EXECUTION_H
# define EXECUTION_H

# include "e_structs.h"
# include "structs.h"

//executor
void	executor(t_vars *vars);
int		execute_ast(t_vars *vars, t_ast_node *current_node, int in_fd, int out_fd);
int		execute_command(t_vars *vars, struct s_command *curr_command_node, int in_fd, int out_fd);
int		run_executable(t_vars *vars, struct s_command *curr_command_node, int in_fd, int out_fd);
int		search_executable(t_vars *vars, char *command);
int		search_env_path(t_vars *vars, char *command);
int		operator_or(t_vars *vars, t_ast_node *current_node, int in_fd, int out_fd);
int		operator_and(t_vars *vars, t_ast_node *current_node, int in_fd, int out_fd);
int		operator_pipe(t_vars *vars, t_ast_node *current_node, int in_fd, int out_fd);
int		operator_subshell(t_vars *vars, t_ast_node *current_node, int in_fd, int out_fd);
int		search_env_path(t_vars *vars, char *command);

//redirections
int		parse_redirections(t_vars *vars, struct s_command *current_command_node, int *in_fd, int *out_fd);
//int		heredoc_redirection(t_vars *vars, char *delimiter, int old_in_fd);
int		heredoc_redirection(char *target, int old_in_fd);

//builtins
int		run_echo(int fd, char **argv);
int		run_pwd(int fd, char **argv);
int		run_cd(t_vars *vars, char **argv);
int		run_export(t_vars *vars, char **argv, int fd);
int		run_env(t_vars *vars, char **argv, int fd);
int		run_unset(t_vars *vars, char **argv);
int		run_exit_child(t_vars *vars, char **argv, int in_fd, int out_fd);
int		run_exit_parent(t_vars *vars, char **argv, int in_fd, int out_fd);

//utils
int			close_fds(int in_fd, int out_fd);
int			chdir_error(char *path, int errornumber);
int			execution_error(char *command, char *errmsg, int errornumber);
void		fatal_error(t_vars *vars, char *errmsg);
int			env_error(char *command, char *errmsg);
int			env_fatal_error(t_vars *vars, char *command, char *errmsg, int fd);
void		free_env_paths(char **env_paths);
void		free_close_tempfile(t_tempfile *tempfile);
t_tempfile	*create_tempfile(t_vars *vars);
char		*get_home(t_vars *vars);
void		update_oldpwd(t_vars *vars);
void		update_pwd(t_vars *vars);
int			within_long_long(char *str);
int			analyse_line(t_vars *vars, char **line, t_tempfile *tempfile, char *del);
void		expand_variables(t_vars *vars, char **pline, char *del);
int			del_is_quoted(char *del);


#endif
