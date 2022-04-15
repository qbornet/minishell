#ifndef AST_H
# define AST_H
# include <sys/stat.h>
# include <sys/types.h>
# include <fcntl.h>
# include <unistd.h>
# include "parser.h"

/* a init au debut du program pour avoir tout les bons fd */
typedef struct s_termstd
{
	int	std_out_fd;
	int	std_in_fd;
	int	std_err_fd;
}	t_termstd;

char	*ft_recreate_str(char *lex, int len);
int		ft_go_preorder(t_btree *tree, (int *f) (t_btree *tree));
int		ft_find_great(t_btree *tree, t_termstd **saved);
#endif
