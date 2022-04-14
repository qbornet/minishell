#include "lexer.h"

size_t	is_eoi(char c, t_token *token)
{
	if (!c)
		token->id = EOI;
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
	token->id = WORD;
}

size_t	is_token_1(char *input, t_token *token)
{
	if (*input == '>')
		token->id = GREAT;
	else if (*input == '<')
		token->id = LESS;
	else if (*input == '(')
		token->id = LBRACE;
	else if (*input == ')')
		token->id = RBRACE;
	return (token->id);
}

size_t	is_token_2(char *input, t_token *token)
{
	if (!ft_strncmp("&&", input, 2))
		token->id = AND_IF;
	else if (!ft_strncmp("||", input, 2))
		token->id = OR_IF;
	else if (!ft_strncmp("<<", input, 2))
		token->id = DLESS;
	else if (!ft_strncmp(">>", input, 2))
		token->id = DGREAT;
	return (token->id);
}
