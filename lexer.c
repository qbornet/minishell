#include "lexer.h"

token	get_next_token(token *token)
{
	int		i;

	i = 0;
	while (input[i] != ' ' && input[i] != 0)
	{
		i++;
	}
	token
	return (
}

int	main(void)
{
	t_tokenlist	*lst;
	t_token		*token;
	char 		*input;

	input = ft_strdup("Hello world");
	token = get_next_token(input);
	if (!token)
	{
		printf("error\n");
	}
	ft_tokenadd_back(token);
	printf("token lex : %s\ntoken len : %d\ntoken id : %d", token.lex, token.len, token.id);
	free(input);

	return (0);
}
