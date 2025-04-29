#ifndef T_VARS_FWD_H

typedef struct s_vars	t_vars;

#define T_VARS_FWD_H
#endif

#ifndef EXECUTION_H
# define EXECUTION_H

# include "structs.h"

//executor
void	executor(t_vars *vars);
int		execute_ast(t_vars *vars, t_ast_node *current_node, int in_fd, int out_fd);
int		execute_command(t_vars *vars, struct s_command *curr_command_node, int in_fd, int out_fd);
int		run_executable(t_vars *vars, struct s_command *curr_command_node, int in_fd, int out_fd);
int		search_executable(t_vars *vars, char *command, char *pathname);
int		search_env_path(t_vars *vars, char *command, char *pathname);
int		operator_or(t_vars *vars, t_ast_node *current_node, int in_fd, int out_fd);
int		operator_and(t_vars *vars, t_ast_node *current_node, int in_fd, int out_fd);
int		operator_pipe(t_vars *vars, t_ast_node *current_node, int in_fd, int out_fd);
int		search_env_path(t_vars *vars, char *command, char *pathname);

//redirections
int		parse_redirections(t_vars *vars, struct s_command *current_command_node, int *in_fd, int *out_fd);

//builtins
int		run_echo(int fd, char **argv);
int		run_pwd(int fd, char **argv);
int		run_cd(t_vars *vars, char **argv);
int		run_export(t_vars *vars, char **argv, int fd);
int		run_env(t_vars *vars, char **argv, int fd);
int		run_unset(t_vars *vars, char **argv);
int		run_exit(t_vars *vars, char **argv, int in_fd, int out_fd, int parent);
int		check_exit_parent(t_vars *vars);

//utils
void	close_fds(int in_fd, int out_fd);
int		chdir_error(char *path, int errornumber);
int		execution_error(char *command, char *errmsg, int errornumber);
void	fatal_error(t_vars *vars, char *errmsg);
int		env_error(char *command, char *errmsg);
int		env_fatal_error(t_vars *vars, char *command, char *errmsg, int fd);
void	free_env_paths(char **env_paths);

#endif
