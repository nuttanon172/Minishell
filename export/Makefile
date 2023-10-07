NAME	=	export

CC	=	cc

INC_RL_RL	=	-I/usr/local/opt/readline/include

CFLAGS	=	-Wall -Wextra -Werror

RM	=	rm -rf

AR	=	ar rc

SRC	=	export.c
			01_export_utils.c \
			02_export_utils.c

OBJ	=	$(SRC:.c=.o)

.PHONY: all clean fclean re
all: $(NAME)
$(NAME) : $(OBJ)
	@$(CC) $(CFLAGS) $(OBJ) -o $(NAME)
	@mv $(NAME) ../bin

clean:
	$(RM) ../bin/$(NAME)
fclean: clean
	$(RM) $(NAME)
re:	fclean all
