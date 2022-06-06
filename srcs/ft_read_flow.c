#include <minishell.h>

static t_strlist	*ft_create_lst(t_tokenlist *tokenlst, t_strlist **s_curr)
{
	char		*str;
	t_strlist	*strlst;
	t_token		*token;

	if (!tokenlst)
		return (NULL);
	strlst = *s_curr;
	token = tokenlst->token;
	if (token && (token->type == E_AND_IF || token->type == E_PIPE
			|| token->type == E_OR_IF || token->type == E_GREAT
			|| token->type == E_DGREAT || token->type == E_LESS
			|| token->type == E_DLESS || token->type == E_EOI
			|| token->type == E_LBRACE || token->type == E_RBRACE))
		return (NULL);
	str = ft_create_str(token->lex, token->len);
	if (!str)
		return (ft_strclear(&strlst, &free));
	if (!strlst)
		strlst = ft_strlst_new(str, token->type);
	else
		ft_strlst_addback(&strlst, str, token->type);
	ft_create_lst(tokenlst->next, &strlst);
	return (strlst);
}

char	*ft_create_str(char *lex, size_t len)
{
	size_t	i;
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


int	ft_find_operator(t_btree *tree)
{
	if (tree && tree->node)
	{
		if (tree->node->type == E_GREAT || tree->node->type == E_DGREAT)
			return (1);
		else if (tree->node->type == E_AND_IF || tree->node->type == E_OR_IF)
			return (2);
		else if (tree->node->type == E_PIPE)
			return (3);
		else if (tree->node->type == E_LESS)
			return (4);
		else if (tree->node->type == E_DLESS)
			return (5);
	}
	return (0);
}

int	ft_read_flow(t_btree *tree, t_strlist **s_curr)
{
	int	res;

	res = 0;
	if (tree && tree->node)
	{
		if (ft_read_flow(tree->left, s_curr) < 0)
			return (-1);
		if (tree && (tree->node->type == E_VALID_BUILTIN
				|| tree->node->type == E_VALID_FILE
				|| tree->node->type == E_WORD))
		{
			*s_curr = ft_create_lst(tree->node->tokenlst, s_curr);
			if (!*s_curr)
				return (-1);
		}
		else if (tree && tree->node->type == E_ERROR)
			return (-1);
		res = ft_find_operator(tree);
		if (res)
			if (!tree->right)
				return (-1);
		if (ft_read_flow(tree->right, s_curr) < 0)
			return (-1);
	}
	return (0);
}

/*
void	print_tokenlst(t_tokenlist *tokenlst)
{
	printf("tokenlst: ");
	while (tokenlst)
	{
		printf("%p->", tokenlst);
		tokenlst = tokenlst->next;
	}
	printf("NULL\n");
}

void	print_strlst(t_strlist *strlst)
{
	printf("strlst: ");
	while (strlst)
	{
		printf("%s:%p->", (char *)strlst->data, strlst);
		strlst = strlst->next;
	}
	printf("NULL\n");
}


int	main(int ac, char **av)
{
	t_strlist	*strlst;
	t_tokenlist	*tokenlst;

	strlst = NULL;
	tokenlst = NULL;
	if (ac != 2)
		return (-1);
	lexical_analysis(av[1], &tokenlst);
	strlst = ft_create_lst(tokenlst, &strlst);
	print_strlst(strlst);
	print_tokenlst(tokenlst);
	ft_tokenclear(&tokenlst, &free);
	ft_strlstclear(&strlst, &free);
	return (0);
}
*/
