#include "minishell.h"

// Upon successful return, this function return the number of characters printed (excluding the null byte used to end output to strings).
// If an output error is encountered, a negative value is returned.

int	ft_echo(const t_cmdblock *cmdblock)
{
	int		i;
	int		flag;
	char	**s;

	
	flag = 0;
	if (!ft_strcmp("-n", cmdblock->cmd[1]))
		flag++;
	dprintf("bite\n");
	if (flag && !cmdblock->cmd[2])
		return (0);
	if (!flag && !cmdblock->cmd[1])
	{
		printf("hello\n");
		write(1, "\n", 1);
		return (0);
	}
	i = 1;
	i += flag;
	s = cmdblock->cmd;
	while (s[i])
	{
		if (write(1, s[i], ft_strlen(s[i])) < 0)
			return (-2);
		i++;
		if (s[i])
			if (write(1, " ", 1) < 0)
				return (-3);
	}
	if (!flag)
		if (write(1, "\n", 1) < 0)
			return (-4);
	return (0);
}
