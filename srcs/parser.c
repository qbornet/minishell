#include "lexer.h"
#include "parser.h"

//Tools
void	ft_print_tokenlist(t_tokenlist *lst)
{
	t_tokenlist *tmp;

	while (lst)
	{
		tmp = lst;
		printf("lex : %s\nlen : %ld\ntype %d\n-------------------------------\n", lst->token->lex, lst->token->len, lst->token->type);
		lst = lst->next;
		free(tmp->token);
		free(tmp);
	}
}
//

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

void	ft_nodedelone(t_nodes *node)
{
	free(node->token);
	free(node);
}

t_nodes	*ft_newnodes(t_token *token)
{
	t_nodes	*node;	
	
	node = malloc(sizeof(t_nodes));
	if (!node)
		return (NULL);
	node->type = token->type;
	node->token = token;
	return (node); 
}

t_btree	*ft_newleaf(t_token *token)
{
	t_nodes	*node;
	t_btree *btree;

	node = ft_newnodes(token);
	if (!node)
		return (NULL);
	btree = ft_newbtree(node);
	if (!btree)
		return (NULL);
	return (btree);
}

void	btree_addnode(t_btree **root, t_tokenlist **lst)
{
	t_btree		*leaf;

	leaf = ft_newleaf((*lst)->token);
	if (!leaf)
		return ;
	if (*root && ((*root)->node->type == E_WORD
			|| ((*root)->left && (*root)->right)))
	{
		leaf->left = *root;
		*root = leaf;
		while ((*lst)->token->type == E_WORD)
			*lst = (*lst)->next;
	}
	else
	{
		if (*root && !(*root)->left)
			(*root)->left = leaf;	
		else if (*root && !(*root)->right)
			(*root)->right = leaf;
	}
}

t_btree	*ft_buildtree(char *input)
{
	t_tokenlist	*lst;
	t_btree 	*root;
	//t_leaf		*leaf;
	//t_btree	*tmp;

	lexer(input, &lst);
	if (!lst)
		return (NULL);
	return (NULL);
	root = ft_newleaf(lst->token);
	if (!root)
		return (NULL);
	while (lst->token->type != E_EOI)
	{
		btree_addnode(&root, &lst);
		if (!root)
			return (NULL);
		lst = lst->next;
	}
	return (root);
}

/*
int main(void)
{
	char	*input;
	t_btree	*root;

	input = "Hello               A=toto worlds && Hello la pluie";
	root = ft_buildtree(input);
	//ft_treeprint(root, 0);
	printf("%s\nlen = %lu\n\n", root->node->token->lex, root->node->token->len);
	printf("%s\nlen = %lu\n", root->left->node->token->lex, root->left->node->token->len);
}
*/
