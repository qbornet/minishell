#include "lexer.h"

size_t	is_eoi(char c, t_token *token)
{
	if (!c)
		token->type = E_EOI;
	return (token->type);
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
	token->type  = E_WORD;
}

size_t	is_token_1(char *input, t_token *token)
{
	if (*input == '>')
		token->type  = E_GREAT;
	else if (*input == '<')
		token->type  = E_LESS;
	else if (*input == '(')
		token->type  = E_LBRACE;
	else if (*input == ')')
		token->type  = E_RBRACE;
	return (token->type);
}

size_t	is_token_2(char *input, t_token *token)
{
	if (!ft_strncmp("&&", input, 2))
		token->type  = E_AND_IF;
	else if (!ft_strncmp("||", input, 2))
		token->type  = E_OR_IF;
	else if (!ft_strncmp("<<", input, 2))
		token->type  = E_DLESS;
	else if (!ft_strncmp(">>", input, 2))
		token->type  = E_DGREAT;
	return (token->type);
}
