#include "minishell.h"

int	ft_varlen(char *s)
{
	char *tmp;

	if (!s)
		return (0);
	tmp = s;
	while (*s && *s != '=')
		s++;
	return (s - tmp);
}

char	*check_var_env(char **env, char *var_name)
{
	if (!env)
		return (NULL);
	while (*env && ft_strncmp(*env, var_name, ft_varlen(*env)))
		env++;
	return (*env);
}

void	expand(char *to_expand)
{
}

int	main(int ac, char **av, char **env)
{
	(void)env;
	(void)av;
	(void)ac;
	char	*result;
	char	*s = "$NOM ! Pseudo : $PSEUDO.";

	result = varexp(s, env);
	printf("%s\n", result);
	return (-1);
}
