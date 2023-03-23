# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: msarigul <msarigul@student.42kocaeli.com.  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/23 00:13:12 by msarigul          #+#    #+#              #
#    Updated: 2023/03/23 00:13:14 by msarigul         ###   ########.tr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror -O3 -Ofast -flto -march=native#-g -ggdb -fsanitize=address -fno-omit-frame-pointer -fsanitize=undefined 
RM = rm -f
#-O3 -Ofast -flto -march=native
NAME = fdf
LIBS = -Lmlx -lmlx -lm -framework OpenGL -framework AppKit
SRCS = bresenham.c projections.c draw.c init.c keys.c main.c mouse.c read.c utils.c gnl/*.c


all: ${NAME}

bonus: ${NAME}

${NAME}:
	${CC} ${CFLAGS} ${SRCS} ${LIBS} -o ${NAME}

clean:

fclean: clean
	$(RM) ${NAME}

re: fclean all

.PHONY: all bonus clean fclean re
