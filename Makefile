NAME = pipex

SRCDIR = src
OBJDIR = obj
LIBFTDIR = libft
INCL_DIR = incl

CC = gcc
CC_FLAGS = -Wall -Wextra -Werror 
INCLUDE = -I $(INCL_DIR)

LIBFT = $(LIBFTDIR)/libft.a
SRC_FILES = main.c parent.c child.c files_ops.c cleanup.c
BONUS_SRC_FILES = main_bonus.c parent.c child.c files_ops.c cleanup_bonus.c
SRC = $(addprefix $(SRCDIR)/,$(SRC_FILES))
OBJ = $(addprefix $(OBJDIR)/,$(SRC_FILES:.c=.o))
BONUS_SRC = $(addprefix $(SRCDIR)/,$(BONUS_SRC_FILES))
BONUS_OBJ = $(addprefix $(OBJDIR)/,$(BONUS_SRC_FILES:.c=.o))

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT)
	$(CC) $(INCLUDE) $(CC_FLAGS) -o $@ $^

$(OBJ): | $(OBJDIR)

$(OBJDIR):
	mkdir $(OBJDIR)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(INCLUDE) $(CC_FLAGS) -c $? -o $@

$(LIBFT):
	$(MAKE) -C $(LIBFTDIR)

bonus:
	$(MAKE) "OBJ = $(BONUS_OBJ)"

clean:
	rm -Rf $(OBJDIR)
	$(MAKE) clean -C $(LIBFTDIR)

fclean: clean
	rm -f $(NAME) $(LIBFT)

re: fclean
	$(MAKE)

.PHONY: bonus clean fclean re all