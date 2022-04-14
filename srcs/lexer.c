#include "lexer.h"

void	set_token(char *input, t_token *token)
{
	token->lex = input;
	token->id = 0;
	if (is_eoi(*input, token))
		token->len = 0;
	else if (is_token_2(input, token))
		token->len = 2;
	else if (is_token_1(input, token))
		token->len = 1;
	else
		word_token(input, token);
}

t_token	*get_next_token(char **input)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	set_token(*input, token);
	*input += token->len;
	while (**input == ' ')
		*input += 1;
	if (token->id)
		return (token);
	return (NULL);
}

void	lexer(char *input, t_tokenlist **lst)
{
	t_token		*token;
	t_tokenlist	*node;

	token = get_next_token(&input);
	if (!token)
		return ;
	*lst = NULL;
	while (token->id != E_EOI)
	{
		node = ft_tokennew(token);
		if (!node)
			return ;
		if (!*lst)
			*lst = node;
		else
			ft_tokenadd_back(lst, node);
		token = get_next_token(&input);
		if (!token)
			return ;
	}
	node = ft_tokennew(token);
	if (!node)
		return ;
	ft_tokenadd_back(lst, node);
}

int	main(void)
{
	char		*input;
	t_tokenlist	*lst;

	input = "monmo||onnai( ssee&&ttoitco)mmentc ava>>p < lutot <<biene< ttoia;sdfjas;dfjaspdfji                   world && Hello Bob";
	if (!input)
		return (-1);
	lexer(input, &lst);
	while (lst)
	{
		printf("lex : %s\nlen : %ld\nid %d\n-------------------------------\n", lst->token->lex, lst->token->len, lst->token->id);
		lst = lst->next;
	}
	return (0);
}
