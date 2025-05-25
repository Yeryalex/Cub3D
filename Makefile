# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rbuitrag <rbuitrag@student.42barcelona.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/10 12:06:04 by rbuitrag          #+#    #+#              #
#    Updated: 2025/05/15 12:54:53 by rbuitrag         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3d

HEADER = inc/cub3d.h 
LIBFT = inc/libft/libft.a
MLX_A = inc/minilibx/libmlx_Linux.a

CFLAGS = -Wall -Werror -Wextra  -g #-fsanitize=address -fsanitize=leak

CFILES =	main.c \
			player/player.c \
			utils/utils.c \
			
		
GREEN = "\033[92m"
RESET = "\033[0m"

OBJS = $(addprefix src/, $(CFILES:.c=.o))

all: library $(NAME)

$(NAME): $(OBJS)
	@echo " "
	@echo $(GREEN)		Successfully compiled!$(RESET)
	@echo " "
	@$(CC) $(CFLAGS) -g $(OBJS) $(LIBFT) $(MLX_A) -Lmlx_linux -L/usr/lib \
				  -Imlx_linux -lXext -lX11 -lm -lz -o -lreadline -o $(NAME)

%.o: %.c $(HEADER) Makefile $(LIBFT) $(MLX_A)
	@$(CC) $(CFLAGS) -I/usr/include -Imlx_linux -O3 -g -c $< -o $@

library:
	@make -C inc/libft --silent
	@make -C inc/minilibx --silent

clean:
	@make clean -C inc/libft --silent
	@make clean -C inc/minilibx --silent
	@rm -f $(OBJS)

fclean: clean
	@make fclean -C inc/libft --silent
	@rm -f $(NAME)

re: fclean all

v: all
	valgrind --leak-check=full --track-origins=yes -s ./cub3d maps/omnipotentes.cub
va: all
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes \
						  --suppressions=suppresionsX11 -q ./cub3d maps/omnipotentes.cub

.PHONY: all clean fclean re library
