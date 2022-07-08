/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btreebuilder.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfrancai <jfrancai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 11:27:02 by jfrancai          #+#    #+#             */
/*   Updated: 2022/07/07 11:33:39 by jfrancai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	is_redirection(int type)
{
	if (type == E_GREAT
		|| type == E_LESS
		|| type == E_DGREAT
		|| type == E_DLESS)
		return (1);
	return (0);
}

static void	go_to_token(t_tokenlist **lst, enum e_token type)
{
	*lst = (*lst)->next;
	while (*lst && (*lst)->token->type == type)
		*lst = (*lst)->next;
}

static void	next_step(t_btree *root, t_tokenlist **lst)
{
	if (!is_redirection(root->node->type)
		&& (root->node->type == E_WORD
			|| (root->right && root->right->node->type == E_WORD)))
		go_to_token(lst, E_WORD);
	else
	{
		if (root->right && root->right->left)
			go_to_token(lst, E_WORD);
		else
		{
			if (root->right && is_redirection(root->node->type))
			{
				root->right->node->type = E_FD;
				root->right->node->tokenlst->token->type = E_FD;
			}
			*lst = (*lst)->next;
		}
	}
}

t_btree	*buildbtree(t_tokenlist *lst)
{
	t_btree		*root;

	root = ft_newleaf(lst);
	if (!root)
		return (NULL);
	next_step(root, &lst);
	while (lst && lst->token->type != E_EOI)
	{
		btree_addnode(&root, &lst);
		if (!root)
			return (NULL);
		next_step(root, &lst);
	}
	return (root);
}
