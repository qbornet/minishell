#include "ast.h"

static char	*ft_do_str(char *lex, int len)
{
	int		i;
	char	*str;

	i = 0;
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	while (i < len && *lex)
		str[i++] = *lex++;
	str[i] = '\0';
	return (str);
}

static int	ft_redirection_dgreat(char *str)
{
	int	fd;
	int	new_fd;

	fd = open(str, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (fd == -1)
		return (-1);
	free(str);
	new_fd = dup2(fd, STDOUT_FILENO);
	close(fd);
	return (new_fd);
}

static int	ft_redirection_great(t_btree *tree, enum e_token type)
{
	int		fd;
	int		new_fd;
	char	*str;

	str = ft_do_str(tree->node->token->lex, tree->node->token->len);
	if (!str)
		return (-1);
	if (type == E_DGREAT)
		return (ft_redirection_dgreat(str));
	fd = open(str, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	free(str);
	if (fd == -1)
		return (-1);
	new_fd = dup2(fd, STDOUT_FILENO);
	close(fd);
	return (new_fd);

}

static int	ft_redirection_less(t_btree *tree)
{
	int		fd;
	int		new_fd;
	char	*str;

	str = ft_do_str(str);
	if (!str)
		return (-1);
	fd = open(str, O_RDONLY);
	free(str);
	if (fd == -1)
	{
		print_error(E_FILE);
		return (-1);
	}
	new_fd = dup2(fd, STDIN_FILENO);
	close(fd);
	return (new_fd);
}

int	ft_redirection(t_btree *tree, int redirection)
{
	if (redirection == 1)
		return (ft_redirection_great(tree->right, tree->node->type));
	else if (redirection == 2)
		return (ft_redirection_less(tree->right));
	return (0);
}
