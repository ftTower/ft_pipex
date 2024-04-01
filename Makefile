SRC_DIR = bin
BUILD_DIR = build
NAME = pipex
CFLAG = -Wall -Wextra -Werror -I./includes -g3

SRC = $(shell find $(SRC_DIR) -type f -name '*.c')
CC = cc

OBJ = $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(SRC))

ARGV = ./bin/utils/exec.c /usr/bin/cat "grep exec" output.txt

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAG) -c $< -o $@
	@clear

all: $(NAME)

$(NAME): $(OBJ)
	@echo $(OBJ)
	@$(CC) $(OBJ) -o $(NAME) $(CFLAG)
	@clear

clear:
	@clear
	@echo "42Paris : $(NAME)"
	@echo ""

clean: clear
	@rm -rf $(BUILD_DIR)
	@rm *.txt
	@echo "Clean : *.o in build !"

fclean: clean
	@rm -f $(NAME)
	@echo "Clean : ./$(NAME)"

pip:
	@valgrind ./$(NAME) $(ARGV)

valgrind: clear
	@valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --trace-children=yes ./$(NAME) $(ARGV)

re: fclean all clear

.PHONY: all clean fclean re