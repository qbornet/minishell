#include "lexer.h"

size_t	is_eoi(char c, t_token *token)
{
	if (!c)
		token->id = E_EOI;
	return (token->id);
}

void	word_token(char *input, t_token *token)
{
	char	*tmp;

	tmp = input;
	while (*input && *input != ' ' && *input != '&'
		&& *input != '|'
		&& *input != '>'
		&& *input != '<'
		&& *input != ')'
		&& *input != '(')
		input++;
	token->len = input - tmp;
	token->id = E_WORD;
}

size_t	is_token_1(char *input, t_token *token)
{
	if (*input == '>')
		token->id = E_GREAT;
	else if (*input == '<')
		token->id = E_LESS;
	else if (*input == '(')
		token->id = E_LBRACE;
	else if (*input == ')')
		token->id = E_RBRACE;
	return (token->id);
}

size_t	is_token_2(char *input, t_token *token)
{
	if (!ft_strncmp("&&", input, 2))
		token->id = E_AND_IF;
	else if (!ft_strncmp("||", input, 2))
		token->id = E_OR_IF;
	else if (!ft_strncmp("<<", input, 2))
		token->id = E_DLESS;
	else if (!ft_strncmp(">>", input, 2))
		token->id = E_DGREAT;
	return (token->id);
}
