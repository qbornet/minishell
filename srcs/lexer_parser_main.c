#include <minishell.h>

int	lexer_parser_main(char *input, char **envp, t_data **d_curr)
{
	t_data	*frame;

	frame = *d_curr;
	if (lexical_analysis(input, &frame->tokenlst) < 0)
		return (-1);
	if (g_exit_status)
	{
		ft_perror(NULL);
		return (0);
	}
	frame->root = buildbtree(envp, frame->tokenlst);
	if (!frame->root)
		return (-1);
	if (ft_read_flow(frame->root, &frame->strlst) < 0)
	{
		g_exit_status = 506;
		ft_perror(NULL);
		*d_curr = frame;
		return (g_exit_status);
	}
	*d_curr = frame;
	return (0);
}

/*
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
		printf("%s%p[type:%d][s_id:%d]->", (char *)strlst->data, strlst, strlst->type, strlst->s_id);
		strlst = strlst->next;
	}
	printf("NULL\n");
}

int	main(int ac, char **av, char **envp)
{
	t_data	*frame;
	t_strlist *lst;

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
	lst = frame->strlst;
	while (lst)
	{
		lst = starexp(&lst, frame, 1);
		lst = lst->next;
	}
	lst = frame->strlst;
	printf("\n");
	printf("\n");
	while (lst->next)
	{
		printf("%s ", (char *)(lst->data));
		lst = lst->next;
	}
	printf("%s ", (char *)(lst->data));
	printf("\n");
	while (lst)
	{
		printf("%s ", (char *)(lst->data));
		lst = lst->prev;
	}
	printf("\n");
	printf("\n");
	print_strlst(frame->strlst);
	ft_free_parser_error(&frame);
	return (0);
}
*/
