NAME = libft.a

OBJDIR = obj
INCL_DIR = ../incl

CC = gcc
CC_FLAGS = -Wall -Wextra -Werror 
INCLUDE = -I $(INCL_DIR)

SRCS = ft_putstr_fd.c ft_split.c ft_strjoin.c ft_strlen.c ft_strncmp.c 
OBJS = $(addprefix $(OBJDIR)/,$(SRCS:.c=.o))

all: $(OBJS)
	ar -rsu $(NAME) $?

$(OBJS): | $(OBJDIR)

$(OBJDIR):
	mkdir $(OBJDIR)

$(OBJDIR)/%.o: %.c
	$(CC) $(INCLUDE) $(CC_FLAGS) -c $< -o $@

clean:
	rm -Rf $(OBJDIR)

fclean: clean
	rm -f $(NAME)

re: fclean
	$(MAKE)

.PHONY: all clean fclean re