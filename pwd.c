#include "bin.h"

void	ft_pwd(void)
{
	char	*cwd;

	cwd = getcwd(NULL, PATH_MAX);
	if (cwd)
		printf("%s\n", cwd);
	else
		printf("NULL\n");
}
