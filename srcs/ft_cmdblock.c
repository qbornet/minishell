#include <minishell.h>
static t_cmdblock	*ft_newblock(char **cmd)
{
	t_cmdblock	*cmdblk;

	cmdblk = ft_calloc(1, sizeof(t_cmdblock));
	if (!cmdblk)
		return (NULL);
	cmdblk->cmd = cmd;
	return (cmdblk);
}

void	ft_cmdclear(t_cmdblock **cmd_curr)
{
	t_cmdblock	*tmp;
	t_cmdblock	*cmdblk;

	cmdblk = *cmd_curr;
	while (cmdblk)
	{
		tmp = cmdblk;
		cmdblk = cmdblk->next;
		free(tmp);
	}
}

int	ft_blockadd_back(t_cmdblock **cmd_curr, char **cmd)
{
	t_cmdblock	*cmdblk;

	cmdblk = *cmd_curr;
	if (!cmdblk)
	{
		cmdblk = ft_newblock(cmd);
		if (!cmdblk)
			return (-1);
		*cmd_curr = cmdblk;
		return (0);
	}
	while (cmdblk->next)
		cmdblk = cmdblk->next;
	cmdblk->next = ft_newblock(cmd);
	if (!cmdblk->next)
		return (-1);
	return (0);
}

