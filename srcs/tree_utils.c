#include "minishell.h"

static int free_ret(char *str)
{
	free(str);
	return (1);
}

/* Fonction qui free tout l'arbre
 * @param: tree
 * - L'arbre qu'ont veut free
 *
 * @param: (*del) (void *)
 * - Pointeur de fonction a utiliser si jamais on veut free notre node sinon NULL
 *
 * */

void	ft_treeclear(t_btree *tree, void (*del) (void *))
{
	if (tree)
	{
		ft_treeclear(tree->right, del);
		ft_treeclear(tree->left, del);
		del(tree->node);
		free(tree);
	}
}

/* Fonction pour print l'arbre
 * @param: tree
 * - L'arbre qu'ont veut print
 *
 * @param: type
 * - La maniere quond veut print (l'ordre quond va utiliser pour traverser l'arbre)
 *   0: Inorder (Left, Root (print), Right)
 *   1: Preorder (Root (print), Left, Right)
 *   2: Postorder (Left, Right, Root (print));
 * */

// on peut faire en sorte que a la place de print le numero de type genre 301, 302, ect.. on peut lui faire print la string du type,
// ex: E_WORD ou WORD
// envoie msg discord si tu veut je modifie la fonction et la fait print comme ca.
void	ft_treeprint(t_btree *tree, int type)
{
	static int	node_pos;

	if (tree && !type)
	{
		ft_treeprint(tree->left, type);
		printf("node %p[%d]:\n\e[20G-	type: %d\n\e[20G-	token: %p\n\n", tree, node_pos++, tree->node->type, tree->node->token);
		ft_treeprint(tree->right, type);
	}
	else if (tree && type == 1)
	{
		printf("node %p[%d]:\n\e[20G-	type: %d\n\e[20G-	token: %p\n\e[20G-	lex: %s\n\e[20G-	len: %zu\n\n", tree, node_pos++, tree->node->type, tree->node->token, tree->node->token->lex, tree->node->token->len);
		ft_treeprint(tree->left, type);
		ft_treeprint(tree->right, type);
	}
	else if (tree && type == 2)
	{
		ft_treeprint(tree->left, type);
		ft_treeprint(tree->right, type);
		printf("node %p[%d]:\n\e[20G-	type: %d\n\e[20G-	token: %p\n\e[20G-	lex: %s\n\e[20G-	len: %zu\n\n", tree, node_pos++, tree->node->type, tree->node->token, tree->node->token->lex, tree->node->token->len);
	}
}

void	ft_treesearch(t_btree *tree, char *to_find)
{
	int		ret;
	char	*str;

	if (tree && tree->node)
	{
		ret = ft_treesearch(tree->left, to_find);
		if (ret == 1)
		{
			if (ft_find_operator(tree) != 2 && ft_find_operator(tree) != 3)
				return (0);
			return (3);
		}
		else if (ret == 3)
			return (3);
		str = ft_create_str(tree->node->token->lex, tree->node->token->len);
		if (tree->node->type == E_WORD
			&& !ft_strncmp(str, to_find, ft_strlen(to_find)))
			return (free_ret(str));
		free(str);
		ret = ft_treesearch(tree->right, to_find);
		if (ret == 1)
			return (1);
		else if (ret == 3)
			return (3);
	}
	return (0);
}

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

/*

int	main(void)
{
	t_btree	*tree;

	tree = calloc(1, sizeof(t_btree));
	tree->node = calloc(1, sizeof(t_nodes));
	tree->node->type = E_WORD;
	tree->right = calloc(1, sizeof(t_btree));
	tree->right->node = calloc(1, sizeof(t_nodes));
	tree->right->node->type = E_ASSIGNMENT_WORD;
	tree->right->left = calloc(1, sizeof(t_btree));
	tree->right->left->node = calloc(1, sizeof(t_nodes));
	tree->right->left->node->type = E_DLESS;
	tree->left = calloc(1, sizeof(t_btree));
	tree->left->node = calloc(1, sizeof(t_nodes));
	tree->left->node->type = E_DGREAT;
	tree->left->left = calloc(1, sizeof(t_btree));
	tree->left->left->node = calloc(1, sizeof(t_nodes));
	tree->left->left->node->type = E_LESS;
	ft_treeprint(tree, 0);
	printf("----------------------\n\n");
	ft_treeprint(tree, 1);
	printf("----------------------\n\n");
	ft_treeprint(tree, 2);
	printf("----------------------\n\n");
	ft_treeclear(tree, &free);
	return (0);
}
*/
