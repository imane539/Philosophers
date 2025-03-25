CFLAGS = -Wall -Werror -Wextra #-fsanitize=address -g3 

SRC = philo.c \
utils.c

OBJECTS = $(SRC:.c=.o)

NAME = philo

all: $(NAME)

$(NAME):$(OBJECTS) 
	cc $(CFLAGS) $^ -o $(NAME)


clean:
	rm -f $(OBJECTS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.SECONDARY :$(OBJECTS)

.PHONY: all clean fclean re
