#include <minishell.h>

int	ft_braces(t_btree **b_curr)
{
	static int	flag;
	t_btree		*root;

	root = *b_curr;
	if (root && root->node)
	{
		ft_braces(&root->left);
		if (root->node->type == E_LBRACE)
			flag = 1;
		else if (root->node->type == E_RBRACE)
			flag = 0;
		if (flag)
			root->node->braces = 1;
		ft_braces(&root->right);
	}
	return (0);
}
