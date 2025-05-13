# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yrodrigu <yrodrigu@student.42barcelo>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/13 17:06:57 by yrodrigu          #+#    #+#              #
#    Updated: 2025/05/13 17:33:42 by yrodrigu         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
NAME = cub3D
HEADER = cub3D
MLX_A = inc/minilibx-linux/libmlx_Linux.a
CFLAGS = -Wall -Wextra -Werror -g
CFILES = src/main.c
OBJS = $(CFILES:.c=.o)

all: $(NAME)

$(NAME): $(OBJS) library
	$(CC) $(CFLAGS) $(OBJS) $(MLX_A) -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz -o $(NAME)

%.o: %.c 
	$(CC) $(CFLAGS) -I/usr/include -Imlx_linux -c $< -o $@

library:
	make -C inc/minilibx-linux --silent

clean:
	make clean -C inc/minilibx-linux --silent
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re library

