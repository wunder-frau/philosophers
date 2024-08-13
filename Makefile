NAME = philo
LIBFT_DIR = libft_
LIBFT = $(LIBFT_DIR)/libft.a
CC = gcc
CFLAGS = -g -Wall -Wextra -Werror
#CFLAGS = -fsanitize=address -g -I$(LIBFT_DIR)

SRC_PATH = src/

FILES_PATH = ./
FILES_SRC = main.c assign.c init.c log_action.c time_managment_utils.c \
			thread_management.c actions.c initialization_time.c\
			atomic_operations.c destroy_and_free.c monitor.c

OBJ_PATH = build/

SRC = $(addprefix $(FILES_PATH), $(FILES_SRC))

LIBFT = libft_/libft.a
OBJ =	$(SRC:.c=.o)
OBJS =	$(addprefix $(OBJ_PATH), $(OBJ))

all: $(OBJ_PATH) $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME)

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR)

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_PATH):
	mkdir $(OBJ_PATH)

clean:
	@rm -rf $(OBJ_PATH)
	@$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	@rm -f $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

submodule:
	@git submodule init
	@git submodule update

.PHONY: all clean fclean re submodule