CFLAGS = -Wall -Werror -Wextra #-fsanitize=address -g3 

SRC = so_long.c parsing.c \
      map_operations.c \
      bfs.c \
      utils.c \
      screen.c \
      player_moves.c \
      queue_operations.c \
      components.c \
      get_next_line/get_next_line.c \
      get_next_line/get_next_line_utils.c

LIBFT = libft/libft.a

OBJECTS = $(SRC:.c=.o)

NAME = so_long

all: $(NAME)

$(NAME):$(OBJECTS) $(LIBFT)
	cc $(CFLAGS) $^ -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -o $(NAME)

$(LIBFT):
	make -C libft

clean:
	make clean -C libft
	rm -f $(OBJECTS)

fclean: clean
	make fclean -C libft
	rm -f $(NAME)

re: fclean all

.SECONDARY :$(OBJECTS)

.PHONY: all clean fclean re
