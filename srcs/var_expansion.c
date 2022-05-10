#include "minishell.h"

char **is_local_var(char **vars, char *to_find)
{
	while (ft_strncmp(*vars, to_find, ft_strlen(to_find)))
		vars++;
	return (vars);
}

int	main(int ac, char **av, char **envp)
{
	(void)envp;
	if (ac != 2)
		return (-1);
	if (is_local_var(av, "toto"))
		return (0);
	else
		return (-1);
}
