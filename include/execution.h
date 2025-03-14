#ifndef EXECUTION_H
# define EXECUTION_H

# include "structs.h"
# include <linux/limits.h>

//executor
void	executor(t_vars *vars);

//builtins
int	run_echo(int fd, char **argv);
int	run_pwd(int fd, char **argv);
int	run_cd(t_vars *vars);

#endif
