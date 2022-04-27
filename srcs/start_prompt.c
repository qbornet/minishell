/* clang -Wall -Werror -Wextra -g3 start_prompt.c -lreadline */

#include "prompt.h"

void	ft_history(char *str)
{
	if (str && *str)
		add_history(str);
}

int	ft_check_tty(void)
{
	if (isatty(STDIN_FILENO) &&
		isatty(STDOUT_FILENO) && isatty(STDERR_FILENO))
		return (1);
	return (0);
}

/* J'ai ajouter des check tty pour pouvoir rentrer et utiliser,
 * les fonction genre readline a besoin d'avoir un tty,
 * j'ai aussi enlever le ft_endl car c'est de la merde et en plus,
 * c'est un enfer a essaye de comprendre le line_buffer de mort */

int	start_prompt(void)
{
	char	*temp;
	char	*str;

	temp = ttyname(STDOUT_FILENO);
	str = temp;
	if (temp)
		printf("tty %s\n\n", temp);
	while (str)
	{
		if (ft_check_tty())
		{
			str = readline(PROMPT);
			ft_history(str);
		}
		else
		{
			perror("Error tty");
			return (1);
		}
	}
	if (!temp)
		perror("Error tty");
	return (0);
}

int	main(void)
{
	start_prompt();
	return (0);
}
