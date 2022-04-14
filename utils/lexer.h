#ifndef LEXER_H
# define LEXER_H
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include "libft.h"

#define INIT_TOKEN 300

#define WORD 301
#define ASSIGNMENT_WORD 302

#define AND_IF 305
#define OR_IF 306
#define DLESS 307
#define DGREAT 308

#define LESS 310
#define GREAT 311
#define LBRACE 312
#define RBRACE 313

#define EOI 309

typedef struct s_token {
	char		*lex;
	size_t		len;
	int			id;	
} t_token;

typedef struct s_tokenlist
{
	t_token	*token;
	struct 	s_tokenlist	*next;
} t_tokenlist;

t_tokenlist	*ft_tokennew(void *content);
void		ft_tokenadd_front(t_tokenlist **alst, t_tokenlist *new);
int			ft_tokentsize(t_tokenlist *lst);
t_tokenlist	*ft_tokenlast(t_tokenlist *lst);
void		ft_tokenadd_back(t_tokenlist **alst, t_tokenlist *new);
void		ft_tokendelone(t_tokenlist *lst, void (*del)(void *));
void		ft_tokenclear(t_tokenlist **lst, void (*del)(void *));

size_t		is_eoi(char c, t_token *token);
void		word_token(char *input, t_token *token);
size_t		is_token_1(char *input, t_token *token);
size_t		is_token_2(char *input, t_token *token);

#endif
