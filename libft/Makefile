# Configuration
#---------------------------------------------------

# Output
NAME = libft.a

# Sources directories
SRCS_DIR = srcs
OBJS_DIR = objs
UTILS_DIR = utils

# Utils
CC = clang
CFLAGS = -MMD -Wall -Wextra -Werror
CPPFLAGS = -I ./$(UTILS_DIR)
RM = rm -rf

# Sources files
SRCS = ft_isalpha.c \
	ft_isdigit.c \
	ft_isalnum.c \
	ft_isascii.c \
	ft_isprint.c \
	ft_strlen.c \
	ft_memset.c \
	ft_bzero.c \
	ft_memcpy.c \
	ft_memmove.c \
	ft_strlcpy.c \
	ft_strdup.c \
	ft_strlcat.c \
	ft_toupper.c \
	ft_calloc.c \
	ft_tolower.c \
	ft_strchr.c \
	ft_strrchr.c \
	ft_strncmp.c \
	ft_split.c \
	ft_strtrim.c \
	ft_memchr.c \
	ft_memcmp.c \
	ft_strjoin.c \
	ft_strnstr.c \
	ft_substr.c \
	ft_strmapi.c \
	ft_striteri.c \
	ft_putchar_fd.c \
	ft_putstr_fd.c \
	ft_putendl_fd.c \
	ft_putnbr_fd.c \
	ft_atoi.c \
	ft_itoa.c
BONUS = ft_lstnew.c \
	ft_lstadd_front.c \
	ft_lstsize.c \
	ft_lstadd_back.c \
	ft_lstdelone.c \
	ft_lstclear.c \
	ft_lstiter.c \
	ft_lstmap.c \
	ft_lstlast.c

# Colors
GREEN   = \033[1;32m
WHITE   = \033[0;m

#---------------------------------------------------

# Header files
UTILS = $(UTILS_DIR)/$(addsufix .h, $(NAME))

OBJS = $(SRCS:%.c=$(OBJS_DIR)/%.o)
OBJS_BONUS = $(BONUS:%.c=$(OBJS_DIR)/%.o)
DEPS = $(OBJS:%.o=%.d)
DEPS_BONUS = $(OBJS_BONUS:%.o=%.d)

all: $(NAME)

$(NAME): $(OBJS)
	echo "-------------------"
	ar -rcs ${NAME} ${OBJS}
	printf "\n[$(GREEN)OK$(WHITE)] Library : $(NAME)\n\n"

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c
	mkdir -p $(OBJS_DIR) 
	$(CC) $(CFLAGS) $(CPPFLAGS) -o $@ -c $<
	printf "[$(GREEN)OK$(WHITE)] $<\n"

clean:
	$(RM) $(OBJS_DIR)
	printf "[$(GREEN)removed$(WHITE)] $(OBJS_DIR)/\n"

fclean: clean
	$(RM) $(NAME)
	printf "[$(GREEN)removed$(WHITE)] $(NAME)\n"

re: fclean all

bonus: $(OBJS) $(OBJS_BONUS)
	echo "-------------------"
	ar -rcs $(NAME) $(OBJS) $(OBJS_BONUS)
	printf "\n[$(GREEN)OK$(WHITE)] Library with bonus : $(NAME)\n\n"

-include $(DEPS) $(DEPS_BONUS)

.PHONNY: all clean fclean re

# Set VERBOSE=1 for verbose
ifndef VERBOSE
.SILENT:
endif
