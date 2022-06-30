#include <minishell.h>

int	opt_strlst(t_btree *root, t_lenlist **len_curr)
{
	int			i;
	static int	flag;

	if (root->node->type == E_VALID_FILE
			|| root->node->type == E_VALID_BUILTIN
			|| root->node->type == E_WORD)
	{
		i = ft_length_lst(root->node->tokenlst);
		if (!flag)
		{
			(*len_curr)->length = i;
			flag = 1;
		}
		return (0);
	}
	if (root->node->type == E_PIPE)
	{
		*len_curr = (*len_curr)->next;
		flag = 0;
	}
	return (0);
}
