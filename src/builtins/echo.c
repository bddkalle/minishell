#include "../../include/minishell.h"

int	run_echo(int fd, char **argv)
{
	int	linebreak;
	char	*s;

	(void)fd;
	linebreak = 1;
	while (*++argv && ft_strcmp(*argv, "-n") == 0)
		linebreak = 0;
	while (*argv)
	{
		s = *argv;
		while (*s)
			if (write (fd, s++, 1) == -1)
				return (0);
		argv++;
		if (*argv)
			write (fd, " ", 1);
	}
	if (linebreak)
		write(fd, "\n", 1);
	return (1);
}
