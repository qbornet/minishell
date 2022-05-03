#include "minishell.h"

void	next_step(char **envp, t_btree *root, t_tokenlist **lst)
{
	if (root->node->type != E_GREAT
		&& root->node->type != E_LESS
		&& root->node->type != E_DLESS
		&& root->node->type != E_DGREAT
		&& (root->node->type == E_WORD
			|| (root->right && root->right->node->type == E_WORD)))
	{
		if (root->right && root->right->node->type == E_WORD)
			check_cmd(root->right->node->tokenlst, envp);
		else
			check_cmd(root->node->tokenlst, envp);
		*lst = (*lst)->next;
		while (*lst && (*lst)->token->type == E_WORD)
			*lst = (*lst)->next;
	}
	else
		*lst = (*lst)->next;
}

t_btree	*buildbtree(char *input, char **envp)
{
	t_tokenlist	*lst;
	t_btree		*root;

	lexical_analysis(input, &lst);
	if (!lst)
		return (NULL);
	root = ft_newleaf(lst);
	if (!root)
		return (NULL);
	next_step(envp, root, &lst);
	while (lst && lst->token->type != E_EOI)
	{
		btree_addnode(&root, &lst);
		if (!root)
			return (NULL);
		next_step(envp, root, &lst);
	}
	return (root);
}

int	main(int ac, char **av, char **envp)
{
	char	*input;
	t_btree	*root;

	(void)ac;
	(void)av;
	input = "echo toto > outfile > outfile1 > outfile2 > outfile3 || ./toto -a yalalallalalall";
	root = buildbtree(input, envp);
	ft_treeprint(root, 0);
	//printf("-------------\nlex = %s\nlen = %lu\n-------------\n", root->node->token->lex, root->node->token->len);
}
