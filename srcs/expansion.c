#include <minishell.h>

static int	ft_ret_opt(char *var_cmp, char *var_name, int index)
{
	free(var_cmp);
	free(var_name);
	return (index);
}

static int	ft_ret_index(char *str, char **var_pool)
{
	int		i;
	char	*var_cmp;
	char	*var_name;
	size_t	len;

	i = -1;
	len = ft_len_var(str);
	var_name = ft_substr(str, 0, len);
	if (!var_name)
		return (-2);
	while (var_pool[++i])
	{
		var_cmp = ft_substr(var_pool[i], 0, (ft_len_var(var_pool[i]) + 1));
		if (!var_cmp)
		{
			free(var_name);
			return (-2);
		}
		if (!ft_strncmp(var_cmp, var_name, ft_strlen(var_name)))
			return (ft_ret_opt(var_cmp, var_name, i));
		free(var_cmp);
	}
	return (-1);
}

static int	ft_var(char *str, char **var_pool)
{
	int	i;
	int	res;

	i = 0;
	res = ft_ret_index(str, var_pool);
	if (res == -2)
		return (-1);
	if (res >= 0)
	{
		free(var_pool[i]);
		var_pool[i] = ft_strdup(str);
		if (!var_pool[i])
			return (-1);
	}
	else
	{
		while (var_pool[i])
			i++;
		var_pool[i] = ft_strdup(str);
		if (!var_pool[i])
			return (-1);
	}
	return (0);
}

static int	ft_search_expansion(t_data **d_curr)
{
	char		*str;
	t_data		*frame;
	t_strlist	*s;

	frame = *d_curr;
	if (!frame->var_pool)
		frame->var_pool = (char **)ft_calloc(4096, sizeof(char *));
	s = frame->strlst;
	if (!frame->var_pool)
		return (ft_free_expan_error(&frame));
	while (s)
	{
		str = s->data;
		if (str && ft_strchr(str, '=') && (!s->prev || !s->prev->data))
		{
			if (ft_var(str, frame->var_pool) < 0)
				return (ft_free_expan_error(&frame));
			else
			{
				free(s->data);
				s->data = NULL;
			}
		}
		s = s->next;
	}
	return (0);
}

int	start_expansion(t_data **d_curr)
{
	t_data	*frame;

	frame = *d_curr;
	frame->logiclst = ft_lstnew(0);
	if (!frame->logiclst)
		return (ft_free_expan_error(&frame));
	if (ft_logic_lst(frame->root, &frame->logiclst) < 0)
		return (ft_free_expan_error(&frame));
	ft_search_expansion(&frame);
	ft_braces(&frame->root);
	ft_treeprint(frame->root, 0);
	return (0);
}


char	**ft_dup_envp(char **envp)
{
	int		i;
	char	**new_env;

	i = 0;
	while (envp[i])
		i++;
	new_env = (char **)ft_calloc(i + 1, sizeof(char *));
	if (!new_env)
		return (NULL);
	i = 0;
	while (envp[i])
	{
		new_env[i] = ft_strdup(envp[i]);
		if (!new_env[i])
		{
			i = 0;
			while (new_env[i])
				free(new_env[i++]);
			free(new_env);
			return (NULL);
		}
		i++;
	}
	return (new_env);
}

void	print_strlst(t_strlist **s_curr)
{
	t_strlist	*strlst;

	strlst = *s_curr;
	while (strlst)
	{
		printf("%s:%p->", (char *)strlst->data, strlst);
		strlst = strlst->next;
	}
	printf("NULL\n");
}

int	main(int ac, char **av, char **envp)
{
	int		i;
	t_data	*frame;

	if (ac != 2)
		return (-1);
	i = 0;
	frame = ft_calloc(1, sizeof(t_data));
	frame->std_fd.stdin = dup(STDIN_FILENO);
	frame->std_fd.stdout = dup(STDOUT_FILENO);
	frame->std_fd.stderr = dup(STDERR_FILENO);
	frame->envp = ft_dup_envp(envp);
	if (!frame->envp)
		return (-1);
	if (lexer_parser_main(av[1], frame->envp, &frame) < 0)
		return (-1);
	print_strlst(&frame->strlst);
	start_expansion(&frame);
	print_strlst(&frame->strlst);
	ft_free_expan_error(&frame);
	return (0);
}
