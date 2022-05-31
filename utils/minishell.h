#ifndef MINISHELL_H
# define MINISHELL_H
# include <sys/stat.h>
# include <sys/types.h>
# include <limits.h>
# include <dirent.h>
# include <fcntl.h>
# include <stdio.h>
# include <stddef.h>
# include <unistd.h>
# include <string.h>
# include <stdlib.h>
# include <stdbool.h>
# include <libft.h>
# include <errno.h>
//# include <readline/readline.h>
//# include <readline/history.h>

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
	E_FD,
	E_CONTINUE,
	E_ERROR
};

enum e_quote
{
	E_SINGLE = 350,
	E_DOUBLE
};

typedef struct s_token {
	char			*lex;
	size_t			len;
	enum e_token	type;	
	enum e_quote	qt;
}	t_token;

typedef struct s_tokenlist
{
	t_token				*token;
	struct s_tokenlist	*next;
}	t_tokenlist;

/* AST_H */
// s_termstd doit etre des dup des STDIN, STDOUT, STDERR constant
typedef struct s_termstd
{
	int	stdout;
	int	stdin;
	int	stderr;
}	t_termstd;

typedef struct s_strlist
{
	void				*data;
	enum e_token		type;
	struct s_strlist	*next;
	struct s_strlist	*prev;
}	t_strlist;

/* PARSER_H */
// Node a mettre dans l'arbre binaire
typedef struct s_nodes
{
	int				braces;
	int				pad;
	size_t			lentokenlist;
	enum e_token	type;
	t_token			*token;
	t_tokenlist		*tokenlst;
}	t_nodes;

// Abre binaire AST
typedef struct s_btree
{
	t_nodes			*node;
	struct s_btree	*left;
	struct s_btree	*right;
}	t_btree;

// Notre struct "foure tout"
typedef struct s_data
{
	char		**envp; // pas oublier a strdup le envp au debut
	char		**var_pool;
	t_btree		*root;
	t_termstd	std_fd;
	t_strlist	*strlst;
	t_tokenlist	*tokenlst;
}	t_data;

/* SORT_H */
/* ft_qsort.c */
void	ft_qsort(char **tab, int start, int end);

// Token list utils
int			ft_tokentsize(t_tokenlist *lst);
void		ft_tokenadd_front(t_tokenlist **alst, t_tokenlist *new);
void		ft_tokenadd_back(t_tokenlist **alst, t_tokenlist *new);
void		ft_tokendelone(t_tokenlist *lst, void (*del)(void *));
void		ft_tokenclear(t_tokenlist **lst, void (*del)(void *));
t_tokenlist	*ft_tokennew(void *content);
t_tokenlist	*ft_tokenlast(t_tokenlist *lst);

// Lexer utils
int			is_special_token(char c, t_token *token);
void		word_token(char *input, t_token *token);
int			is_eoi(char c, t_token *token);
int			is_token_1(char *input, t_token *token);
int			is_token_2(char *input, t_token *token);
//void		sep_token(char *input, t_token *token);

// Lexer
int			lexical_analysis(char *input, t_tokenlist **lst);

// Btree builder
t_btree	*buildbtree(char **envp, t_tokenlist *lst);

// Btree utils
t_btree		*ft_newbtree(t_nodes *node);
t_nodes		*ft_newnodes(t_tokenlist *lst);
t_btree		*ft_newleaf(t_tokenlist *lst);
void		btree_addnode(t_btree **root, t_tokenlist **lst);
int			is_redirection(int type);

// Check for valid built-in, valid file in filesystem or unknow word; used in btreebuilder
bool		check_cmd(t_nodes *node, char **envp);

// Check cmd utils
char		*get_path(char **env, char *pg);

// Free utils for strings
char		*free_str(char *str);
char		*free_tab(char **tab);
char		*free_elt_tab(char **tab);
char		*free_str_tab(char **tab, int index);
/* AST_H */
/* ft_strlist.c ft_read_flow.c */
int			lexer_parser_main(char *input, char **envp, t_data **d_curr);
int			ft_find_operator(t_btree *tree);
int			ft_read_flow(t_btree *tree, t_strlist **s_curr);
int			ft_strlst_addback(\
		t_strlist **lst_curr, void *data, enum e_token type);
void		ft_strdelone(t_strlist *strlst, void (*del) (void *));
void		*ft_strclear(t_strlist **s_curr, void (*del) (void *));
char		*ft_create_str(char *lex, size_t len);
t_strlist	*ft_strlst_new(void *data, enum e_token type);

/* PARSER_H */
/* parser.c tree_utils.c */
int			ft_treeexecute(t_btree *tree);
void		ft_treesearch(t_btree *tree, char *to_find);
void		ft_treeclear(t_btree *tree, void (*del) (void *));
void		ft_treeprint(t_btree *tree, int type);
void		ft_print_tokenlist(t_tokenlist *lst);

/* EXPANSION_H */
/* expansion.c expansion_utils.c expansion_error.c ft_braces.c*/
int			ft_braces(t_btree **b_curr);
int			ft_free_expan_error(t_data **d_curr);
int			start_expansion(t_data **d_curr);
void		ft_move_node(t_data **d_curr, t_strlist **s_curr);
void		ft_do_varexp(t_data **d_curr);
size_t		ft_len_var(char *str);
/* STAREXP_H */
/* starexp.c starexp_utils.c */
int			starexp(t_strlist **strlst);
int			ft_starexp(const char *s1, const char *s2, size_t n);
<<<<<<< HEAD
=======
int			insert_strlst(t_strlist **strlst, t_strlist **head);

>>>>>>> star
/* VAREXP_H */
/* varexp.c varexp_utils.c */
void		expand(t_strlist *strlst, char **env, t_data **frame);
size_t		ft_len_onechar(char *s, char a);
size_t		ft_len_metachar(char *s);


/* BIN_H */
int			ft_free_err(char **old, char **new);
int			ft_pwd(void);
int			ft_echo(const char *s, int flag);
int			ft_cd(const char *path);
int			ft_export(char *var, char ***env_curr);
int			ft_unset(char *var, char ***env_curr);
int			ft_env(char **envp);
int			print_error(t_error code);
#endif
