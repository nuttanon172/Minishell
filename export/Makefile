# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: naam <marvin@42.fr>                        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/24 22:36:28 by naam              #+#    #+#              #
#    Updated: 2023/09/25 18:50:54 by naam             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = exporttt

CC = cc
CFLAGS = -Wall -Wextra -Werror

RM = rm -rf
AR = ar rc

SRC  = export.c \
		01_export_utils.c \
		02_export_utils.c \
		
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
