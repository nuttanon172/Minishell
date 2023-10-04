# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ntairatt <ntairatt@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/24 21:18:22 by naam              #+#    #+#              #
#    Updated: 2023/10/04 17:52:55 by ntairatt         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

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
