NAME = libft.a

CC = gcc
CC_FLAGS = -Wall -Wextra -Werror
DEBUG_FLAGS = -g -fsanitize=address # to be deleted

OBJDIR = obj

SRC = ft_strncmp.c ft_split.c
OBJ = $(addprefix $(OBJDIR)/,$(SRC:.c=.o))

all: $(OBJ)
	ar -rsu $(NAME) $?

$(OBJ): | $(OBJDIR)

$(OBJDIR):
	mkdir $(OBJDIR)

$(OBJDIR)/%.o: %.c
	$(CC) $(CC_FLAGS) $(DEBUG_FLAGS) -c $< -o $@

clean:
	rm -Rf $(OBJDIR)

fclean: clean
	rm -f $(NAME)

re: fclean
	make

.PHONY: all clean fclean re