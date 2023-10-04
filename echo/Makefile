NAME = echooo

CC = cc

CFLAGS = -Wall -Wextra -Werror

RM = rm -rf
AR = ar rc

.PHONY: all clean fclean re
SRC  = echo.c
OBJ = $(SRC:%.c=%.o)

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
