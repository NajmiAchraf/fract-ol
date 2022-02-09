# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: anajmi <anajmi@student.1337.ma>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/18 14:50:48 by anajmi            #+#    #+#              #
#    Updated: 2022/02/09 15:35:01 by anajmi           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fractol
# FILE = $(FILE:.c=.out)
# OBJ = ./tests/test0linpx.c
# OBJ = ./tests/test1manpx.c
# OBJ = ./tests/test2linimg.c
# OBJ = ./tests/test3manimg.c
# OBJ = ./tests/test4julia.c
# OBJ = ./src/fractol.c
# OBJ = ./src/fractoljul.c
OBJ = ./src/fractolmod.c

ifeq ($(shell uname -s), Linux)
  MLXINC	= -I/usr/local/include -Imlx_linux -O3
  MLXLIB	= ./libft/libftlinux.a -lmlx -lXext -lX11 -lm -lz
else
  MLXINC	= -Imlx
  MLXLIB	= ./libft/libft.a -lmlx -framework OpenGL -framework AppKit
endif

%.o: %.c
	$(CC) -Wall -Wextra -Werror $(MLXINC) -c $< -o $@

all:
	$(CC) $(OBJ) $(MLXLIB) -o ${NAME}

clean:
	rm -rf ${NAME}

re: clean all
	
