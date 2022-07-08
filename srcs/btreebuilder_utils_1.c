/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btreebuilder_utils_1.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfrancai <jfrancai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 12:27:12 by jfrancai          #+#    #+#             */
/*   Updated: 2022/06/25 12:45:02 by jfrancai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ft_word_or_brace(t_btree **leaf, t_btree **root)
{
	if (is_word_or_brace((*root)->node->type))
	{
		(*leaf)->left = *root;
		*root = *leaf;
	}
	else
	{
		if (!(*root)->right)
			(*root)->right = *leaf;
		else
		{
			(*leaf)->left = (*root)->right;
			(*root)->right = *leaf;
		}
	}
}

static int	check_0(t_btree **root)
{
	if (!(*root)->right && !is_word_or_brace((*root)->node->type)
		&& (*root)->node->type != E_VALID_BUILTIN
		&& (*root)->node->type != E_VALID_FILE)
		return (1);
	return (0);
}

static int	check_1(t_btree **root)
{
	if (!(*root)->left && !is_word_or_brace((*root)->node->type)
		&& (*root)->node->type != E_VALID_BUILTIN
		&& (*root)->node->type != E_VALID_FILE
		&& !is_redirection((*root)->node->type))
		return (1);
	return (0);
}

void	ft_not_word_or_brace(t_btree **leaf, t_btree **root)
{
	if (check_0(root))
	{
		(*root)->right = ft_newleaf(NULL);
		if (!(*root)->right)
		{
			free((*leaf)->node);
			free(*leaf);
			return ;
		}
		(*root)->right->node->type = E_CONTINUE;
	}
	if (check_1(root))
	{
		(*root)->left = ft_newleaf(NULL);
		if (!(*root)->left)
		{
			free((*leaf)->node);
			free(*leaf);
			return ;
		}
		(*root)->left->node->type = E_ERROR;
	}
	(*leaf)->left = *root;
	*root = *leaf;
}
