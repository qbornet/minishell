#include <minishell.h>

static size_t	ft_index_match(char **envp)
{
	size_t	index;

	index = 0;
	while (envp[index])
	{
		if (!ft_strncmp("_=", envp[index], 2))
			return (index);
		index++;
	}
	return (index);
}

static int	underscore_match(t_cmdblock *cmdblock, t_data **d_curr)
{
	int		i;
	char	*str;
	char	*path;
	t_data	*frame;

	if (!cmdblock || !cmdblock->cmd[0])
		return (0);
	frame = *d_curr;
	i = ft_index_match(frame->envp);
	if (g_exit_status)
		return (-1);
	path = get_path(frame->envp, cmdblock->cmd[0]);
	if (!path)
		return (-1);
	str = ft_strjoin("_=", path);
	if (!str)
	{
		free(path);
		return (-1);
	}
	free(path);
	free(frame->envp[i]);
	frame->envp[i] = str;
	return (0);
}

int	underscore(t_data **frame, t_process *pr)
{
	int			i;
	t_cmdblock	*cmdblock;

	i = -1;
	cmdblock = (*frame)->cmdblk;
	while (++i < pr->len_cmdb)
	{
		if (!check_builtin(cmdblock))
		{
			if (underscore_match(cmdblock, frame) < 0)
				return (0);
		}
		cmdblock = cmdblock->next;
	}
	return (0);
}
