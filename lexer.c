#include "lexer.h"

void	*free_word(t_word *word)
{
	if (word->lex)
		free(word->lex);
	free(word);
	return (NULL);
}

t_word	*ft_newword(char *lex, int token)
{
	t_word	*newword;

	newword = malloc(sizeof(t_word));
	if (!newword)
		return (NULL);
	newword->lex = malloc(sizeof(char));
	if (!newword->lex)
	{
		free(newword);
		return (NULL);
	}
	(newword->lex)[0] = lex;
	newword->token = token;
	return (newword);
}

t_list	*lexer(char *input)
{
	char	*lex;
	t_word	*word;
	t_list	*lst;


	lex = malloc(sizeof(char));
	if (!lex)
		return (NULL);
	word = ft_newword(lex, INIT_TOKEN);
	if (!word)
	{
		free(lex);
		return (NULL);
	}	
	lst = ft_lstnew(word);
	if (!lst)
		return (free_word(word));

	while (*input)
	{
		// rule 1
		if (!*input && word->token == INIT_TOKEN)
		{
			word->token = END_OF_INPUT; 
			break;
		}
	}

	ft_lstclear(&lst, free);
	return ;
}

int	main(void)
{
	tokenize("hello world");
	return (0);
}
