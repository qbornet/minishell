#include "ast.h"

int	ft_lstexist(t_strlist **s_curr, char *str)
{
	char		*compare;
	t_strlist	*strlst;

	strlst = *s_curr;
	while (strlst)
	{
		compare = strlst->data;
		if (!ft_strncmp(compare, str, ft_strlen(str)))
				return (1);
		wordlst = strlst->next;
	}
	return (0);
}

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
	ft_create_lst(tokenlst->next, &strlst->next);
}

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

int	ft_read_flow(t_btree *tree, t_strlist **s_curr)
{
	int			res;
	t_strlist	*strlst;

	strlst = *s_curr;
	if (tree && tree->node)
	{
		if (tree->node->type == E_VALID_CMD)
			ft_recreate_str(tree->node->tokenlst, &strlst);
		if (ft_read_flow(tree->left) < 0)
			return (-1);
		res = ft_find_redirection(tree)
		if (res)
		{
			ft_reverse_list(&wordlist);
			if (ft_redirection(tree, res) < 0)
				return (-1);
		}
		else if (ft_find_logical(tree))
			ft_reverse_list(&wordlist);
	}
	return (0);
}
