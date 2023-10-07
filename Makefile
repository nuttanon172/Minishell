NAME = minishell

CC = cc

LIB_RL	=	-L/usr/local/opt/readline/lib/
INC_RL	=	-I/usr/opt/readline/include

CFLAGS	=	-Wall -Wextra -Werror $(LIB_RL) $(INC_RL)

#LDFLAGS = -L/opt/homebrew/opt/readline/lib
#CPPFLAGS = -I/opt/homebrew/opt/readline/include/readline
#CFLAGS = -Wall -Wextra -Werror $(CPPFLAGS) $(LDFLAGS)

RM = rm -rf

AR = ar rc

SRC  = 01_0main.c \
		01_0main_util.c \
		01_1main.c \
		01_1main_util.c \
		01_2main.c \
		01_2main_util.c \
		01_3main.c \
		01_4main.c \
		02_get_from_readline.c \
		03_0pipex.c \
		03_1pipex.c \
		04_utils.c \
		05_utils_string.c \
		06_0utils_table_ok.c \
		06_1utils_table_ok.c \
		07_0utils_env_split_ok.c \
		07_1utils_env_split_ok.c

OBJ = $(SRC:%.c=%.o)

$(NAME):
	$(CC) $(CFLAGS) $(SRC) -o $(NAME)
	@echo "Nanoshell starts"

.PHONY: all clean fclean re
all: $(NAME)
	@make -C echo
	@make -C unset
	@make -C export
	@make -C exit
	@make -C env
	@mkae -C echo

clean:
	$(RM) $(OBJ)
	@make clean -C echo
	@make clean -C unset
	@make clean -C export
	@make clean -C exit
	@make clean -C env
	@mkae clean -C echo
	@echo "cleaned!"

fclean: clean
	$(RM) $(NAME)
	$(RM) $(OBJ)
	@echo "no clue now :|"

re:	fclean all
