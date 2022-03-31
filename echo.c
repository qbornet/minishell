#include "bin.h"

void	ft_echo(char *s, int flag)
{
	if (!flag)
		printf("%s\n", s);
	else
		printf("%s", s);
}
