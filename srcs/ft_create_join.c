#include <minishell.h>

static int	ft_lenlst_malloc(t_lenlist **len_curr, int length)
{
	if (!(*len_curr))
	{
		*len_curr = ft_lennew(length);
		if (!*len_curr)
			return (-1);
	}
	else
		ft_lenadd_back(len_curr, length);
	return (0);
}

static void	ft_cmd_node(t_btree *root, int *pipe_count)
{

	if (root && root->node)
	{
		ft_cmd_node(root->left, pipe_count);
		if (root->node->type == E_PIPE)
			*pipe_count += 1;
		ft_cmd_node(root->right, pipe_count);
	}
}

static int	ft_length_lst(t_tokenlist *tokenlst)
{
	int	i;

	i = 0;
	while (tokenlst)
	{
		if (tokenlst->token->type == E_PIPE
				|| tokenlst->token->type == E_EOI
				|| tokenlst->token->type == E_DGREAT
				|| tokenlst->token->type == E_DLESS
				|| tokenlst->token->type == E_GREAT
				|| tokenlst->token->type == E_LESS)
			break ;
		tokenlst = tokenlst->next;
		i++;
	}
	return (i);
}

static int	ft_strlst_len(t_btree *root, t_lenlist **len_curr)
{
	int			i;

	if (root && root->node)
	{
		if (ft_strlst_len(root->left, len_curr) < 0)
			return (-1);
		if (root->node->type == E_VALID_FILE
				|| root->node->type == E_VALID_BUILTIN
				|| root->node->type == E_WORD)
		{
			i = ft_length_lst(root->node->tokenlst);
			if (ft_lenlst_malloc(len_curr, i) < 0)
				return (-1);
			return (0);
		}
		if (ft_strlst_len(root->right, len_curr) < 0)
			return (-1);
	}
	return (0);
}

int	ft_create_join(t_data **d_curr)
{
	int			total_cmd;
	int			tmp;
	t_lenlist	*lenlst;
	
	total_cmd = 1;
	lenlst = (*d_curr)->lenlst;
	ft_cmd_node((*d_curr)->root, &total_cmd);
	(*d_curr)->total_cmd = total_cmd;
	tmp = total_cmd;
	while (--tmp)
		ft_lenadd_back(&lenlst, 0);
	(*d_curr)->lenlst = lenlst;
	(*d_curr)->cmd_pool = ft_calloc((total_cmd + 1), sizeof(char **));
	if (!(*d_curr)->cmd_pool)
		return (-1);
	if (ft_strlst_len((*d_curr)->root, &(*d_curr)->lenlst) < 0)
		return (-1);
	if (ft_create_cmd(d_curr, total_cmd) < 0)
		return (-1);
	return (0);
}
