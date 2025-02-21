NAME = cub3D

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
		src/rendering/paint.c \
		src/utils/initialization.c \
		src/utils/utils.c

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
		src/bonus/loop_bonus.c \
		src/bonus/paint_bonus.c \
		src/bonus/raycasting_bonus.c \
		src/bonus/check_map_bonus.c \
		src/bonus/parse_imgs_bonus.c \
		src/bonus/parse_main_bonus.c \
		src/bonus/initialization_bonus.c \
		src/bonus/utils_bonus.c

CFLAGS = -Wall -Werror -Wextra
LDFLAGS = -lm
MLXFLAGS = -I . -L minilibx-linux -lmlx -lXext -lX11

LIBFT = ./libft/libft.a

all: $(NAME)

$(NAME): $(SRCS)
		make -C ./minilibx-linux all
		make -C ./libft all
		cc $(CFLAGS) -g $(SRCS) $(LIBFT) $(LDFLAGS) $(MLXFLAGS) -o $(NAME)

bonus: $(SRCS_B)
		make -C ./minilibx-linux all
		make -C ./libft all
		cc $(CFLAGS) -g $(SRCS_B) $(LIBFT) $(LDFLAGS) $(MLXFLAGS) -o $(NAME)_bonus

clean:
		@echo "오브젝트 파일은 존재하지 않습니다."

fclean: clean
		make -C ./libft fclean
		rm -rf $(NAME) $(NAME)_bonus

re: fclean all

.PHONY: all bonus clean fclean re