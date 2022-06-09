#ifndef MINISHELL_H
# define MINISHELL_H
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
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
# include <readline/readline.h>
# include <readline/history.h>

# define HEREDOC_PROMPT "here_doc?> "
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
	E_STAR,
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
	unsigned int		s_id;
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

typedef struct s_lenlist
{
	int					length;
	struct s_lenlist	*next;
}	t_lenlist;

// Notre struct "foure tout"
typedef struct s_data
{
	char		*str; // variable temporaire juste pour tester le here_doc
	char		**envp; // pas oublier a strdup le envp au debut
	char		**var_pool;
	char		***cmd_pool;
	t_btree		*root;
	t_termstd	std_fd;
	t_strlist	*strlst;
	t_lenlist	*lenlst;
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
/* expansion.c expansion_utils.c expansion_error.c expansion_check.c */
/* ft_create_join.c ft_create_cmd.c ft_lenlst.c */
int			ft_create_cmd(t_data **d_curr, int total_cmd);
int			ft_create_join(t_data **d_curr);
int			start_expansion(t_data **d_curr);
int			ft_check_pool(char  *str, char **pool, int res);
int			ft_free_expan_error(t_data **d_curr);
int			ft_do_starexp(t_data **d_curr);
void		ft_lenclear(t_lenlist **len_curr);
void		ft_lenadd_back(t_lenlist **len_curr, int data);
void		ft_do_varexp(t_data **d_curr);
void		ft_move_node(t_data **d_curr, t_strlist **s_curr);
size_t		ft_len_var(char *str);
t_lenlist	*ft_lennew(int data);
/* STAREXP_H */
/* starexp.c starexp_utils.c */
t_strlist	*starexp(t_strlist **strlst, t_data *frame, unsigned int *s_id);
t_strlist	*insert_strlst(t_strlist **slst, t_strlist **head, t_data *frame, unsigned int *s_id);
int			ft_starcmp(const char *s1, const char *s2);

/* VAREXP_H */
/* varexp.c varexp_utils.c */
void		expand(t_strlist *strlst, char **env, t_data **frame);
size_t		ft_len_onechar(char *s, char a);
size_t		ft_len_metachar(char *s);
/* HERE_DOC_H */
/* heredoc_str.c heredoc_utils.c heredoc_error.c here_doc.c */
int		here_doc(t_data **d_curr, char *word);
int		opt_word(char **w_curr);
int		ft_error_here(char *word);
int		ft_strcmp_here(char *s1, char *s2);
char	*do_expand(t_data **d_curr, char *str);
char	*ft_varexp(char *var, char **envp, char **var_pool);
char	*ft_error_ret(char *s1);
char	*ft_error_malloc(char **arr);
char	*ft_random_str(char *pathname, int bytes);
void	opt_free_doexpand(char *str, char *begin_str, char *end_str);
void	opt_find_dollars(char **s_curr, size_t *i);
size_t	ft_num_expand(char *str);
size_t	ft_null(char *str);
size_t	ft_strjoin_len(char *str);

/* BIN_H */
int			ft_free_err(char **old, char **new);
int			ft_pwd(void);
int			ft_echo(const char *s, int flag);
int			ft_cd(const char *path);
int			ft_export(char *var, char ***env_curr);
int			ft_unset(char *var, char ***env_curr);
int			ft_env(char **envp);
int			print_error(t_error code);

/* PIPE_H */
/* Pipex */
int		get_cmd_tab(char *cmd_string, char **env, char ***cmd);
int		exec_cmd(char **cmd, char **env);
int		pipex(int **pipes, int *pids, char **envp, char *raw_cmd);

/* Pipex tools */
char	*get_path(char **env, char *pg);
int		dup_inout(int new_in, int new_out);
int		close_pipe(int *pd);

/* Pipes */
int		ft_pipe(int argc, char **argv, char **envp);

/* Pipe utils 0 */
int		pipe_in(char *infile, int *pd);
int		pipe_mid(int *pd_in, int *pd_out);
int		pipe_out(int *pd, char *outfile);
int		open_fd(int **pipes, char **avector, int pipes_len, int i);

/* Pipe utils 1 */
int		close_pipes(int **pipes, int pipes_len, int *pids, int i);
int		alloc_pipes_pids(int ***pipes, int **pids, int pipes_len);
int		**malloc_and_open_pipes(int len);

/* Free tools */
char	*free_str(char *str);
char	*free_tab(char **tab);
char	*free_elt_tab(char **tab);
char	*free_str_tab(char **tab, int index);
void	*free_int_tab(int **tab, int i);
void	*free_int(int *tab);
int		free_and_return(int **tab1, int *tab2, int index, int return_val);
int		free_and_msg(int **tab1, int *tab2, int index, char *msg);

/* Error tools */
int		standard_error(char *str);
int		main_error(char *str);
int		error(char *str);
int		pipex_status(int pipes_len, int **pipes, int *pids);

#endif
