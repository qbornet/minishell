#include "ast.h"

t_strlist	*ft_strlst_new(void *data, enum e_token type)
{
	t_strlist	*new;

	if (!data)
		return (NULL);
	new = ft_calloc(1, sizeof(t_wordlist));
	if (!new)
		return (NULL);
	new->data = data;
	new->type = type;
	return (new);
}

int	ft_strlst_addback(t_strlist **lst_curr, void *data, enum e_token type)
{
	t_strlist	*head;

	if (!lst_curr)
		return (-1);
	head = *lst_curr;
	if (!head)
	{
		*lst_curr = ft_wordlst_new(data);
		if (!*lst_curr)
			return (-1);
	}
	while (head->next)
		head = head->next;
	head->next = ft_wordlst_new(data);
	if (!head->next)
		return (-1);
	head->next->type = type;
	head->next->prev = head;
	return (0);
}
