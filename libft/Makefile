NAME = libft.a

CC = gcc
CFLAGS = -Wall -Wextra -Werror
AR = ar -rcs

LIBFT_DIR	= src/libft
GNL_DIR		= src/get_next_line

LIBFT_SRCS = ft_bzero.c \
		ft_memchr.c \
		ft_memmove.c \
		ft_memcmp.c \
		ft_memcpy.c \
		ft_memset.c \
		ft_strchr.c \
		ft_strlcat.c \
		ft_strlcpy.c \
		ft_strlen.c \
		ft_strncmp.c \
		ft_strnstr.c \
		ft_strrchr.c \
		ft_atoi.c \
		ft_isalpha.c \
		ft_isdigit.c \
		ft_isalnum.c \
		ft_isascii.c \
		ft_isprint.c \
		ft_isspace.c \
		ft_toupper.c \
		ft_tolower.c \
		ft_calloc.c \
		ft_strdup.c \
		ft_substr.c \
		ft_strjoin.c \
		ft_strtrim.c \
		ft_itoa.c \
		ft_split.c \
		ft_strmapi.c \
		ft_putchar_fd.c \
		ft_putstr_fd.c \
		ft_putendl_fd.c \
		ft_putnbr_fd.c \
			ft_lstnew.c \
			ft_lstadd_front.c \
			ft_lstsize.c \
			ft_lstlast.c \
			ft_lstadd_back.c \
			ft_lstdelone.c \
			ft_lstclear.c \
			ft_lstiter.c \
			ft_lstmap.c \

GNL_SRCS =	get_next_line.c \
			get_next_line_utils.c

LIBFT_OBJS = $(addprefix $(LIBFT_DIR)/, $(LIBFT_SRCS:.c=.o))
GNL_OBJS = $(addprefix $(GNL_DIR)/, $(GNL_SRCS:.c=.o))

OBJS = $(LIBFT_OBJS) $(GNL_OBJS)

all : $(NAME)

$(NAME): $(OBJS)
	$(AR) $@ $^

$(LIBFT_DIR)/%.o: $(LIBFT_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(GNL_DIR)/%.o: $(GNL_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean :
	rm -f $(OBJS) $(BONUS_OBJS)

fclean : clean
	rm -f $(NAME)

re : fclean all

.PHONY : all clean fclean re bonus