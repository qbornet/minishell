/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btreebuilder_utils_0.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfrancai <jfrancai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 11:27:07 by jfrancai          #+#    #+#             */
/*   Updated: 2022/06/25 13:04:05 by jfrancai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_btree	*ft_newbtree(t_nodes *node)
{
	t_btree	*btree;

	btree = ft_calloc(1, sizeof(t_btree));
	if (!btree)
		return (NULL);
	btree->node = node;
	return (btree);
}

t_nodes	*ft_newnodes(t_tokenlist *lst)
{
	t_nodes	*node;

	node = ft_calloc(1, sizeof(t_nodes));
	if (!node)
		return (NULL);
	node->tokenlst = lst;
	if (!lst)
		return (node);
	node->token = node->tokenlst->token;
	node->type = node->token->type;
	return (node);
}

t_btree	*ft_newleaf(t_tokenlist *lst)
{
	t_nodes	*node;
	t_btree	*btree;

	node = ft_newnodes(lst);
	if (!node)
		return (NULL);
	btree = ft_newbtree(node);
	if (!btree)
	{
		free(node);
		return (NULL);
	}
	return (btree);
}

int	is_word_or_brace(int type)
{
	if (type == E_WORD || type == E_LBRACE || type == E_RBRACE)
		return (1);
	return (0);
}

void	btree_addnode(t_btree **root, t_tokenlist **lst)
{
	t_btree	*leaf;

	if (!*root)
		return ;
	leaf = ft_newleaf(*lst);
	if (!leaf)
		return ;
	if (!is_word_or_brace(leaf->node->type))
		return (ft_not_word_or_brace(&leaf, root));
	else
		return (ft_word_or_brace(&leaf, root));
}
