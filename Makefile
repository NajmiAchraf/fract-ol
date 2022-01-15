# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: anajmi <anajmi@student.1337.ma>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/18 14:50:48 by anajmi            #+#    #+#              #
#    Updated: 2022/01/10 02:22:33 by anajmi           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fractol
# FILE = $(FILE:.c=.out)
# OBJ = test0linpx.c
# OBJ = test1manpx.c
# OBJ = test2linimg.c
# OBJ = test3manimg.c
# OBJ = ./src/fractol.c
# OBJ = ./src/fractoljul.c
OBJ = ./src/fractolmod.c

# MacOS
# %.o: %.c
# 	$(CC) -Wall -Wextra -Werror -Imlx -c $< -o $@

# all:
# 	$(CC) $(OBJ) ./libft/libft.a -lmlx -framework OpenGL -framework AppKit  -o ${NAME}

# linux
# %.c: %.c
# 	$(CC) -Wall -Wextra -Werror -I/usr/local/include -Imlx_linux -O3 -c $< -o $@

# all:
# 	$(CC) $(OBJ) ./libft/libft.a  -lmlx -lXext -lX11 -lm -lz -o $(NAME)


ifeq ($(shell uname -s), Linux)
  MLXINC	= -I/usr/local/include -Imlx_linux -O3
  MLXLIB	= ./libft/libft.a -lmlx -lXext -lX11 -lm -lz
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
	
