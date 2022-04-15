#include "ast.h"

static int	ft_redirection(t_btree *tree, enum e_token type, t_termstd **curr_std)
{
	int			fd;
	int			new_fd;
	char		*str;
	t_termstd	*saved_fd;

	new_fd = 0;
	saved_fd = *curr_std;
	str = ft_recreate_str(tree->node->token->lex, tree->node->token->len);
	if (!str)
		return (-1);
	saved_fd->std_out_fd = dup(STDOUT_FILENO);
	if (type == E_DGREAT)
	{
		fd = open(str, O_WRONLY | O_CREAT | O_APPEND, 0644);
		free(str);
		if (fd == -1)
			return (-1);
		new_fd = dup2(fd, STDOUT_FILENO);
		close(fd);
		return (new_fd);
	}
	fd = open(str, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	free(str);
	if (fd == -1)
		return (-1);
	new_fd = dup2(fd, STDOUT_FILENO);
	close(fd);
	return (new_fd);
}

char	*ft_recreate_str(char *lex, int len)
{
	int		i;
	char	*str;
	
	i = 0;
	str = malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	while (i < len && *lex)
		str[i++] = *lex++;
	str[i] = '\0';
	return (str);
}

int	ft_go_preorder(t_btree *tree, (int *f) (t_btree *tree))
{
	int	res;

	if (tree)
	{
		res = f(tree);
		if (res < 0)
			return (res);
		ft_go_preorder(tree->left);
		ft_go_preorder(tree->right);
	}
	return (0);
}

/* Fonctionne que pour les GREAT STDOUT_FILENO maintenant renvoie dans le fd de la redirection 
 * t_termstd doit recevoir les dup de 0, 1, 2 (STDOUT, STDIN, STDERR),
 * pour pouvoir remettre la bonne sortie une fois finie */

int	ft_find_great(t_btree *tree, t_termstd **saved)
{
	int	res;

	res = 0;
	if (tree)
	{
		if (!tree->node)
			return ;
		if (tree->node->type == E_GREAT
				|| tree->node->type == E_DGREAT)
		{
			res = ft_redirection(tree->right, tree->node->type, saved);
			if (res < 0)
				return (res);
			return (res);
		}
		ft_find_great(tree->left, saved);
		ft_find_great(tree->right, saved);
	}
	return (0);
}
