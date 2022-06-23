#include "minishell.h"

int	exec_builtin(t_cmdblock *cmdblock, t_data **frame)
{
	if (!ft_strcmp("echo", cmdblock->cmd[0]))
		return (ft_echo(cmdblock));
	if (!ft_strcmp("cd", cmdblock->cmd[0]))
		ft_cd((*frame)->cmdblk, (*frame)->envp);
	if (!ft_strcmp("pwd", cmdblock->cmd[0]))
		return (ft_pwd());
	if (!ft_strcmp("export", cmdblock->cmd[0]))
		ft_export((*frame)->cmdblk, &(*frame)->envp);
	if (!ft_strcmp("unset", cmdblock->cmd[0]))
		ft_unset((*frame)->cmdblk, &(*frame)->envp);
	if (!ft_strcmp("env", cmdblock->cmd[0]))
		return (ft_env((*frame)->envp));
	if (!ft_strcmp("exit", cmdblock->cmd[0]))
		ft_exit(0);
	return (1);
}
