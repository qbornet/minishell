#include <minishell.h>

t_lenlist	*ft_lennew(int data)
{
	t_lenlist	*lenlst;

	lenlst = malloc(sizeof(t_lenlist));
	if (!lenlst)
		return (NULL);
	lenlst->length = data;
	lenlst->next = NULL;
	return (lenlst);
}

void	ft_lenclear(t_lenlist **len_curr)
{
	t_lenlist	*tmp;
	t_lenlist	*lenlst;

	lenlst = *len_curr;
	while (lenlst)
	{
		tmp = lenlst;
		lenlst = lenlst->next;
		free(tmp);
	}
	*len_curr = NULL;
}

void	ft_lenadd_back(t_lenlist **len_curr, int data)
{
	t_lenlist	*lenlst;

	lenlst = *len_curr;
	if (!lenlst)
	{
		lenlst = ft_lennew(data);
		if (!lenlst)
			return ;
		*len_curr = lenlst;
		return ;
	}
	while (lenlst && lenlst->next)
		lenlst = lenlst->next;
	lenlst->next = ft_lennew(data);
}
