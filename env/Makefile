NAME	=	env

CC	=	cc

INC_RL_RL	=	-I/usr/local/opt/readline/include

CFLAGS	=	-Wall -Wextra -Werror

RM	=	rm -rf

AR	=	ar rc

SRC	=	env.c

OBJ	=	$(SRC:.c=.o)

.PHONY: all clean fclean re
all: $(NAME)
$(NAME) : $(OBJ)
	@$(CC) $(CFLAGS) $(OBJ) -o $(NAME)
	@mv $(NAME) ./bin

clean:
	$(RM) ../bin/$(NAME)
fclean: clean
	$(RM) $(NAME)
re:	fclean all
