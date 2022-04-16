#include "lexer.h"

void	set_token(char *input, t_token *token)
{
	token->lex = input;
	token->type = 0;
	if (is_eoi(*input, token))
		token->len = 0;
	else if (is_token_2(input, token))
		token->len = 2;
	else if (is_token_1(input, token))
		token->len = 1;
	else if (*input == ' ')
		sep_token(input, token);
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
	/*
	while (**input == ' ')
		(*input)++;
	*/
	if (token->type)
		return (token);
	return (NULL);
}

t_token	*get_first_token(char **input)
{
	t_token	*token;

	token = NULL;
	while (token == NULL)
	{
		token = get_next_token(input);
		if (!token)
			return (NULL);
		if (token->type == E_ASSIGNMENT_WORD)
		{
			free(token);
			token = NULL;
		}
	}
	return (token);
}

void	lexer(char *input, t_tokenlist **lst)
{
	t_token		*token;
	t_tokenlist	*newlst;

	*lst = NULL;
	token = get_first_token(&input);
	if (!token)
		return ;
	while (token->type != E_EOI)
	{
		newlst = ft_tokennew(token);
		if (!newlst)
			return ;
		ft_tokenadd_back(lst, newlst);
		token = get_next_token(&input);
		if (!token)
			return ;
	}
	newlst = ft_tokennew(token);
	if (!newlst)
		return ;
	ft_tokenadd_back(lst, newlst);
}

/*
int	main(void)
{
	char		*input;
	t_tokenlist	*lst;
	t_tokenlist *tmp;

	input = "monmo||onnai( ssee&&ttoitco)mmentc ava>>p < lutot <<biene< ttoia;sdfjas;dfjaspdfji                   world && Hello Bob";
	if (!input)
		return (-1);
	lexer(input, &lst);
	while (lst)
	{
		tmp = lst;
		printf("lex : %s\nlen : %ld\ntype %d\n-------------------------------\n", lst->token->lex, lst->token->len, lst->token->type);
		lst = lst->next;
		free(tmp->token);
		free(tmp);
	}
	return (0);
}
*/
