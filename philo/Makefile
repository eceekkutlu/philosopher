NAME = philo
CC = cc
CFLAGS = -Wall -Wextra -Werror
LDFLAGS = -pthread

SRCS = main.c \
	create_func.c \
	for_died.c \
	utils.c \
	write_func.c

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LDFLAGS) -o $(NAME)

%.o: %.c philo.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re