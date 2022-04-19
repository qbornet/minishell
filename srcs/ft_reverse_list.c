/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_reverse_list.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbornet <qbornet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 13:45:13 by qbornet           #+#    #+#             */
/*   Updated: 2022/04/19 14:52:17 by qbornet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ast.h"

static void	ft_swap(void *a, void *b, size_t size)
{
	size_t			i;
	unsigned char	*p;
	unsigned char	*q;
	unsigned char	temp;

	if (!a || !b || size <= 0)
		return ;

	i = 0;
	p = a;
	q = b;
	while (i < size)
	{
		temp = p[i];
		p[i] = q[i];
		q[i] = temp;
		i++;
	}
}

void	ft_reverse_list(t_wordlist **lst_curr)
{
	t_wordlist	*tmp;
	t_wordlist	*head;
	
	head = *lst_curr;
	tmp = head;
	while (tmp->next)
		tmp = tmp->next;
	while (tmp->prev && head->next && tmp != head)
	{
		ft_swap(head->data, tmp->data, sizeof(void *));
		head = head->next;
		tmp = tmp->prev;
	}
}

/*
void	ft_printlst(t_wordlist **w_curr)
{
	t_wordlist	*wordlist;

	wordlist = *w_curr;
	while (wordlist)
	{
		printf("%s->", (char *)wordlist->data);
		wordlist = wordlist->next;
	}
	printf("NULL\n");
}

int	main(void)
{
	char	str1[10] = "Hello";
	char	str2[10] = "World";
	t_wordlist	*wordlist = ft_wordlst_new(str1);

	ft_wordlst_addback(&wordlist, str2);
	ft_printlst(&wordlist);
	ft_reverse_list(&wordlist);
	ft_printlst(&wordlist);
	return (0);
}
*/
