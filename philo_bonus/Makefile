CFLAGS = -Wall -Werror -Wextra  #-fsanitize=thread -g3 

SRC = philo_bonus.c \
utils_bonus.c \
philo_manager_bonus.c \
threads_bonus.c \
itoa_bonus.c
OBJECTS = $(SRC:.c=.o)

NAME = philo_bonus

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
