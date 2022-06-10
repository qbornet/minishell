#include <minishell.h>

static int	insert_cmd(t_data **d_curr)
{
	size_t		i;
	char		***cpool;

	i = -1;
	cpool = (*d_curr)->cmd_pool;
	while (cpool[++i])
		if (ft_blockadd_back(&(*d_curr)->cmdblk, cpool[i]) < 0)
			return (-1);
	return (0);
}


static int	insert_outfile(t_btree *root, t_cmdblock **cmd_curr)
{
	char			*str;
	t_token			*token;

	if (root && root->node)
	{
		if (insert_outfile(root->left, cmd_curr) < 0)
			return (-1);
		if (root->node->type == E_GREAT || root->node->type == E_DGREAT)
		{
			if (root->right && root->right->node->type == E_FD)
				token = root->right->node->token;
			if (root->right->left && root->right->left->node->type == E_FD)
				token = root->right->left->node->token;
			str = ft_create_str(token->lex, token->len);
			if (!str)
				return (-1);
			if (ft_rediradd_back(&(*cmd_curr)->outfile, str, root->node->type) < 0)
				return (-1);
		}
		if (root->node->type == E_PIPE)
			*cmd_curr = (*cmd_curr)->next;
		if (insert_outfile(root->right, cmd_curr) < 0)
			return (-1);
	}
	return (0);
}

static int	insert_infile(t_btree *root, t_cmdblock **cmd_curr)
{
	char		*str;
	t_token		*token;

	if (root && root->node)
	{
		if (insert_infile(root->left, cmd_curr) < 0)
			return (-1);
		if (root->node->type == E_LESS || root->node->type == E_DLESS)
		{
			if (root->right && root->right->node->type == E_FD)
				token = root->right->node->token;
			if (root->right->left && root->right->left->node->type == E_FD)
				token = root->right->left->node->token;
			str = ft_create_str(token->lex, token->len);
			if (!str)
				return (-1);
			if (ft_rediradd_back(&(*cmd_curr)->infile, str, root->node->type) < 0)
				return (-1);
		}
		if (root->node->type == E_PIPE)
			*cmd_curr = (*cmd_curr)->next;
		if (insert_infile(root->right, cmd_curr) < 0)
			return (-1);
	}
	return (0);
}

int	command_block(t_data **d_curr)
{
	t_cmdblock	*tmp;

	if (insert_cmd(d_curr) < 0)
		return (-1);
	tmp = (*d_curr)->cmdblk;
	if (insert_outfile((*d_curr)->root, &(*d_curr)->cmdblk) < 0)
		return (-1);
	(*d_curr)->cmdblk = tmp;
	tmp = (*d_curr)->cmdblk;
	if (insert_infile((*d_curr)->root, &(*d_curr)->cmdblk) < 0)
		return (-1);
	(*d_curr)->cmdblk = tmp;
	return (0);
}
