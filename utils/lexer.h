#ifndef LEXER_H
# define LEXER_H
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include "libft.h"

typedef struct t_list	t_garbage;

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
	E_VALID_CMD
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
#endif
