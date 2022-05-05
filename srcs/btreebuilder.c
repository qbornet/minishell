#include "minishell.h"

int	is_redirection(int type)
{
	if (type == E_GREAT
		|| type == E_LESS
		|| type == E_DGREAT
		|| type == E_DLESS)
		return (1);
	return (0);
}

void	next_step(char **envp, t_btree *root, t_tokenlist **lst)
{
	if (!is_redirection(root->node->type)
		&& (root->node->type == E_WORD
		|| (root->right && root->right->node->type == E_WORD)))
	{
		if (root && root->right && root->right->node->type == E_WORD)
			check_cmd(root->right->node, envp);
		else
			check_cmd(root->node, envp);
		*lst = (*lst)->next;
		while (*lst && (*lst)->token->type == E_WORD)
			*lst = (*lst)->next;
	}
	else
	{
		if (root->right && root->right->left)
		{
			check_cmd(root->right->node, envp);
			*lst = (*lst)->next;
			while (*lst && (*lst)->token->type == E_WORD)
				*lst = (*lst)->next;
		}
		else
		{
			if (root->right && is_redirection(root->node->type))
			{
				root->right->node->type = E_FD;
				root->right->node->tokenlst->token->type = E_FD;
			}
			*lst = (*lst)->next;
		}
	}
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

	input = "> outfile0 > outfile1 > outfile2 ls -a && (echo hello > outfile3 || echo tata > outfile4)";
	lexical_analysis(input, &lst);
	if (!lst)
		return (0);
	root = buildbtree(envp, lst);
	ft_treeprint(root, 0);
	/*
	root = root->left;
	if (!root)
	{
		printf("no leaf here\n");
	}
	else
	{
		token = root->node->token;
		printf("lex : %s\nlen: %lu\ntype: %d\n", token->lex, token->len, token->type);
	}
	*/
	while (lst)
	{
		tmp = lst;
		lst = lst->next;
		free(tmp->token);
		free(tmp);
	}
	//printf("-------------\nlex = %s\nlen = %lu\n-------------\n", root->node->token->lex, root->node->token->len);
}
