/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_block.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfrancai <jfrancai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 11:27:18 by jfrancai          #+#    #+#             */
/*   Updated: 2022/06/25 11:27:19 by jfrancai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	insert_cmd(t_data **d_curr)
{
	size_t		i;
	char		***cpool;
	int			total_cmd;

	i = 0;
	total_cmd = (*d_curr)->total_cmd;
	cpool = (*d_curr)->cmd_pool;
	while (total_cmd--)
	{
		if (!cpool[i])
		{
			if (ft_blockadd_back(\
						&(*d_curr)->cmdblk, (*d_curr)->std_fd, NULL) < 0)
				return (-1);
		}
		else if (ft_blockadd_back(\
					&(*d_curr)->cmdblk, (*d_curr)->std_fd, cpool[i]) < 0)
			return (-1);
		i++;
	}
	return (0);
}

static int	opt_insert_filedes(t_btree *r, t_cmdblock **cmd_curr)
{
	char	*str;
	t_token	*token;

	if (r->node->type == E_GREAT || r->node->type == E_DGREAT
		|| r->node->type == E_LESS || r->node->type == E_DLESS)
	{
			if (r->right && r->right->node->type == E_FD)
				token = r->right->node->token;
			if (r->right->left && r->right->left->node->type == E_FD)
				token = r->right->left->node->token;
			str = ft_create_str(token->lex, token->len);
			if (!str)
				return (-1);
			if (ft_rediradd_back(&(*cmd_curr)->fd, str, r->node->type) < 0)
			{
				free(str);
				return (-1);
			}
	}
	return (0);
}

static int	insert_filedes(t_btree *r, t_cmdblock **cmd_curr)
{
	if (r && r->node)
	{
		if (insert_filedes(r->left, cmd_curr) < 0)
			return (-1);
		if (opt_insert_filedes(r, cmd_curr) < 0)
			return (-1);
		if (r->node->type == E_PIPE)
			*cmd_curr = (*cmd_curr)->next;
		if (insert_filedes(r->right, cmd_curr) < 0)
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
	if (insert_filedes((*d_curr)->root, &(*d_curr)->cmdblk) < 0)
		return (-1);
	(*d_curr)->cmdblk = tmp;
	return (0);
}
