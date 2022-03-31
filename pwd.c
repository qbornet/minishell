#include "bin.h"

int	ft_pwd(void)
{
	char	*cwd;

	cwd = getcwd(NULL, PATH_MAX);
	if (cwd)
		return (printf("%s\n", cwd));
}
