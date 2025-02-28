NAME = cub3D
NAME_BONUS = $(NAME)_bonus

SRCS =	main.c \
		src/parsing/check_map.c \
		src/parsing/check_elements.c \
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
		src/rendering/raycasting_setup.c \
		src/rendering/paint.c \
		src/utils/initialization.c \
		src/utils/utils.c \
		src/parsing/check_map_utils.c

SRCS_B = src/bonus/main_bonus.c \
		src/parsing/check_map_closed.c \
		src/parsing/check_map_empty.c \
		src/parsing/check_elements.c \
		src/parsing/exit_parse.c \
		src/parsing/parse_file.c \
		src/parsing/parse_vars.c \
		src/rendering/movement.c \
		src/rendering/rotation.c \
		src/utils/initialization.c \
		src/bonus/check_map_bonus.c \
		src/bonus/door_bonus.c \
		src/bonus/loop_bonus.c \
		src/bonus/mouse_bonus.c \
		src/bonus/shoot_bonus.c \
		src/bonus/paint_bonus.c \
		src/bonus/parse_imgs_bonus.c \
		src/bonus/parse_main_bonus.c \
		src/bonus/parse_sprite_bonus.c \
		src/bonus/raycasting_bonus.c \
		src/bonus/raycasting_main_bonus.c \
		src/bonus/raycasting_setup_bonus.c \
		src/bonus/utils_bonus.c \
		src/parsing/check_map_utils.c \
		src/bonus/parse_enemy_bonus.c \
		src/bonus/enemy_draw_bonus.c \
		src/bonus/enemy_set_bonus.c \
		src/bonus/utils_free_bonus.c

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

# Add a phony target for bonus and make the actual compilation depend on the binary
bonus: $(NAME_BONUS)

# Create a separate rule for the bonus binary that depends on the object files
$(NAME_BONUS): $(OBJS_B)
	make -C ./minilibx-linux all
	make -C ./libft all
	cc $(CFLAGS) $(OBJS_B) $(LIBFT) $(LDFLAGS) $(MLXFLAGS) -g -o $(NAME_BONUS)

%.o: %.c
	cc $(CFLAGS) -c $^ -I./ -o $@

clean:
	rm -rf $(OBJS) $(OBJS_B)
	make -C ./libft clean

fclean: clean
	make -C ./libft fclean
	rm -rf $(NAME) $(NAME_BONUS)

re: fclean all

.PHONY: all clean fclean re bonus
