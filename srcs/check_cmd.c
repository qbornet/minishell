#include "minishell.h"

bool	is_valid_builtin(t_token *token)
{
	if ((token->len == 4 && !ft_strncmp(token->lex, "echo", 4))
		|| (token->len == 2 && !ft_strncmp(token->lex, "cd", 2))
		|| (token->len == 3 && !ft_strncmp(token->lex, "pwd", 3))
		|| (token->len == 6 && !ft_strncmp(token->lex, "export", 6))
		|| (token->len == 5 && !ft_strncmp(token->lex, "unset", 5))
		|| (token->len == 3 && !ft_strncmp(token->lex, "env", 3))
		|| (token->len == 4 && !ft_strncmp(token->lex, "exit", 4)))
		return (true);
	return (false);
}

bool	is_valid_file(t_token *token, char **envp)
{
	char		*s;
	char		*path;
	bool		boolean;
	size_t		i;

	s = malloc(sizeof(char) * (token->len + 1));
	if (!s)
		return (false);
	i = -1;
	while (++i < token->len)
		s[i] = (token->lex)[i];
	s[i] = '\0';
	path = get_path(envp, s);
	if (path)
	{
		free(path);
		boolean = true;
	}
	else
		boolean = false;
	free(s);
	return (boolean);
}

bool	check_cmd(t_nodes *node, char **envp)
{
	if (is_valid_builtin(node->tokenlst->token))
	{
		node->tokenlst->token->type = E_VALID_BUILTIN;
		node->type = E_VALID_BUILTIN;
	}
	else if (is_valid_file(node->tokenlst->token, envp))
	{
		node->tokenlst->token->type = E_VALID_FILE;
		node->type = E_VALID_FILE;
	}
	return (true);
}
