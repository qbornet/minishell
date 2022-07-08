# Configuration
#---------------------------------------------------
# main is in start.c

# Output 
NAME = minishell

# Sources directories
SRCS_DIR = srcs
OBJS_DIR = objs
UTILS_DIR = utils

# Utils
# Faut pas oublier d'enlever le fsan pour checker les exit_codes
CC = clang
CFLAGS = -MMD -Wall -Wextra -Werror -g3 -fsanitize=address
CPPFLAGS = -I ./$(UTILS_DIR) -I ./libft/utils
LDFLAGS = -L ./libft
RM = rm -rf

# Lib
LFT = ./libft/

# Sources files
SRCS = 	env_utils.c \
	lexer_parser_main.c \
	sig.c \
	exit_free.c \
	start_prompt.c \
	start_utils.c \
	io_tools.c \
	main.c \
	start.c 

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
	ft_perror.c \
	ft_perror_utils_0.c \
	ft_perror_utils_1.c \
	ft_qsort.c

# File to create lexer part
LEXER = lexer.c \
	lexer_utils.c \
	quotes.c

# File to create binary tree part
BTREE = btreebuilder.c \
	btreebuilder_utils_0.c \
	btreebuilder_utils_1.c \
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
	ft_read_flow_utils.c \
	ft_strlist.c

# File to create expansion part
EXPAN = expansion.c \
		expansion_utils.c \
		expansion_error.c \
		expansion_check.c \
		expansion_tilde.c \
		expansion_tilde_utils.c \
		opt_join.c \
		ft_create_cmd.c \
		ft_create_join.c \
		ft_lenlist.c \
		ft_cmdblock.c \
		ft_redirlst.c \
		command_block.c

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
	pipex_utils.c \
	ft_redirection.c \
	exec.c \
	exec_utils.c \
	exec_builtin.c \
	export.c \
	export_utils.c \
	export_error.c \
	export_vpool.c \
	echo.c \
	cd.c \
	pwd.c \
	unset.c \
	unset_utils.c \
	env.c \
	exit.c \
	underscore.c \
	ft_print_export.c \
	opt_export.c \
	error_tools.c


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

all: $(NAME)

$(NAME): $(PIPEOBJS) $(EXPANOBJS) $(READOBJS) $(LEXEROBJS) $(BTREEOBJS) $(TOOLSOBJS) $(VAREXPOBJS) $(STAROBJS) $(HEREOBJS) $(OBJS)
	make -C $(LFT) 
	echo "------------------"
	$(CC) $(CFLAGS) $(CPPFLAGS) $(LDFLAGS) $(READOBJS) $(EXPANOBJS) $(LEXEROBJS) $(BTREEOBJS) $(TOOLSOBJS) $(VAREXPOBJS) $(STAROBJS) $(HEREOBJS) $(PIPEOBJS) $(OBJS) -lft -lreadline -o $@
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
