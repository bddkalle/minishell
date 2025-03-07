#include <cstdio>
#include <unistd.h>
int	run_cd(int fd, char **argv)
{
	char	*cwd;

	argv++;
	if (**argv == '/')
		if (chdir(**argv) == -1)
		{
			perror("const char *s")
			return (0);
		}
}
