# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ametapod <pe4enko111@rambler.ru>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/06/09 18:18:13 by ametapod          #+#    #+#              #
#    Updated: 2020/06/09 18:18:13 by ametapod         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D
LIB = libft
CC = gcc
HEADER = ft_printf.h
SRC = main.c
OBJ = $(SRC:.c=.o)
CFLAGS = -Wall -Wextra -Werror

ifdef WITH_BONUS
	OBJ_FILES = $(OBJBONUS)
else
	OBJ_FILES = $(OBJ)
endif

all: $(NAME)

$(NAME): $(OBJ)
	#$(CC) -Lmlx -lmlx -framework OpenGL -framework AppKit -o $(NAME)
	$(CC) $(OBJ) -Lmlx_linux -lmlx -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz -o $(NAME)

#libfta:
#	@cd $(LIB) && make

%.o: %.c
	#$(CC) -Wall -Wextra -Werror -Imlx -c $< -o $@
	$(CC) $(CFLAGS) -I/usr/include -Imlx_linux -O3 -c $< -o $@

bonus:
	$(MAKE) all

clean:
	/bin/rm -f *.o

fclean: clean
	/bin/rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
