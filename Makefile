SRCS = ft_tokenadd_back.c \
	   ft_tokenadd_front.c \
	   ft_tokenclear.c \
	   ft_tokendelone.c \
	   ft_tokenlast.c \
	   ft_tokennew.c \
	   ft_tokensize.c \
	   lexer.c


OBJS = $(SRCS:%.c=%.o)


CC = clang
CFLAGS = -Wall -Werror -Wextra 

%.o: %.c
	$(CC) $(CFLAGS) -I ./libft/utils -c $< -o $@

lexer.out: $(OBJS)
	$(CC) $(CFLAGS) $^ -o  $@
