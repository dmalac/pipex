NAME = pipex

SRCDIR = src
OBJDIR = obj
LIBFTDIR = libft
INCL_DIR = incl

CC = gcc
CC_FLAGS = -Wall -Wextra -Werror
INCLUDE = -I $(INCL_DIR)

LIBFT = $(LIBFTDIR)/libft.a
LIBFT_BONUS = $(LIBFTDIR)/libft_bonus.a
SRC_FILES = main.c parent.c child.c files_ops.c cleanup.c
BONUS_SRC_FILES = main_bonus.c parent_bonus.c child_bonus.c files_ops_bonus.c \
cleanup_bonus.c
SRC = $(addprefix $(SRCDIR)/,$(SRC_FILES))
OBJ = $(addprefix $(OBJDIR)/,$(SRC_FILES:.c=.o))
BONUS_SRC = $(addprefix $(SRCDIR)/,$(BONUS_SRC_FILES))
BONUS_OBJ = $(addprefix $(OBJDIR)/,$(BONUS_SRC_FILES:.c=.o))
BONUS ?= 0

all: $(NAME)

ifeq ($(BONUS),1)
$(NAME): $(BONUS_OBJ) $(LIBFT_BONUS)
	$(CC) $(INCLUDE) $(CC_FLAGS) -o $@ $^
else
$(NAME): $(OBJ) $(LIBFT)
	$(CC) $(INCLUDE) $(CC_FLAGS) -o $@ $^
endif

$(OBJ): | $(OBJDIR)

$(BONUS_OBJ): | $(OBJDIR)

$(OBJDIR):
	mkdir $(OBJDIR)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(INCLUDE) $(CC_FLAGS) -c $? -o $@

$(LIBFT):
	$(MAKE) -C $(LIBFTDIR)

$(LIBFT_BONUS):
	$(MAKE) bonus -C $(LIBFTDIR)

bonus:
	$(MAKE) "BONUS = 1"

clean:
	rm -Rf $(OBJDIR)
	$(MAKE) clean -C $(LIBFTDIR)

fclean: clean
	rm -f $(NAME) $(LIBFT) $(LIBFT_BONUS)

re: fclean
	$(MAKE)

.PHONY: bonus clean fclean re all