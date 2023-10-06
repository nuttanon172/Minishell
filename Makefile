NAME = minishell

#SRC_DIR = ./source
#OBJ_DIR = obj

CC = cc

CFLAGS = -Wall -Wextra -Werror -L /usr/local/opt/readline/lib/ -I /usr/opt/readline/include

RM = rm -rf

AR = ar rc

SRC  = 01_main.c \
		02_get_from_readline.c \
		03_pipex.c \
		04_utils.c \
		05_utils_string.c \
		06_utils_table_ok.c \
		07_utils_env_split.c

OBJ = $(SRC:%.c=%.o)

.PHONY: all clean fclean re
all: $(NAME)

$(NAME) : $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)
	@echo "Nanoshell starts"

$(OBJ):
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

#clean .o keep .c .a
clean:
	$(RM) $(OBJ_DIR)
	@echo "cleaned!"

#clean .o & .a keep .c
fclean: clean
	$(RM) $(NAME)
	$(RM) $(OBJ_DIR)
	@echo "no clue now :|"

re:	fclean all

#$(NAME): $(OBJ) liball
#	$(CC) $(CFLAGS) $(OBJ) $(MLX) $(LIBFT) $(FT_PRINTF) $(MLX_FLAGS) -o $(NAME)
#	@echo "Nanoshell starts"

#$(OBJ): $(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
#	mkdir -p $(OBJ_DIR)
#	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

#liball:
#	make -C $(LIBFT_DIR)
#	make -C $(MLX_DIR)
#	make -C $(FT_PRINTF_DIR) 

#clean .o keep .c .a
#clean:
#	$(RM) $(OBJ_DIR)
#	make clean -C $(MLX_DIR)
#	make clean -C $(LIBFT_DIR)
#	make clean -C $(FT_PRINTF_DIR)
#	@echo "yep, cleaned"

#clean .o & .a keep .c
#fclean: clean
#	$(RM) $(NAME)
#	$(RM) $(OBJ_DIR)
#	make clean -C $(MLX_DIR)
#	make fclean -C $(LIBFT_DIR)
#	make fclean -C $(FT_PRINTF_DIR)
#	@echo "start over"

#re:	fclean all

#.PHONY: all clean fclean re
