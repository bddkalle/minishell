#ifndef EXECUTION_H
# define EXECUTION_H

# include "structs.h"

//executor
void	executor(t_vars *vars);
int	execute_ast(t_vars *vars, t_ast_node *current_node, int in_fd, int out_fd);
int	run_executable(t_vars *vars, struct s_command *curr_command_node, int in_fd, int out_fd);
int	search_executable(t_vars *vars, char *command, char *pathname);
int	search_env_path(char *command, char *pathname);
int	operator_or(t_vars *vars, t_ast_node *current_node, int in_fd, int out_fd);
int	operator_and(t_vars *vars, t_ast_node *current_node, int in_fd, int out_fd);
int	operator_pipe(t_vars *vars, t_ast_node *current_node, int in_fd, int out_fd);

//redirections
int	parse_redirections(t_vars *vars, struct s_command *current_command_node, int *in_fd, int *out_fd);

//builtins
int	run_echo(int fd, char **argv);
int	run_pwd(int fd, char **argv);
int	run_cd(t_vars *vars);

//error
void	chdir_error(char *path);
int		execution_error(char *command, char *errmsg);
void	fatal_error(t_vars *vars, char *errmsg);

#endif
