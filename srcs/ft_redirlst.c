#include <minishell.h>

static t_redirlist	*ft_redirnew(char *str, enum e_token type)
{
	t_redirlist	*redirlst;
	
	redirlst = ft_calloc(1, sizeof(t_redirlist));
	if (!redirlst)
		return (NULL);
	redirlst->str = str;
	redirlst->type = type;
	return (redirlst);
}

void	ft_redirclear(t_redirlist **r_curr, void (*del) (void *))
{
	t_redirlist	*tmp;
	t_redirlist	*redirlst;

	redirlst = *r_curr;
	while (redirlst)
	{
		tmp = redirlst;
		del(redirlst->str);
		redirlst = redirlst->next;
		free(tmp);
	}
}

int	ft_rediradd_back(t_redirlist **r_curr, char *str, enum e_token type)
{
	t_redirlist	*redirlst;

	redirlst = *r_curr;
	if (!redirlst)
	{
		redirlst = ft_redirnew(str, type);
		if (!redirlst)
			return (-1);
		*r_curr = redirlst;
		return (0);
	}
	while (redirlst->next)
		redirlst = redirlst->next;
	redirlst->next = ft_redirnew(str, type);
	if (!redirlst->next)
		return (-1);
	return (0);
}
