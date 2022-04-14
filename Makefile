# Configuration
#---------------------------------------------------

# Output 
NAME = lexer

# Sources directories
SRCS_DIR = srcs
OBJS_DIR = objs
UTILS_DIR = utils

# Utils
CC = clang
CFLAGS = -MMD -Wall -Wextra -Werror
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
	lexer.c \
	lexer_utils.c

GREEN   = \033[1;32m
WHITE   = \033[0;m

#---------------------------------------------------

# Header files
UTILS = $(UTILS_DIR)/$(addsufix .h, $(NAME))

OBJS = $(SRCS:%.c=$(OBJS_DIR)/%.o)
DEPS = $(OBJS:%.o=%.d)

all: $(NAME)

$(NAME): $(OBJS)
	make -C $(LFT) 
	echo "-------------------"
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

# Set VERBOSE=1 for verbose
ifndef VERBOSE
.SILENT:
endif
