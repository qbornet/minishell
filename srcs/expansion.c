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
	free(var_name);
	return (-1);
}

static int	ft_var(char *str, t_data **d_curr)
{
	int	res;

	res = ft_ret_index(str, (*d_curr)->envp);
	if (res == -2)
		return (-1);
	if (ft_check_pool(str, (*d_curr)->envp, res))
		return (1);
	res = ft_ret_index(str, (*d_curr)->var_pool);
	if (res == -2)
		return (-1);
	if (ft_check_pool(str, (*d_curr)->var_pool, res))
		return (1);
	return (0);
}

static int	ft_search_expansion(t_data **d_curr)
{
	char		*str;
	t_data		*frame;
	t_strlist	*s;

	frame = *d_curr;
	if (!frame->var_pool)
		frame->var_pool = ft_calloc(4096, sizeof(char *));
	s = frame->strlst;
	if (!frame->var_pool)
		return (ft_free_expan_error(&frame));
	while (s)
	{
		str = s->data;
		if (str && ft_strchr(str, '=') && (!s->prev || !s->prev->data))
		{
			if (ft_var(str, &frame) < 0)
				return (ft_free_expan_error(&frame));
			free(s->data);
			s->data = NULL;
		}
		s = s->next;
	}
	return (0);
}

int	start_expansion(t_data **d_curr)
{
	if (ft_search_expansion(d_curr) < 0)
		return (-1);
	ft_do_varexp(d_curr);
	if (ft_do_starexp(d_curr) < 0)
		return (ft_free_expan_error(d_curr));
	if (ft_create_join(d_curr) < 0)
		return (ft_free_expan_error(d_curr));
	if (command_block(d_curr) < 0)
		return (ft_free_expan_error(d_curr));
	return (0);
}


char	**ft_dup_envp(char **envp)
{
	int		i;
	char	**new_env;

	i = 0;
	while (envp[i])
		i++;
	new_env = ft_calloc((i + 2), sizeof(char *));
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
	new_env[i] = NULL;
	return (new_env);
}

void	print_strlst(t_strlist *strlst)
{

	printf("strlst: ");
	while (strlst)
	{
		printf("%s:%d->", (char *)strlst->data, strlst->s_id);
		strlst = strlst->next;
	}
	printf("NULL\n");
}

void	ft_get_word(t_data **d_curr, t_btree *root)
{
	if (root && root->node)
	{
		ft_get_word(d_curr, root->left);
		if (root->node->type == E_FD)
			(*d_curr)->str = ft_create_str(root->node->token->lex, root->node->token->len);
		ft_get_word(d_curr, root->right);
	}
}

int	main(int ac, char **av, char **envp)
{
	t_data	*frame;
	t_cmdblock	*cmdblk;
	t_redirlist	*redir;

	if (ac != 2)
		return (-1);
	frame = ft_calloc(1, sizeof(t_data));
	frame->std_fd = ft_calloc(1, sizeof(t_termstd));
	frame->std_fd->stdin = dup(STDIN_FILENO);
	frame->std_fd->stdout = dup(STDOUT_FILENO);
	frame->envp = ft_dup_envp(envp);
	if (!frame->envp)
		return (-1);
	if (lexer_parser_main(av[1], frame->envp, &frame) < 0)
		return (-1);
	//ft_treeprint(frame->root, 0);
	print_strlst(frame->strlst);
	start_expansion(&frame);
	print_strlst(frame->strlst);
	cmdblk = frame->cmdblk;
	while (cmdblk)
	{
		for (int i = 0; cmdblk->cmd[i]; i++)
			printf("[%d]: %s\n", i, cmdblk->cmd[i]);
		printf("std_fd:\e[20G	- stdin:%d\n\e[20G	- stdout:%d\n", cmdblk->std_fd->stdin, cmdblk->std_fd->stdout);
		printf("outfile: ");
		redir = cmdblk->outfile;
		while (redir)
		{
			printf("\e[20G	-[type: %d]:%s\n", redir->type, redir->str);
			redir = redir->next;
		}
		printf("\ninfile: ");
		redir = cmdblk->infile;
		while (redir)
		{
			printf("\e[20G	-[type: %d]:%s\n", redir->type, redir->str);
			redir = redir->next;
		}
		printf("\n");
		cmdblk = cmdblk->next;
	}
	ft_pipe(&frame, envp);
	ft_free_expan_error(&frame);
	return (0);
}
