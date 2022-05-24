#include "minishell.h"
#include <sys/types.h>
#include <dirent.h>

void	starexp(void)
{

}

int	main(void)
{
	DIR		*dir;

	dir = opendir(".");
	readdir(dir);
	return (0);
}
