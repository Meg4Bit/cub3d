NAME = cub3D
LIB = libft
CC = gcc
DIR = srcs
SRC =   $(DIR)/main.c\
		$(DIR)/utils.c\
		$(DIR)/ray_caster.c\
		$(DIR)/print_sprite.c\
		$(DIR)/render_next_frame.c\
		$(DIR)/key_hooks.c\
		$(DIR)/text_load.c\
		$(DIR)/read_file.c\
		$(DIR)/check_args.c\
		$(DIR)/vars_setup.c\
		$(DIR)/parse_map.c\
		$(DIR)/free_all.c\
		$(DIR)/bmp.c
OBJ = $(SRC:.c=.o)
CFLAGS = -Wall -Wextra -Werror

all: minilibx libfta $(NAME)

$(NAME): $(OBJ)
	$(CC) $(OBJ) -Lmlx_linux -lmlx -L$(LIB) -lft -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lbsd -o $(NAME)

libfta:
	@cd $(LIB) && make

minilibx:
	cd mlx_linux && make

%.o: %.c
	$(CC) $(CFLAGS) -I/usr/include -Imlx_linux -O3 -c $< -o $@

bonus:
	$(MAKE) all

clean:
	/bin/rm -f */*.o

fclean: clean
	/bin/rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
