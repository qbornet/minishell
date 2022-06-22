#include "minishell.h"

int	exec_builtin(t_cmdblock *cmdblock)
{
	if (!ft_strcmp("echo", cmdblock->cmd[0]))
		return (ft_echo(cmdblock));
	if (!ft_strcmp("cd", cmdblock->cmd[0]))
		return (0);
	if (!ft_strcmp("pwd", cmdblock->cmd[0]))
		return (0);
	if (!ft_strcmp("export", cmdblock->cmd[0]))
		return (0);
	if (!ft_strcmp("unset", cmdblock->cmd[0]))
		return (0);
	if (!ft_strcmp("env", cmdblock->cmd[0]))
		return (0);
	if (!ft_strcmp("exit", cmdblock->cmd[0]))
		return (0);
	return (1);
}
