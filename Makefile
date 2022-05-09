NAME = philo

FLAGS = -Wall -Wextra -Werror -MD

CC = gcc

SRC = 	Philosophers.c	\
		utils1.c		\
		utils2.c		\
		utils3.c

HEADER = Philosophers.h

OBJ = $(SRC:%.c=%.o)

all: $(NAME)

$(NAME): $(OBJ) $(HEADER)
	gcc $(FLAGS) $(SRC) -o $(NAME)

%o: %.c
	gcc $(FLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ) *.d

fclean: clean
	rm -rf $(NAME) *.d

re: fclean all

.PHONY: clean fclean all re
