#include "ast.h"

char	*ft_create_str(char *lex, size_t len)
{
	int		i;
	char	*str;

	i = 0;
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	while (i < len)
		str[i++] = *lex++;
	str[i] = '\0';
	return (str);
}

void	*ft_create_lst(t_tokenlist *tokenlst, t_strlist **s_curr)
{
	char		*str;
	t_strlist	*strlst;
	t_token		*token;

	strlst = *s_curr;
	token = tokenlst->token;
	if (!token)
		return ;
	if (token && token->type == E_AND_IF
		|| token->type == E_OR_IF || token->type == E_GREAT
		|| token->type == E_DGREAT || token->type == E_LESS
		|| token->type == E_DLESS)
		return ;
	str = ft_create_str(token->lex, token->len);
	if (!str)
		return ;
	if (!strlst)
		strlst = ft_strlst_new(str, token->type);
	else
		ft_strlst_addback(&strlst, str, token->type);
	ft_create_lst(tokenlst->next, &strlst);
}

int	ft_find_operator(t_btree *tree)
{
	if (tree && tree->node)
	{
		if (tree->node->type == E_GREAT || tree->node->type == E_DGREAT)
			return (1);
		else if (tree->node->type == E_LESS)
			return (2);
		else if (tree->node->type == E_DLESS)
			return (3);
		else if (tree->node->type == E_AND_IF || tree->node->type == E_OR_IF)
			return (4);
	}
	return (0);
}

int	ft_read_flow(t_btree *tree, t_strlist **s_curr)
{
	int	res;

	res = 0;
	if (tree && tree->node)
	{
		if (tree->node->type == E_VALID_BUILTIN || tree->node->type == E_VALID_FILE)
			ft_recreate_str(tree->node->tokenlst, s_curr);
		if (ft_read_flow(tree->left) < 0)
			return (-1);
		res = ft_find_operator(tree);
		if (res)
			if (!tree->right)
				return (-1);
	}
	return (0);
}
