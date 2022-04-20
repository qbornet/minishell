#ifndef AST_H
# define AST_H
# include "parser.h"
# include <sys/stat.h>
# include <sys/types.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>

/* a init au debut du program pour avoir tout les bons fd */
typedef struct s_termstd
{
	int	std_out_fd;
	int	std_in_fd;
	int	std_err_fd;
}	t_termstd;

typedef struct s_wordlist
{
	void				*data;
	enum e_token		type;
	struct s_wordlist	*next;
	struct s_wordlist	*prev;
}	t_wordlist;

int			ft_wordlst_addback(t_wordlist **lst_curr, void *data, enum e_token type);
int			ft_go_preorder(t_btree *tree, int (*f) (t_btree *tree));
int			ft_find_great(t_btree *tree, t_termstd **saved);
char		*ft_recreate_str(char *lex, int len);
t_wordlist	*ft_wordlst_new(void *data, enum e_token type);
#endif
