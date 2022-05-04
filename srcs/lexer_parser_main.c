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

	input = "echo hello || echo hi";
	(void)ac;
	(void)av;
	root = buildbtree(input, envp);
	printf("root: %p\n", root);
	ft_treeprint(root, 0);
	ft_read_flow(root, &strlst);
	print_strlst(strlst);
	return (0);
}
