#ifndef MINISHELL_H
# define MINISHELL_H
# include <sys/stat.h>
# include <sys/types.h>
# include <limits.h>
# include <fcntl.h>
# include <stdio.h>
# include <unistd.h>
# include <string.h>
# include <stdlib.h>
# include <stdbool.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft.h"

# define DEFAULT_PATH "PATH=/usr/local/bin:/usr/bin:/bin"
# define PROMPT "$> "
# define ERR_PARSER "Error: Syntax error\n"
# define ERR_COMMAND "Error: command not found\n"
# define ERR_FILE "Error: no such file\n"

typedef struct t_list	t_garbage;

typedef enum e_error
{
	E_FILE = 1,
	E_PARSER,
	E_COMMAND = 127,
	E_MAX
}	t_error;

enum e_token
{
	E_INIT = 300,
	E_WORD,
	E_ASSIGNMENT_WORD,
	E_EXPANSION,
	E_AND_IF,
	E_OR_IF,
	E_DLESS,
	E_DGREAT,
	E_EOI,
	E_LESS,
	E_GREAT,
	E_LBRACE,
	E_RBRACE,
	E_SEP,
	E_PIPE,
	E_VALID_BUILTIN,
	E_VALID_FILE,
	E_UNKNOWN_WORD
};

typedef struct s_token {
	char		*lex;
	size_t		len;
	enum e_token		type;	
} t_token;

typedef struct s_tokenlist
{
	t_token	*token;
	struct 	s_tokenlist	*next;
} t_tokenlist;

// Node a mettre dans l'arbre binaire
typedef struct s_nodes
{
	enum e_token	type;
	t_token			*token;
	t_tokenlist		*tokenlst;
	size_t			lentokenlist;
}	t_nodes;

// Abre binaire AST
typedef struct s_btree
{
	t_nodes			*node;
	struct s_btree	*left;
	struct s_btree	*right;
}	t_btree;

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

int			ft_tokentsize(t_tokenlist *lst);
void		ft_tokenadd_front(t_tokenlist **alst, t_tokenlist *new);
void		ft_tokenadd_back(t_tokenlist **alst, t_tokenlist *new);
void		ft_tokendelone(t_tokenlist *lst, void (*del)(void *));
void		ft_tokenclear(t_tokenlist **lst, void (*del)(void *));
t_tokenlist	*ft_tokennew(void *content);
t_tokenlist	*ft_tokenlast(t_tokenlist *lst);

int			is_special_token(char c);
void		word_token(char *input, t_token *token);
int			is_eoi(char c, t_token *token);
int			is_token_1(char *input, t_token *token);
int			is_token_2(char *input, t_token *token);
//void		sep_token(char *input, t_token *token);

void		lexical_analysis(char *input, t_tokenlist **lst);

bool		check_cmd(t_tokenlist *lst, char **envp);

char		*get_path(char **env, char *pg);

char		*free_str(char *str);
char		*free_tab(char **tab);
char		*free_elt_tab(char **tab);
char		*free_str_tab(char **tab, int index);

// a refaire les fonction t_wordlist en t_strlist refaire une fonction recreate_str
int			ft_wordlst_addback(t_strlist **lst_curr, void *data, enum e_token type);
int			ft_find_great(t_btree *tree, t_termstd **saved);
char		*ft_recreate_str(char *lex, int len);
t_strlist	*ft_wordlst_new(void *data, enum e_token type);

int		ft_free_err(char **old, char **new);
int		ft_pwd(void);
int		ft_echo(const char *s, int flag);
int		ft_cd(const char *path);
int		ft_export(char *var, char ***env_curr);
int		ft_unset(char *var, char ***env_curr);
int		ft_env(char **envp);

int	print_error(t_error);

// tree_utils.c
void	ft_treeclear(t_btree *tree, void (*del) (void *));
void	ft_treeprint(t_btree *tree, int type);
#endif
