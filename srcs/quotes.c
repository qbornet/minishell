#include "minishell.h"

void	quotes_token(char **input, t_token *token)
{
	char	*tmp;

	tmp = *input;
	while (**input && token->qt)
	{
		if (**input == '\"' && token->qt == E_DOUBLE)
			token->qt = 0;
		if (**input == '\'' && token->qt == E_SINGLE)
			token->qt = 0;
		(*input)++;
	}
	token->len = *input - tmp;
}
