NAME = cub3D
LIB = libft
CC = gcc
HEADER = ft_printf.h
DIR = srcs
SRC =   $(DIR)/main.c\
		$(DIR)/utils.c\
		$(DIR)/ray_caster.c\
		$(DIR)/print_sprite.c\
OBJ = $(SRC:.c=.o)
CFLAGS = -Wall -Wextra -Werror

ifdef WITH_BONUS
	OBJ_FILES = $(OBJBONUS)
else
	OBJ_FILES = $(OBJ)
endif

all: libfta $(NAME)

$(NAME): $(OBJ)
	#$(CC) -Lmlx -lmlx -framework OpenGL -framework AppKit -o $(NAME)
	$(CC) $(OBJ) -Lmlx_linux -lmlx -L$(LIB) -lft -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lbsd -o $(NAME)

libfta:
	@cd $(LIB) && make

%.o: %.c
	#$(CC) -Wall -Wextra -Werror -Imlx -c $< -o $@
	$(CC) $(CFLAGS) -I/srcs -I/usr/include -Imlx_linux -O3 -c $< -o $@

bonus:
	$(MAKE) all

clean:
	/bin/rm -f */*.o

fclean: clean
	/bin/rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
