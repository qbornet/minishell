#ifndef LEXER_H
# define LEXER_H
# include <stdio.h>
# include <unistd.h>
# include "libft.h"

#define INIT_TOKEN 300
#define WORD 301
#define ASSIGNMENT_WORD 302
#define NEWLINE 303
#define IO_NUMBER 304
#define AND_IF 305
#define OR_IF 306
#define DLESS 307
#define DGREAT 308
#define EOI 309

typedef struct s_word {
	char	*lexeme;
	int		token;	
} t_word;

#endif
