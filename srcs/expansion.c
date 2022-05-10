#include <minishell.h>

static int	ft_var(char *str, char **var_pool)
{
	int	i;

	i = 0;
	while (var_pool[i])
		i++;
	var_pool[i] = ft_strdup(str);
	if (!var_pool[i])
		return (-1);
	return (0);
}

static void	ft_search_expansion(t_data **d_curr)
{
	char		*str;
	t_data		*frame;
	t_strlist	*s;

	frame = *d_curr;
	frame->var_pool = (char **)ft_calloc(4096, sizeof(char *));
	s = frame->strlst;
	if (!frame->var_pool)
		return ;
	while (s)
	{
		str = s->data;
		if (str && ft_strchr(str, '=') && !s->prev)
		{
			if (ft_var(str, frame->var_pool) < 0)
				return ;
			else
			{
				free(s->data);
				s->data = NULL;
			}
		}
		s = s->next;
	}
	ft_move_node(&frame, &frame->strlst);
}


int	start_expansion(t_data **d_curr)
{
	t_data	*frame;

	frame = *d_curr;
	ft_search_expansion(d_curr);
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
			return (NULL);
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
	ft_strclear(&frame->strlst, &free);
	ft_tokenclear(&frame->tokenlst, &free);
	ft_treeclear(frame->root, &free);
	for (int i = 0; frame->envp[i]; i++)
	{
		free(frame->envp[i]);
		if (frame->var_pool[i])
			free(frame->var_pool[i]);
	}
	free(frame->envp);
	free(frame->var_pool);
	free(frame);
	return (0);
}
