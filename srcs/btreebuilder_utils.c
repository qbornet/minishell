#include "minishell.h"

t_btree	*ft_newbtree(t_nodes *node)
{
	t_btree	*btree;

	btree = ft_calloc(1, sizeof(t_btree));
	if (!btree)
		return (NULL);
	btree->node = node;
	return (btree);
}

t_nodes	*ft_newnodes(t_tokenlist *lst)
{
	t_nodes	*node;

	node = ft_calloc(1, sizeof(t_nodes));
	if (!node)
		return (NULL);
	node->tokenlst = lst;
	if (!lst)
		return (node);
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
	{
		free(node);
		return (NULL);
	}
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
		if (!(*root)->right && !is_word_or_brace((*root)->node->type)
			&& (*root)->node->type != E_VALID_BUILTIN
			&& (*root)->node->type != E_VALID_FILE)
		{
			(*root)->right = ft_newleaf(NULL);
			if (!(*root)->right)
			{
				free(leaf->node);
				free(leaf);
				return ;
			}
			(*root)->right->node->type = E_CONTINUE;
		}
		if (!(*root)->left && !is_word_or_brace((*root)->node->type)
			&& (*root)->node->type != E_VALID_BUILTIN
			&& (*root)->node->type != E_VALID_FILE
			&& !is_redirection((*root)->node->type))
		{
			(*root)->left = ft_newleaf(NULL);
			if (!(*root)->left)
			{
				free(leaf->node);
				free(leaf);
				return ;
			}
			(*root)->left->node->type = E_ERROR;
		}
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
