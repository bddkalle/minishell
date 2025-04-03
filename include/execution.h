#ifndef EXECUTION_H
# define EXECUTION_H

# include "structs.h"
# include <linux/limits.h>

//executor
void	executor(t_vars *vars);
int	execute_ast(t_vars *vars, t_ast_node *current_node);
int	run_executable(t_vars *vars, struct s_command *curr_command_node);
int	operator_or(t_vars *vars, t_ast_node *current_node);
int	operator_and(t_vars *vars, t_ast_node *current_node);
int	operator_pipe(t_vars *vars, t_ast_node *current_node);

//builtins
int	run_echo(int fd, char **argv);
int	run_pwd(int fd, char **argv);
int	run_cd(t_vars *vars);

//error
void	chdir_error(char *path);
int		execution_error(char *command, char *errmsg);
void	fatal_error(t_vars *vars, char *errmsg);

#endif
