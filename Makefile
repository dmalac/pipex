NAME = pipex

SRCDIR = src
OBJDIR = obj
LIBFTDIR = libft
INCL_DIR = incl

CC = gcc
CC_FLAGS = -Wall -Wextra -Werror 
INCLUDE = -I $(INCL_DIR)
# to be deleted
DEBUG_FLAGS = -g -fsanitize=address

LIBFT = $(LIBFTDIR)/libft.a
SRC_FILES = main.c parent.c child.c files_operations.c
SRC = $(addprefix $(SRCDIR)/,$(SRC_FILES))
OBJ = $(addprefix $(OBJDIR)/,$(SRC_FILES:.c=.o))

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT)
	$(CC) $(INCLUDE) $(CC_FLAGS) -o $@ $^

debug:		#rm debug
	make "CC_FLAGS = $(CC_FLAGS) $(DEBUG_FLAGS)"

$(OBJ): | $(OBJDIR)

$(OBJDIR):
	mkdir $(OBJDIR)

$(OBJDIR)/%.o: $(SRCDIR)/%.c	#rm debug flags
	$(CC) $(INCLUDE) $(CC_FLAGS) -c $? -o $@

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