#include <minishell.h>

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

static int	ft_strlst_len(t_btree *root, t_lenlist **len_curr)
{
	if (root && root->node)
	{
		if (ft_strlst_len(root->left, len_curr) < 0)
			return (-1);
		opt_strlst(root, len_curr);
		if (ft_strlst_len(root->right, len_curr) < 0)
			return (-1);
	}
	return (0);
}

int	ft_length_lst(t_tokenlist *tokenlst)
{
	int	i;

	i = 0;
	while (tokenlst)
	{
		if (tokenlst->token->type == E_WORD
				|| tokenlst->token->type == E_VALID_FILE
				|| tokenlst->token->type == E_VALID_BUILTIN)
			i++;
		if (tokenlst->token->type == E_PIPE
				|| tokenlst->token->type == E_EOI)
			break ;
		tokenlst = tokenlst->next;
	}
	return (i);
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
	while (tmp)
	{
		ft_lenadd_back(&lenlst, 0);
		tmp--;
	}
	(*d_curr)->lenlst = lenlst;
	(*d_curr)->cmd_pool = ft_calloc((total_cmd + 1), sizeof(char **));
	if (!(*d_curr)->cmd_pool)
		return (-1);
	lenlst = (*d_curr)->lenlst;
	if (ft_strlst_len((*d_curr)->root, &(*d_curr)->lenlst) < 0)
		return (-1);
	(*d_curr)->lenlst = lenlst;
	if (ft_create_cmd(d_curr, total_cmd) < 0)
		return (-1);
	return (0);
}
