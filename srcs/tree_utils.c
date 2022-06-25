/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfrancai <jfrancai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 11:30:20 by jfrancai          #+#    #+#             */
/*   Updated: 2022/06/25 12:18:17 by jfrancai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Fonction qui free tout l'arbre
 * @param: tree
 * - L'arbre qu'ont veut free
 *
 * @param: (*del) (void *)
 * - Pointeur de fonction a utiliser si jamais on veut free notre node sinon NULL
 *
 * */

void	ft_treeclear(t_btree *tree, void (*del) (void *))
{
	if (tree)
	{
		ft_treeclear(tree->right, del);
		ft_treeclear(tree->left, del);
		del(tree->node);
		free(tree);
	}
}
