NAME = philo
CC = cc
CFLAGS = -g -Wall -Wextra -Werror

SRC_PATH = src/

FILES_PATH = ./
FILES_SRC = main.c assign.c init.c log_action.c time_managment_utils.c \
			thread_management.c actions.c initialization_time.c\
			atomic_operations.c destroy_and_free.c monitor.c auxiliary_functions.c

OBJ_PATH = build/

SRC = $(addprefix $(FILES_PATH), $(FILES_SRC))

OBJ =	$(SRC:.c=.o)
OBJS =	$(addprefix $(OBJ_PATH), $(OBJ))

all: $(OBJ_PATH) $(NAME)

$(NAME): $(OBJS)
	@echo "🔗 Link objects to create the executable..."
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
	@echo "✅ Build complete: $(NAME)"

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	@echo "🔨 Compiling $<..."
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_PATH):
	mkdir $(OBJ_PATH)
	@echo "📁 Create the build directory if it doesn't exist: $(OBJ_PATH)"

clean:
	@echo "🧹 Cleaning up..."
	@rm -rf $(OBJ_PATH)
	@echo "🗑️ Removed build directory: $(OBJ_PATH)"

fclean: clean
	@rm -f $(NAME)
	@echo "🚮 Removing executable: $(NAME)"

re: fclean all
	@echo "🔄 Rebuild the project: $(NAME)"

.PHONY: all clean fclean re