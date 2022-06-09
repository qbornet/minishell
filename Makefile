# Configuration
#---------------------------------------------------
# main is in expansion.c

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
SRCS = 	env_utils.c \
	lexer_parser_main.c

# Tools
TOOLS = ft_tokenadd_back.c \
	ft_tokenadd_front.c \
	ft_tokenclear.c \
	ft_tokendelone.c \
	ft_tokenlast.c \
	ft_tokennew.c \
	ft_tokensize.c \
	free_str_utils.c \
	free_int_utils.c \
	ft_qsort.c

# File to create lexer part
LEXER = lexer.c \
	lexer_utils.c

# File to create binary tree part
BTREE = btreebuilder.c \
	btreebuilder_utils.c \
	tree_utils.c \
	check_cmd.c

# File to create star expansion part
STAR = starexp.c \
	starexp_utils.c

# File to create var ($) expansion part
VAREXP = varexp.c \
	varexp_utils.c

# File to create read parser part
READ = ft_read_flow.c \
	   ft_strlist.c

# File to create expansion part
EXPAN = expansion.c \
		expansion_utils.c \
		expansion_error.c \
		expansion_check.c \
		ft_create_cmd.c \
		ft_create_join.c \
		ft_lenlst.c

# File to create here_doc part
HEREDOC = heredoc_utils.c \
		  heredoc_error.c \
		  heredoc_str.c \
		  opt_heredoc.c \
		  here_doc.c

# File to create pipe part
PIPE = pipe.c \
	pipe_utils_0.c \
	pipe_utils_1.c \
	pipex.c \
	pipex_utils.c \
	error_tools.c \


GREEN   = \033[1;32m
WHITE   = \033[0;m

#---------------------------------------------------

# Header files
UTILS = $(UTILS_DIR)/$(addsufix .h, $(NAME))

PIPEOBJS = $(PIPE:%.c=$(OBJS_DIR)/%.o)
EXPANOBJS = $(EXPAN:%.c=$(OBJS_DIR)/%.o)
READOBJS = $(READ:%.c=$(OBJS_DIR)/%.o)
LEXEROBJS = $(LEXER:%.c=$(OBJS_DIR)/%.o)
BTREEOBJS = $(BTREE:%.c=$(OBJS_DIR)/%.o)
STAROBJS = $(STAR:%.c=$(OBJS_DIR)/%.o)
TOOLSOBJS = $(TOOLS:%.c=$(OBJS_DIR)/%.o)
VAREXPOBJS = $(VAREXP:%.c=$(OBJS_DIR)/%.o)
HEREOBJS = $(HEREDOC:%.c=$(OBJS_DIR)/%.o)
OBJS = $(SRCS:%.c=$(OBJS_DIR)/%.o)
DEPS = $(OBJS:%.o=%.d)

pipe: $(PIPEOBJS) $(EXPANOBJS) $(READOBJS) $(LEXEROBJS) $(BTREEOBJS) $(TOOLSOBJS) $(VAREXPOBJS) $(STAROBJS) $(HEREOBJS) $(OBJS)
	make -C $(LFT)
	echo "-------------------"
	$(CC) $(CFLAGS) $(CPPFLAGS) $(LDFLAGS) $(READOBJS) $(EXPANOBJS) $(LEXEROBJS) $(BTREEOBJS) $(TOOLSOBJS) $(VAREXPOBJS) $(STAROBJS) $(HEREOBJS) $(OBJS) -lft -lreadline -o $@
	printf "\n[$(GREEN)OK$(WHITE)] Binary : $@\n\n"

here:	$(EXPANOBJS) $(READOBJS) $(LEXEROBJS) $(BTREEOBJS) $(TOOLSOBJS) $(VAREXPOBJS) $(STAROBJS) $(HEREOBJS) $(OBJS)
	make -C $(LFT)
	echo "-------------------"
	$(CC) $(CFLAGS) $(CPPFLAGS) $(LDFLAGS) $(READOBJS) $(EXPANOBJS) $(LEXEROBJS) $(BTREEOBJS) $(TOOLSOBJS) $(VAREXPOBJS) $(STAROBJS) $(HEREOBJS) $(OBJS) -lft -lreadline -o $@
	printf "\n[$(GREEN)OK$(WHITE)] Binary : $@\n\n"

expan:	$(EXPANOBJS) $(READOBJS) $(LEXEROBJS) $(BTREEOBJS) $(TOOLSOBJS) $(VAREXPOBJS) $(STAROBJS) $(OBJS)
	make -C $(LFT)
	echo "-------------------"
	$(CC) $(CFLAGS) $(CPPFLAGS) $(LDFLAGS) $(READOBJS) $(EXPANOBJS) $(LEXEROBJS) $(BTREEOBJS) $(TOOLSOBJS) $(VAREXPOBJS) $(STAROBJS) $(OBJS) -lft -o $@
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


lexer: $(LEXEROBJS) $(TOOLSOBJS)
	make -C $(LFT)
	echo "-------------------"
	$(CC) $(CFLAGS) $(CPPFLAGS) $(LDFLAGS) $(LEXEROBJS) $(TOOLSOBJS) -lft -o $@
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
