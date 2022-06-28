#include "minishell.h"

/* :0 */

void	ft_exit(t_data **d_curr, int status)
{
	char		*var;
	size_t		i;
	t_cmdblock	*cmdblk;

	i = 0;
	cmdblk = (*d_curr)->cmdblk;
	while (cmdblk->cmd[i])
	{
		var = ft_strdup(cmdblk->cmd[i]);
		if (!var)
			exit_group(d_curr);
		if (ft_strchr(var, '-'))
		{
			ft_putstr_fd("exit: no option for exit ", 2);
			ft_putendl_fd(var, 2);
			free(var);
			ft_free_all(d_curr);
			exit(2);
		}
		free(var);
		i++;
	}
	write(1, "exit\n", 5);
	ft_free_all(d_curr);
	exit(status);
}
