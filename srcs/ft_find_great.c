#include "ast.h"

int	ft_lstexist(t_list **w_curr, char *str)
{
	char		*compare;
	t_wordlist	*wordlst;

	wordlst = *w_curr;
	while (wordlst)
	{
		compare = wordlst->content;
		if (!ft_strncmp(compare, str, ft_strlen(str)))
				return (1);
		wordlst = wordlst->next;
	}
	return (0);
}

void	*ft_recreate_str(t_token *token, t_wordlist **w_curr)
{
	int			i;
	int			len;
	char		*lex;
	char		*str;
	t_wordlist	*wordlst;

	i = 0;
	len = token->len;
	lex = token->lex;
	wordlst = *w_curr;
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	while (i < len && *lex)
		str[i++] = *len++;
	str[i] = '\0';
	if (!wordlst)
		wordlst = ft_wordlst_new(str);
	if (ft_lstexist(&wordlst, str))
	{
		free(str);
		return (NULL);
	}
	ft_wordlst_addback(&wordlst, str);
	return ((void *)command);
}

int	ft_go_preorder(t_btree *tree, int (*f) (t_btree *tree))
{
	int	res;

	if (tree)
	{
		res = f(tree);
		if (res < 0)
			return (res);
		ft_go_preorder(tree->left);
		ft_go_preorder(tree->right);
	}
	return (0);
}

//int	ft_here_doc()

int	ft_find_redirection(t_btree *tree)
{
	if (tree && tree->node)
	{
		if (tree->node->type == E_GREAT || tree->node->type == E_DGREAT)
			return (1);
		else if (tree->node->type == E_LESS)
			return (2);
	}
	return (0);
}

int	ft_read_flow(t_btree *tree, t_wordlist **w_curr)
{
	int			res;
	t_wordlist	*wordlist;

	wordlist = *w_curr;
	if (tree && tree->node)
	{
		if (tree->node->type == E_WORD)
			ft_recreate_str(tree->node->token);
		ft_read_flow(tree->left);
		res = ft_find_redirection(tree)
		if (res)
		{
			ft_reverse_list(wordlist);
			ft_redirection(tree, res);
		}
		else if (ft_find_logical(tree))
			ft_reverse_list(wordlist);
		ft_read_flow(tree->right);
	}
}
