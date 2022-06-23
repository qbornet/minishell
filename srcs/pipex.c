#include "minishell.h"

static int	get_cmd_tab(t_cmdblock *cmdblock, char **env)
{
	char	*path;
	char	**cmd;

	cmd = cmdblock->cmd;
	if (!*cmd)
		return (-1);
	path = get_path(env, cmd[0]);
	if (!path)
	{
		ft_putstr_fd(cmd[0], 2);
		ft_putendl_fd(": command not found", 2);
		free_str_tab(cmd, 0);
		return (-1);
	}
	free_str(cmd[0]);
	cmd[0] = path;
	cmdblock->cmd = cmd;
	return (0);
}

static int	exec_cmd(t_cmdblock *cmdblock, char **env)
{
	if (access((cmdblock->cmd)[0], X_OK) == -1)
	{
		perror((cmdblock->cmd)[0]);
		free_str_tab(cmdblock->cmd, 0);
		exit(127);
	}
	execve((cmdblock->cmd)[0], cmdblock->cmd, env);
	exit(0);
}

int	pipex(t_process *pr, char **envp, t_cmdblock *cmdblock)
{
	int	exec_code;

	if (g_exit_status == 130)
		exit(g_exit_status);
	exec_code = exec_builtin(cmdblock, envp);
	if (exec_code == 0)
		exit(0);
	else if (exec_code < 0)
	{
		free_pipes_pids(pr->pipes, pr->pids, cmdblock->len, -1);
		g_exit_status = 126;
		return (-1);
	}
	if (get_cmd_tab(cmdblock, envp) < 0)
	{
		free_pipes_pids(pr->pipes, pr->pids, cmdblock->len, -1);
		g_exit_status = 127;
		return (-1);
	}
	if (exec_cmd(cmdblock, envp) < 0)
	{
		free_pipes_pids(pr->pipes, pr->pids, cmdblock->len, -1);
		g_exit_status = 126;
		return (-1);
	}
	exit(0);
}
