# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: naam <marvin@42.fr>                        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/24 22:18:17 by naam              #+#    #+#              #
#    Updated: 2023/09/25 18:51:17 by naam             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = envvv
CC = cc
CFLAGS = -Wall -Wextra -Werror

RM = rm -rf
AR = ar rc

SRC  = env.c
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

.PHONY: all clean fclean re
