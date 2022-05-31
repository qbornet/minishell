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
CFLAGS = -MMD -Wall -Wextra -Werror -g3 #-fsanitize=address
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
	env_utils.c \
	lexer_parser_main.c

# Tools
TOOLS = free_str_utils.c \
	ft_qsort.c

# File to create lexer part
LEXER = lexer.c \
	lexer_utils.c

# File to create binary tree part
BTREE = btreebuilder.c \
	btreebuilder_utils.c \
	tree_utils.c \
	check_cmd.c

STAR = starexp.c \
	starexp_utils.c

VAREXP = varexp.c \
	varexp_utils.c

# File to create read parser part
READ = ft_read_flow.c \
	   ft_strlist.c

# File to create expansion part
EXPAN = expansion.c \
		expansion_utils.c \
		expansion_error.c \
		ft_braces.c

GREEN   = \033[1;32m
WHITE   = \033[0;m

#---------------------------------------------------

# Header files
UTILS = $(UTILS_DIR)/$(addsufix .h, $(NAME))

EXPANOBJS = $(EXPAN:%.c=$(OBJS_DIR)/%.o)
READOBJS = $(READ:%.c=$(OBJS_DIR)/%.o)
LEXEROBJS = $(LEXER:%.c=$(OBJS_DIR)/%.o)
BTREEOBJS = $(BTREE:%.c=$(OBJS_DIR)/%.o)
STAROBJS = $(STAR:%.c=$(OBJS_DIR)/%.o)
TOOLSOBJS = $(TOOLS:%.c=$(OBJS_DIR)/%.o)
VAREXPOBJS = $(VAREXP:%.c=$(OBJS_DIR)/%.o)
OBJS = $(SRCS:%.c=$(OBJS_DIR)/%.o)
DEPS = $(OBJS:%.o=%.d)


expan:	$(EXPANOBJS) $(READOBJS) $(LEXEROBJS) $(BTREEOBJS) $(OBJS)
	make -C $(LFT)
	echo "-------------------"
	$(CC) $(CFLAGS) $(CPPFLAGS) $(LDFLAGS) $(READOBJS) $(EXPANOBJS) $(LEXEROBJS) $(BTREEOBJS) $(OBJS) -lft -o $@
	printf "\n[$(GREEN)OK$(WHITE)] Binary : $@\n\n"

read: $(READOBJS) $(OBJS)
	make -C $(LFT)
	echo "-------------------"
	$(CC) $(CFLAGS) $(CPPFLAGS) $(LDFLAGS) $(READOBJS) $(OBJS) -lft -o $@
	printf "\n[$(GREEN)OK$(WHITE)] Binary : $@\n\n"

test: $(READOBJS) $(LEXEROBJS) $(BTREEOBJS) $(OBJS)
	make -C $(LFT)
	echo "-------------------"
	$(CC) $(CFLAGS) $(CPPFLAGS) $(LDFLAGS) $(READOBJS) $(LEXEROBJS) $(BTREEOBJS) $(OBJS) -lft -o $@
	printf "\n[$(GREEN)OK$(WHITE)] Binary : $@\n\n"

eclean:	clean
	$(RM) expan
	printf "[$(GREEN)removed$(WHITE)] expan\n"

star: $(READOBJS) $(BTREEOBJS) $(STAROBJS) $(TOOLSOBJS) $(OBJS) $(LEXEROBJS) $(VAREXPOBJS)
	make -C $(LFT)
	echo "-------------------"
	$(CC) $(CFLAGS) $(CPPFLAGS) $(LDFLAGS) $(OBJS) $(READOBJS) $(VAREXPOBJS) $(BTREEOBJS) $(TOOLSOBJS) $(LEXEROBJS) $(STAROBJS) -lft -o $@
	printf "\n[$(GREEN)OK$(WHITE)] Binary : $@\n\n"

varexp: $(READOBJS) $(LEXEROBJS) $(BTREEOBJS) $(OBJS) $(VAREXPOBJS)
	make -C $(LFT)
	echo "-------------------"
	$(CC) $(CFLAGS) $(CPPFLAGS) $(LDFLAGS) $(READOBJS) $(LEXEROBJS) $(BTREEOBJS) $(OBJS) $(VAREXPOBJS) -lft -o $@
	printf "\n[$(GREEN)OK$(WHITE)] Binary : $@\n\n"
	
tclean: clean
	$(RM) test

rclean:
	$(RM) $(OBJS_DIR)
	$(RM) read

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

.PHONNY: all clean fclean re rclean

ifndef VERBOSE
.SILENT:
endif
lexer.out: $(OBJS)
	$(CC) $(CFLAGS) $^ -o  $@
