#include <minishell.h>

// Upon successful return, this function return the number of characters printed (excluding the null byte used to end output to strings).
// If an output error is encountered, a negative value is returned.

int	ft_echo(char *s, int flag)
{
	if (!flag)
		return (printf("%s\n", s));
	return (printf("%s", s));
}
