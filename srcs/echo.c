#include "minishell.h"

// Upon successful return, this function return the number of characters
// printed (excluding the null byte used to end output to strings).
// If an output error is encountered, a negative value is returned.

static int	set_flag(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

static int	ft_echo_printer(char **s, int i, int flag)
{
	int	len;

	while (s[i])
	{
		if (!s[i][0])
			len = write(1, " ", 1);
		else
			len = write(1, s[i], ft_strlen(s[i]));
		if (len < 0)
			return (-2);
		i++;
		if (s[i] && len > 0)
			if (write(1, " ", 1) < 0)
				return (-3);
	}
	if (!flag)
		if (write(1, "\n", 1) < 0)
			return (-4);
	return (0);
}

int	ft_echo(const t_cmdblock *cmdblock)
{
	int		i;
	int		flag;

	flag = 0;
	i = 0;
	while (cmdblock->cmd[++i] && cmdblock->cmd[i][0] == '-'
		&& cmdblock->cmd[i][0] && cmdblock->cmd[i][1] == 'n')
		if (!set_flag(cmdblock->cmd[i] + 1))
			break ;
	if (i != 1)
		flag = 1;
	return (ft_echo_printer(cmdblock->cmd, i, flag));
}
