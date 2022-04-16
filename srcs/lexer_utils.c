#include "lexer.h"

size_t	is_eoi(char c, t_token *token)
{
	if (!c)
		token->type = E_EOI;
	return (token->type);
}

int	is_special_token(char c)
{
	if (c == '$'
		|| c == '&'
		|| c == '='
		|| c == '|'
		|| c == '>'
		|| c == '<'
		|| c == ')'
		|| c == '(')
		return (c);
	return (0);
}

void	word_token(char *input, t_token *token)
{
	char	*tmp;

	tmp = input;
	while (*input && *input != ' ' && !is_special_token(*input))
		input++;
	token->len = input - tmp;
	token->type  = E_WORD;
}

void	sep_token(char *input, t_token *token)
{
	char *tmp;

	tmp = input;
	while (*input == ' ')
		input++;
	token->len = input - tmp;
	token->type = E_SEP;
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
	else if (*input == '=')
		token->type = E_ASSIGNMENT_WORD;
	else if (*input == '$')
		token->type = E_EXPANSION;
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
