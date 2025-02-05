NAME = cub3D

SRCS =	main.c \
		src/parsing/parsing.c \
		src/rendering/loop.c \
		src/rendering/raycasting.c \
		src/rendering/paint.c \
		src/utils/initialization.c \
		src/utils/utils.c
SRCS_B =

OBJS = $(SRCS:.c=.o)
OBJS_B = $(addprefix ./bonus/, $(SRCS_B:.c=.o))

CFLAGS = -Wall -Werror -Wextra
LDFLAGS = -lm
MLXFLAGS = -I . -L minilibx-linux -lmlx -lXext -lX11

LIBFT = ./libft/libft.a

all: $(NAME)

$(NAME): $(OBJS)
	make -C ./minilibx-linux all
	make -C ./libft all
	ar rcs $@.a $^
	cc $(CFLAGS) main.c $(NAME).a $(LIBFT) $(LDFLAGS) $(MLXFLAGS) -g -o $(NAME)

bonus: $(OBJS_B)
	make -C ./minilibx-linux all
	make -C ./libft all
	ar rcs bonus.a $^
	cc $(CFLAGS) ./bonus/main_bonus.c bonus.a $(LIBFT) $(FTPRINTF) -I . -L minilibx-linux -lmlx -lXext -lX11 -g -o $(NAME)_bonus

%.o: %.c
	cc $(CFLAGS) -c $^ -I./ -o $@

bonus/%.o: bonus/%.c
	cc $(CFLAGS) -c $< -I./ -o $@

clean:
	rm -rf $(OBJS) $(OBJS_B)
	make -C ./libft clean

fclean: clean
	make -C ./libft fclean
	rm -rf $(NAME).a $(NAME)_bonus.a
	rm -rf $(NAME) $(NAME)_bonus

re: fclean all

.PHONY: all clean fclean re
