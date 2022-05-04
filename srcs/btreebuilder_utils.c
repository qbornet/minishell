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

int	is_word_or_brace(int type)
{
	if (type == E_WORD || type == E_LBRACE || type == E_RBRACE)
		return (1);
	return (0);
}

void	btree_addnode(t_btree **root, t_tokenlist **lst)
{
	t_btree	*leaf;

	if (!*root)
		return ;
	leaf = ft_newleaf(*lst);
	if (!leaf)
		return ;
	if (!is_word_or_brace(leaf->node->type))
	{
		leaf->left = *root;
		*root = leaf;
	}
	else
	{
		if (is_word_or_brace((*root)->node->type))
		{
			leaf->left = *root;
			*root = leaf;
		}
		else
		{
			if (!(*root)->right)	
				(*root)->right = leaf;
			else
			{
				leaf->left = (*root)->right;
				(*root)->right = leaf;
			}
		}
	}
}
