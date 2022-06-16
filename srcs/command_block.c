#include <minishell.h>

static int	insert_cmd(t_data **d_curr)
{
	size_t		i;
	char		***cpool;

	i = -1;
	cpool = (*d_curr)->cmd_pool;
	while (cpool[++i])
		if (ft_blockadd_back(\
					&(*d_curr)->cmdblk, (*d_curr)->std_fd, cpool[i]) < 0)
			return (-1);
	if (!cpool[0])
		if (ft_blockadd_back(\
					&(*d_curr)->cmdblk, (*d_curr)->std_fd, NULL) < 0)
			return (-1);
	return (0);
}

static int	insert_outfile(t_btree *r, t_cmdblock **cmd_curr)
{
	char			*str;
	t_token			*token;

	if (r && r->node)
	{
		if (insert_outfile(r->left, cmd_curr) < 0)
			return (-1);
		if (r->node->type == E_GREAT || r->node->type == E_DGREAT)
		{
			if (r->right && r->right->node->type == E_FD)
				token = r->right->node->token;
			if (r->right->left && r->right->left->node->type == E_FD)
				token = r->right->left->node->token;
			str = ft_create_str(token->lex, token->len);
			if (!str)
				return (-1);
			if (ft_rediradd_back(&(*cmd_curr)->outfile, str, r->node->type) < 0)
				return (-1);
		}
		if (r->node->type == E_PIPE)
			*cmd_curr = (*cmd_curr)->next;
		if (insert_outfile(r->right, cmd_curr) < 0)
			return (-1);
	}
	return (0);
}

static int	insert_infile(t_btree *r, t_cmdblock **cmd_curr)
{
	char		*str;
	t_token		*token;

	if (r && r->node)
	{
		if (insert_infile(r->left, cmd_curr) < 0)
			return (-1);
		if (r->node->type == E_LESS || r->node->type == E_DLESS)
		{
			if (r->right && r->right->node->type == E_FD)
				token = r->right->node->token;
			if (r->right->left && r->right->left->node->type == E_FD)
				token = r->right->left->node->token;
			str = ft_create_str(token->lex, token->len);
			if (!str)
				return (-1);
			if (ft_rediradd_back(&(*cmd_curr)->infile, str, r->node->type) < 0)
				return (-1);
		}
		if (r->node->type == E_PIPE)
			*cmd_curr = (*cmd_curr)->next;
		if (insert_infile(r->right, cmd_curr) < 0)
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
