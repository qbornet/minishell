#include <minishell.h>

int	ft_free_parser_error(t_data **d_curr)
{
	int		i;
	t_data	*frame;

	i = 0;
	frame = *d_curr;
	close(frame->std_fd.stdin);
	close(frame->std_fd.stdout);
	close(frame->std_fd.stderr);
	ft_strclear(&frame->strlst, &free);
	ft_treeclear(frame->root, &free);
	ft_tokenclear(&frame->tokenlst, &free);
	while (frame->envp[i])
		free(frame->envp[i++]);
	free(frame->envp);
	free(frame);
	return (-1);
}

int	lexer_parser_main(char *input, char **envp, t_data **d_curr)
{
	t_data	*frame;

	frame = *d_curr;
	lexical_analysis(input, &frame->tokenlst);
	frame->root = buildbtree(envp, frame->tokenlst);
	ft_treeprint(frame->root, 0);
	if (ft_read_flow(frame->root, &frame->strlst) < 0)
		return (ft_free_parser_error(&frame));
	*d_curr = frame;
	return (0);
}

// Juste pour tester la struct t_data
char	**ft_dup_envp(char **envp)
{
	int		i;
	char	**new_envp;

	i = 0;
	while (envp[i])
		i++;
	new_envp = (char **)ft_calloc(i + 1, sizeof(char *));
	if (!new_envp)
		return (NULL);
	i = 0;
	while (envp[i])
	{
		new_envp[i] = ft_strdup(envp[i]);
		i++;
	}
	return (new_envp);
}

void	print_strlst(t_strlist *strlst)
{
	printf("strlst: ");
	while (strlst)
	{
		printf("%s:%p->", (char *)strlst->data, strlst);
		strlst = strlst->next;
	}
	printf("NULL\n");
}

int	main(int ac, char **av, char **envp)
{
	t_data	*frame;

	if (ac != 2)
		return (-1);
	frame = ft_calloc(1, sizeof(t_data));
	frame->std_fd.stdin = dup(STDIN_FILENO);
	frame->std_fd.stdout = dup(STDOUT_FILENO);
	frame->std_fd.stderr = dup(STDERR_FILENO);
	frame->envp = ft_dup_envp(envp);
	if (!frame->envp)
		return (-1);
	if (lexer_parser_main(av[1], frame->envp, &frame) < 0)
		return (-1);
	print_strlst(frame->strlst);
	ft_free_parser_error(&frame);
	return (0);
}
