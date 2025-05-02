#include "../../include/minishell.h"

int compare_digits(char *str, int negative)
{
	char		max[20];
	char		min[20];
	const char	*limit;
	int			i;

	ft_strlcpy(max, "9223372036854775807", 20);
	ft_strlcpy(min, "9223372036854775808", 20);
	if (negative)
		limit = min;
	else
		limit = max;
	i = 0;
	while (i < 19)
	{
		if (!ft_isdigit(str[i]))
			return (0);
		if (str[i] < limit[i])
			return (1);
		if (str[i] > limit[i])
			return (0);
		i++;
	}
	return (1);
}

int	within_long_long(char *str)
{
	int	negative;
	int	len;

	negative = 0;
	if (*str == '-')
	{
		negative = 1;
		str++;
	}
	else if (*str == '+')
		str++;
	while (*str == '0')
		str++;
	len = ft_strlen(str);
	if (len > 19)
		return (0);
	if (len < 19)
		return (1);
	return (compare_digits(str, negative));
}
