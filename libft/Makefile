NAME = libft.a

OBJDIR = obj
INCL_DIR = ../incl

CC = gcc
CC_FLAGS = -Wall -Wextra -Werror 
INCLUDE = -I $(INCL_DIR)
# DEBUG_FLAGS = -g -fsanitize=address # to be deleted

SRC = ft_putnbr_fd.c ft_putstr_fd.c ft_split.c ft_strjoin.c ft_strlen.c ft_strncmp.c 
OBJ = $(addprefix $(OBJDIR)/,$(SRC:.c=.o))

all: $(OBJ)
	ar -rsu $(NAME) $?

$(OBJ): | $(OBJDIR)

$(OBJDIR):
	mkdir $(OBJDIR)

$(OBJDIR)/%.o: %.c
	$(CC) $(INCLUDE) $(CC_FLAGS) -c $< -o $@

clean:
	rm -Rf $(OBJDIR)

fclean: clean
	rm -f $(NAME)

re: fclean
	make

.PHONY: all clean fclean re