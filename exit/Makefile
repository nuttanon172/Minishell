NAME = exittt

CC = cc

CFLAGS = -Wall -Wextra -Werror

RM = rm -rf

AR = ar rc

SRC  = exit.c

OBJ = $(SRC:%.c=%.o)

.PHONY: all clean fclean re
all: $(NAME)
$(NAME) : $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

%o: %c $(INCLUDE)
	@cc $(FLAGS) -I/usr/local/opt/readline/include -c $< -o $@

clean:
	$(RM) $(OBJ)
fclean: clean
	$(RM) $(NAME)
re:	fclean all
