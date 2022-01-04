# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: anajmi <anajmi@studetnt.1337.ma>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/18 14:50:48 by anajmi            #+#    #+#              #
#    Updated: 2021/12/27 20:45:55 by anajmi           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = a.out
# FILE = $(FILE:.c=.out)
# OBJ = test0linpx.c
# OBJ = test1manpx.c
# OBJ = test2linimg.c
OBJ = test3manimg.c

# %.o: %.c
# 	$(CC) -Wall -Wextra -Werror -Imlx -c $< -o $@

# all:
# 	$(CC) $(OBJ) libmlx.a -lmlx -framework OpenGL -framework AppKit  -o ${NAME}

%.c: %.c
	$(CC) -Wall -Wextra -Werror -I/usr/local/include -Imlx_linux -O3 -c $< -o $@
# linux
all:
	$(CC) $(OBJ) -lmlx -lXext -lX11 -lm -lz -o $(NAME)

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
	
