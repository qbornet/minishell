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

typedef struct s_strlist
{
	void				*data;
	enum e_token		type;
	struct s_strlist	*next;
	struct s_strlist	*prev;
}	t_strlist;

// a refaire les fonction t_wordlist en t_strlist refaire une fonction recreate_str
int			ft_wordlst_addback(t_strlist **lst_curr, void *data, enum e_token type);
int			ft_find_great(t_btree *tree, t_termstd **saved);
char		*ft_recreate_str(char *lex, int len);
t_strlist	*ft_wordlst_new(void *data, enum e_token type);
#endif
