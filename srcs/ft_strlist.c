#include <minishell.h>

t_strlist	*ft_strlst_new(void *data, enum e_token type)
{
	t_strlist	*new;

	if (!data)
		return (NULL);
	new = ft_calloc(1, sizeof(t_strlist));
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
		*lst_curr = ft_strlst_new(data, type);
		if (!*lst_curr)
			return (-1);
		return (0);
	}
	while (head->next)
		head = head->next;
	head->next = ft_strlst_new(data, type);
	if (!head->next)
		return (-1);
	head->next->prev = head;
	return (0);
}

void	*ft_strclear(t_strlist **s_curr, void (*del) (void *))
{
	t_strlist	*tmp;
	t_strlist	*strlst;

	strlst = *s_curr;
	while (strlst)
	{
		tmp = strlst;
		del(strlst->data);
		strlst = strlst->next;
		free(tmp);
	}
	*s_curr = NULL;
	return (NULL);
}
