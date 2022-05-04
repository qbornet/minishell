#include <minishell.h>

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
	char		*input;
	t_btree		*root;
	t_strlist	*strlst;
	t_tokenlist	*lst;
	t_tokenlist	*tmp;

	(void)ac;
	(void)av;

	input = "echo hello || echo hi";
	lexical_analysis(input, &lst);
	if (!lst)
		return (-1);
	root = buildbtree(envp, lst);
	//printf("root: %p\n", root);
	ft_treeprint(root, 0);
	ft_read_flow(root, &strlst);
	print_strlst(strlst);
	while (lst)
	{
		tmp = lst;
		lst = lst->next;
		free(tmp->token);
		free(tmp);
	}
	return (0);
}
