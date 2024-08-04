NAME = philo
CC = cc
CFLAGS = -g -Wall -Wextra -Werror

SRC_PATH = src/

FILES_PATH = ./
FILES_SRC = assign.c init.c

OBJ_PATH = build/

SRC = main.c \
	$(addprefix $(FILES_PATH), $(FILES_SRC))

LIBFT = libft/libft.a
OBJ =	$(SRC:.c=.o)
OBJS =	$(addprefix $(OBJ_PATH), $(OBJ))

all: $(OBJ_PATH) $(NAME)

$(NAME): $(OBJS)
	# make -C ./libft
	# @$(CC) $(CFLAGS) $(OBJS) ./libft/libft.a -o $(NAME)
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_PATH):
	mkdir $(OBJ_PATH)

clean:
	# make clean -C ./libft
	@rm -rf $(OBJ_PATH)

fclean: clean
	# make fclean -C ./libft
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re