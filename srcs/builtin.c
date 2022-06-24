#include "minishell.h"

int	exec_builtin(t_cmdblock *cmdblock, t_data **frame)
{
	if (!cmdblock->cmd || !cmdblock->cmd[0])
		return (0);
	if (!ft_strcmp("echo", cmdblock->cmd[0]))
		return (ft_echo(cmdblock));
	if (!ft_strcmp("cd", cmdblock->cmd[0]))
		return (ft_cd((*frame)->cmdblk, (*frame)->envp));
	if (!ft_strcmp("pwd", cmdblock->cmd[0]))
		return (ft_pwd());
	if (!ft_strcmp("export", cmdblock->cmd[0]))
		return (ft_export((*frame)->cmdblk, &(*frame)->envp));
	if (!ft_strcmp("unset", cmdblock->cmd[0]))
		return (ft_unset((*frame)->cmdblk, &(*frame)->envp));
	if (!ft_strcmp("env", cmdblock->cmd[0]))
		return (ft_env((*frame)->envp));
	if (!ft_strcmp("exit", cmdblock->cmd[0]))
		return (ft_exit(0));
	return (2);
}
