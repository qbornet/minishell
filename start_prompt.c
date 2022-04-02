#include "prompt.h"

/* ft_endl creer une nouvelle ligne pour readline
 * apres chaque commande entree*/

void	ft_endl(void)
{
	rl_replace_line("\n", 0);
	rl_redisplay();
	rl_redisplay();
	rl_on_new_line();
}

void	ft_history(char *str)
{
	if (str && *str)
		add_history(str);
}

/* temp existe juste pour rentrer dans le while, oui oui c'est overkill */

int	main(void)
{
	char	temp;
	char	*str;

	str = &temp;
	while (str)
	{
		str = readline(PROMPT);
		ft_history(str);
		ft_endl();
	}
	return (0);
}
