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
		if (root && root->right && root->right->node->type == E_WORD)
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

t_btree	*buildbtree(char **envp, t_tokenlist *lst)
{
	t_btree		*root;

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

/*
int	main(int ac, char **av, char **envp)
{
	char		*input;
	t_btree		*root;
	t_token 	*token;
	t_tokenlist	*lst;
	t_tokenlist	*tmp;

	(void)ac;
	(void)av;
	(void)token;

	input = "echo tata || (echo toto && echo titi)";
	lexical_analysis(input, &lst);
	if (!lst)
		return (0);
	root = buildbtree(envp, lst);
	ft_treeprint(root, 0);
	while (lst)
	{
		tmp = lst;
		lst = lst->next;
		free(tmp->token);
		free(tmp);
	}

	root = root->right->left;
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
