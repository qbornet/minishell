# Configuration
#---------------------------------------------------

# Output 
NAME = minishell

# Sources directories
SRCS_DIR = srcs
OBJS_DIR = objs
UTILS_DIR = utils

# Utils
CC = clang
CFLAGS = -MMD -Wall -Wextra -Werror -g3
CPPFLAGS = -I ./$(UTILS_DIR) -I ./libft/utils
LDFLAGS = -L ./libft
RM = rm -rf

# Lib
LFT = ./libft/

# Sources files
SRCS = ft_tokenadd_back.c \
	ft_tokenadd_front.c \
	ft_tokenclear.c \
	ft_tokendelone.c \
	ft_tokenlast.c \
	ft_tokennew.c \
	ft_tokensize.c \
	free_str_utils.c \
	env_utils.c 

# File to create lexer part
LEXER = lexer.c \
	lexer_utils.c

# File to create binary tree part
BTREE = parser.c \
	tree_utils.c \
	check_cmd.c

GREEN   = \033[1;32m
WHITE   = \033[0;m

#---------------------------------------------------

# Header files
UTILS = $(UTILS_DIR)/$(addsufix .h, $(NAME))

LEXEROBJS = $(LEXER:%.c=$(OBJS_DIR)/%.o)
BTREEOBJS = $(BTREE:%.c=$(OBJS_DIR)/%.o)
OBJS = $(SRCS:%.c=$(OBJS_DIR)/%.o)
DEPS = $(OBJS:%.o=%.d)

all: $(NAME)

lexer: $(LEXEROBJS) $(OBJS)
	make -C $(LFT)
	echo "-------------------"
	$(CC) $(CFLAGS) $(CPPFLAGS) $(LDFLAGS) $(LEXEROBJS) $(OBJS) -lft -o $@
	printf "\n[$(GREEN)OK$(WHITE)] Binary : $(NAME)\n\n"

btree: $(BTREEOBJS) $(LEXEROBJS) $(OBJS)
	make -C $(LFT)
	echo "-------------------"
	$(CC) $(CFLAGS) $(CPPFLAGS) $(LDFLAGS) $(BTREEOBJS) $(LEXEROBJS) $(OBJS) -lft -o $@
	printf "\n[$(GREEN)OK$(WHITE)] Binary : $(NAME)\n\n"

$(NAME): $(OBJS)
	make -C $(LFT) 
	echo "------------------"
	$(CC) $(CFLAGS) $(CPPFLAGS) $(LDFLAGS) $(OBJS) -lft -o $(NAME)
	printf "\n[$(GREEN)OK$(WHITE)] Binary : $(NAME)\n\n"

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c $(UTILS)
	mkdir -p $(OBJS_DIR) 
	$(CC) $(CFLAGS) $(CPPFLAGS) -o $@ -c $<
	printf "[$(GREEN)OK$(WHITE)] $<\n"

clean:
	make clean -C $(LFT) 
	$(RM) $(OBJS_DIR)
	printf "[$(GREEN)removed$(WHITE)] $(OBJS_DIR)/\n"

fclean: clean
	make fclean -C $(LFT)
	$(RM) $(NAME)
	printf "[$(GREEN)removed$(WHITE)] $(NAME)\n"

re: fclean all

-include $(DEPS)

.PHONNY: all clean fclean re

ifndef VERBOSE
.SILENT:
endif
lexer.out: $(OBJS)
	$(CC) $(CFLAGS) $^ -o  $@
