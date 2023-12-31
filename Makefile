NAME = minishell

CC = cc

#LIB_RL	=	-lreadline -L/usr/local/opt/readline/lib/ -I/usr/opt/readline/include
LIB_RL	=	-lreadline -L/opt/homebrew/opt/readline/lib/ -I/opt/homebrew/opt/readline/include/readline/

CFLAGS	=	-Wall -Wextra -Werror

RM = rm -rf

AR = ar rc

SRCS  = 01_0main.c \
		01_1main.c \
		01_2main.c \
		01_2main_utils.c \
		01_3main.c \
		01_4main.c \
		01_5main.c \
		02_get_from_readline.c \
		03_0pipex_utils.c \
		03_0pipex_utils2.c \
		03_0pipex.c \
		03_1pipex.c \
		04_utils.c \
		05_utils_string.c \
		06_0utils_table_ok.c \
		06_1utils_table_ok.c \
		07_1utils_env_split_ok.c \
		07_2utils_env_split_ok.c \
		08_unset.c \
		09_export.c \
		10_isDir.c \
		11_check_ex_unset.c \
		shelllvl.c \
		minishell_utils.c \
		minishell_utils2.c \
		builtin.c

OBJS = $(SRCS:.c=.o)

$(NAME): $(OBJS)
	@$(RM) bin
	@mkdir bin
	@make -C env
	@$(CC) $(CFLAGS) $(OBJS) $(LIB_RL) -o $(NAME)
	@echo "Nanoshell starts"

.PHONY: all clean fclean re
all: $(NAME)

clean:
	@$(RM) $(OBJS)
	@make clean -C env
	@echo "cleaned!"

fclean: clean
	@make fclean -C env
	@$(RM) bin
	@$(RM) $(NAME)
	@echo "no clue now :|"

re:	fclean all
