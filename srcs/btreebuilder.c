#include "minishell.h"

void	next_step(char **envp, t_btree *root, t_tokenlist **lst)
{
	if (!(*lst))
		return ;
	if (!root->right)
		return ;
	if (root && root->right && root->node->type != E_GREAT
		&& root->node->type != E_LESS
		&& root->node->type != E_DLESS
		&& root->node->type != E_DGREAT
		&& (root->node->type == E_WORD
			|| (root->right && root->right->node->type == E_WORD)))
	{
		if (root && root->right && root->right->node->type == E_WORD)
			printf("Hello");
			//check_cmd(root->right->node->tokenlst, envp);
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
	/*
	while (lst && lst->token->type != E_EOI)
	{
		btree_addnode(&root, &lst);
		if (!root)
			return (NULL);
		next_step(envp, root, &lst);
	}
	*/
	return (root);
}
/*
int	main(int ac, char **av, char **envp)
{
	char	*input;
	t_btree	*root;
	t_token *token;

	(void)ac;
	(void)av;
	(void)token;
	input = "echo tata || (echo toto && echo titi)";
	root = buildbtree(input, envp);
	root = root->right->left;
	//ft_treeprint(root, 0);
	if (!root)
	{
		printf("no leaf here\n");
		return (0);
	}
	token = root->node->token;
	printf("lex : %s\nlen: %lu\ntype: %d\n", token->lex, token->len, token->type);
	//printf("-------------\nlex = %s\nlen = %lu\n-------------\n", root->node->token->lex, root->node->token->len);
}
*/
