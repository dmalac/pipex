NAME = pipex

CC = gcc
CC_FLAGS = -Wall -Wextra -Werror
DEBUG_FLAGS = -g -fsanitize=address	# to be deleted

SRCDIR = src
OBJDIR = obj
LIBFTDIR = libft

LIBFT = $(LIBFTDIR)/libft.a
SRC_FILES = main.c
SRC = $(addprefix $(SRCDIR)/,$(SRC_FILES))
OBJ = $(addprefix $(OBJDIR)/,$(SRC_FILES:.c=.o))

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT)
	$(CC) $(CC_FLAGS) $(DEBUG_FLAGS) -o $@ $^

$(OBJ): | $(OBJDIR)

$(OBJDIR):
	mkdir $(OBJDIR)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CC_FLAGS) $(DEBUG_FLAGS) -c $? -o $@

$(LIBFT):
	make -C $(LIBFTDIR)

clean:
	rm -Rf $(OBJDIR)
	make clean -C $(LIBFTDIR)

fclean: clean
	rm -f $(NAME) $(LIBFT)

re: fclean
	make

.PHONY: clean fclean re all