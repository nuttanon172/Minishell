NAME = minishell

CC = cc

LIB_RL	=	-lreadline -L/usr/local/opt/readline/lib/ -I/usr/opt/readline/include

CFLAGS	=	-Wall -Wextra -Werror -g -fsanitize=address

RM = rm -rf

AR = ar rc

SRCS  = 01_0main.c \
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
		07_1utils_env_split_ok.c \
		07_2utils_env_split_ok.c \
		minishell_utils.c

OBJS = $(SRCS:.c=.o)

$(NAME): $(OBJS)
	@$(RM) bin
	@mkdir bin
	@make -C echo
	@make -C env
	@make -C exit
	@make -C export
	@make -C pwd
	@make -C unset
	@$(CC) $(CFLAGS) $(OBJS) $(LIB_RL) -o $(NAME)
	@echo "Nanoshell starts"

.PHONY: all clean fclean re
all: $(NAME)

clean:
	@$(RM) $(OBJS)
	@make clean -C echo
	@make clean -C env
	@make clean -C exit
	@make clean -C export
	@make clean -C pwd
	@make clean -C unset
	@echo "cleaned!"

fclean: clean
	@make fclean -C echo
	@make fclean -C env
	@make fclean -C exit
	@make fclean -C export
	@make fclean -C pwd
	@make fclean -C unset
	@$(RM) bin
	@$(RM) $(NAME)
	@$(RM) .minishell.env
	@echo "no clue now :|"

re:	fclean all
