# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: anajmi <anajmi@student.1337.ma>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/18 14:50:48 by anajmi            #+#    #+#              #
#    Updated: 2022/01/06 20:58:08 by anajmi           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = a.out
# FILE = $(FILE:.c=.out)
# OBJ = test0linpx.c
# OBJ = test1manpx.c
# OBJ = test2linimg.c
# OBJ = test3manimg.c
OBJ = ./src/main.c

# MacOS
%.o: %.c
	$(CC) -Wall -Wextra -Werror -Imlx -c $< -o $@

all:
	$(CC) $(OBJ) ./Libft/libft.a -lmlx -framework OpenGL -framework AppKit  -o ${NAME}

# linux
# %.c: %.c
# 	$(CC) -Wall -Wextra -Werror -I/usr/local/include -Imlx_linux -O3 -c $< -o $@

# all:
# 	$(CC) $(OBJ) -lmlx -lXext -lX11 -lm -lz -o $(NAME)

# MacOS
# all:
# 	$(CC) $(OBJ) libmlx.dylib libmlx.a -lmlx -framework OpenGL -framework AppKit  -o ${NAME}

	
# all:
# 	$(CC) $(OBJ) -lmlx -framework OpenGL -framework AppKit  -o ${NAME}

# all:
# 	$(CC) $(OBJ) libmlx.dylib libmlx.a -o ${NAME}

clean:
	rm -rf a.out

re: clean all
	
