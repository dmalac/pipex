NAME = libft.a
NAME_BONUS = libft_bonus.a

OBJDIR = obj
INCL_DIR = ../incl

CC = gcc
CC_FLAGS = -Wall -Wextra -Werror 
INCLUDE = -I $(INCL_DIR)

SRCS = ft_putstr_fd.c ft_split.c ft_strjoin.c ft_strlen.c ft_strncmp.c 
OBJS = $(addprefix $(OBJDIR)/,$(SRCS:.c=.o))
BONUS_SRCS = ft_putstr_fd.c ft_split.c ft_strjoin.c ft_strlen.c ft_strncmp.c \
ft_bzero.c ft_substr.c get_next_line.c
BONUS_OBJS = $(addprefix $(OBJDIR)/,$(BONUS_SRCS:.c=.o))

all: $(NAME)

$(NAME): $(OBJS)
	ar -rsu $(NAME) $?

$(OBJS): | $(OBJDIR)

$(OBJDIR):
	mkdir $(OBJDIR)

$(OBJDIR)/%.o: %.c
	$(CC) $(INCLUDE) $(CC_FLAGS) -c $< -o $@

bonus: $(NAME_BONUS)

$(NAME_BONUS): $(BONUS_OBJS)
	ar -rsu $(NAME_BONUS) $?

clean:
	rm -Rf $(OBJDIR)

fclean: clean
	rm -f $(NAME) $(NAME_BONUS)

re: fclean
	$(MAKE)

.PHONY: all bonus clean fclean re