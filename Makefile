NAME = cub3D

SRCS =	main.c \
		src/parsing/check_map.c \
		src/parsing/check_map_closed.c \
		src/parsing/check_map_empty.c \
		src/parsing/exit_parse.c \
		src/parsing/parse_file.c \
		src/parsing/parse_imgs.c \
		src/parsing/parse_main.c \
		src/parsing/parse_vars.c \
		src/rendering/movement.c \
		src/rendering/rotation.c \
		src/rendering/loop.c \
		src/rendering/raycasting.c \
		src/rendering/paint.c \
		src/utils/initialization.c \
		src/utils/utils.c

SRCS_B = main.c \
		src/parsing/check_map_bonus.c \
		src/parsing/check_map_closed.c \
		src/parsing/check_map_empty.c \
		src/parsing/exit_parse.c \
		src/parsing/parse_file.c \
		src/parsing/parse_imgs.c \
		src/parsing/parse_main.c \
		src/parsing/parse_vars.c \
		src/rendering/movement.c \
		src/rendering/rotation.c \
		src/utils/initialization.c \
		src/utils/utils.c \
		src/bonus/loop_bonus.c \
		src/bonus/paint_bonus.c \
		src/bonus/raycasting_bonus.c

OBJS = $(SRCS:.c=.o)
OBJS_B = $(SRCS_B:.c=.o)

CFLAGS = -Wall -Werror -Wextra
LDFLAGS = -lm
MLXFLAGS = -I . -L minilibx-linux -lmlx -lXext -lX11

LIBFT = ./libft/libft.a

all: $(NAME)

$(NAME): $(OBJS)
	make -C ./minilibx-linux all
	make -C ./libft all
	cc $(CFLAGS) $(OBJS) $(LIBFT) $(LDFLAGS) $(MLXFLAGS) -g -o $(NAME)

bonus: $(OBJS_B)
	make -C ./minilibx-linux all
	make -C ./libft all
	cc $(CFLAGS) $(OBJS_B) $(LIBFT) $(LDFLAGS) $(MLXFLAGS) -g -o $(NAME)_bonus

%.o: %.c
	cc $(CFLAGS) -c $^ -I./ -o $@

bonus/%.o: bonus/%.c
	cc $(CFLAGS) -c $< -I./ -o $@

clean:
	rm -rf $(OBJS) $(OBJS_B)
	make -C ./libft clean

fclean: clean
	make -C ./libft fclean
	rm -rf $(NAME) $(NAME)_bonus

re: fclean all

.PHONY: all clean fclean re

