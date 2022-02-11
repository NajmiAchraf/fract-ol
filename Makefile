# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: anajmi <anajmi@student.1337.ma>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/18 14:50:48 by anajmi            #+#    #+#              #
#    Updated: 2022/02/11 14:43:49 by anajmi           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fractol

FILES = \
	./src/main.c			\
	./src/fractol.c			\
	./src/bind_exec.c		\
	./src/bind.c			\
	./src/help.c			\
	./src/image.c			\
	./src/value.c			\
	./utils/ft_atof.c		\
	./utils/ft_atoi.c		\
	./utils/ft_putchar.c	\
	./utils/ft_putstr.c

OBJ = $(FILES:.c=.o)

ifeq ($(shell uname -s), Linux)
  MLXINC	= -I/usr/local/include -Imlx_linux -O3
  MLXLIB	= ./libft/libftlinux.a -lmlx -lXext -lX11 -lm -lz
else
  MLXINC	= -Imlx
  MLXLIB	= ./libft/libft.a -lmlx -framework OpenGL -framework AppKit
endif

all: $(NAME) 

$(NAME): $(OBJ)
	$(CC) $(OBJ) $(MLXLIB) -o ${NAME}

$(OBJ): %o:%c
	$(CC) -c -Wall -Wextra -Werror $(MLXINC) $^ -o $@

clean:
	rm -rf ${OBJ}

fclean: clean
	rm -rf ${NAME}

re: fclean all
