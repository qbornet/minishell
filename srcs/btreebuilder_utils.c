#include "minishell.h"

t_btree	*ft_newbtree(t_nodes *node)
{
	t_btree	*btree;

	btree = malloc(sizeof(btree));
	if (!btree)
		return (NULL);
	btree->left = NULL;
	btree->right = NULL;
	btree->node = node;
	return (btree);
}

t_nodes	*ft_newnodes(t_tokenlist *lst)
{
	t_nodes	*node;

	node = malloc(sizeof(t_nodes));
	if (!node)
		return (NULL);
	node->tokenlst = lst;
	node->token = node->tokenlst->token;
	node->type = node->token->type;
	return (node);
}

t_btree	*ft_newleaf(t_tokenlist *lst)
{
	t_nodes	*node;
	t_btree	*btree;

	node = ft_newnodes(lst);
	if (!node)
		return (NULL);
	btree = ft_newbtree(node);
	if (!btree)
		return (NULL);
	return (btree);
}

void	btree_addnode(t_btree **root, t_tokenlist **lst)
{
	t_btree	*leaf;

	if (!*root)
		return ;
	leaf = ft_newleaf(*lst);
	if (!leaf)
		return ;
	if ((*root)->node->type == E_WORD)
	{
		leaf->left = *root;
		*root = leaf;
	}
	else
	{
		if (!(*root)->right && leaf->node->type == E_WORD)
			(*root)->right = leaf;
		else
		{
			leaf->left = *root;
			*root = leaf;
		}
	}
}
