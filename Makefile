SRC_BONUS_DIR       = src_bonus
BUILD_BONUS_DIR     = build_bonus
SRC_DIR             = src
BUILD_DIR           = build
NAME                = pipex
CFLAG               = -Wall -Wextra -Werror -I./includes/ -g3

SRC_MAIN            = ./bin/main/main.c \
                      ./bin/pipex/bonus.c \
                      ./bin/pipex/pipex.c \
                      ./bin/print/print.c \
                      ./bin/print/ft_printf.c \
                      ./bin/print/print_functions.c \
                      ./bin/print/print_functions2.c \
                      ./bin/print/utils.c \
                      ./bin/setup/args.c \
                      ./bin/setup/setup.c \
                      ./bin/setup/env.c \
                      ./bin/utils/bool.c \
                      ./bin/utils/exec.c \
                      ./bin/utils/free.c \
                      ./bin/utils/path.c \
                      ./bin/utils/split.c \
                      ./bin/utils/utils.c \
                      ./bin/utils/get_next_line.c \
                      ./bin/utils/get_next_line_utils.c \

SRC_BONUS           = ./bin/main/main_bonus.c \
                      ./bin/pipex/bonus.c \
                      ./bin/pipex/pipex.c \
                      ./bin/print/print.c \
                      ./bin/print/ft_printf.c \
                      ./bin/print/print_functions.c \
                      ./bin/print/print_functions2.c \
                      ./bin/print/utils.c \
                      ./bin/setup/args.c \
                      ./bin/setup/setup.c \
                      ./bin/setup/env.c \
                      ./bin/utils/bool.c \
                      ./bin/utils/exec.c \
                      ./bin/utils/free.c \
                      ./bin/utils/path.c \
                      ./bin/utils/split.c \
                      ./bin/utils/utils.c \
                      ./bin/utils/get_next_line.c \
                      ./bin/utils/get_next_line_utils.c \

OBJ_MAIN            = $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SRC_MAIN))
OBJ_BONUS           = $(patsubst $(SRC_BONUS_DIR)/%.c, $(BUILD_BONUS_DIR)/%.o, $(SRC_BONUS))

CC                  = cc

all: $(NAME)

$(NAME): $(OBJ_MAIN)
	@mkdir -p $(dir $@)
	$(CC) $(OBJ_MAIN) -o $(NAME) $(CFLAG)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAG) -c $< -o $@

bonus: $(OBJ_BONUS)
	@mkdir -p $(dir $(NAME))
	$(CC) $(OBJ_BONUS) -o $(NAME) $(CFLAG)

$(BUILD_BONUS_DIR)/%.o: $(SRC_BONUS_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAG) -c $< -o $@

clean:
	@rm -rf $(BUILD_DIR) $(BUILD_BONUS_DIR)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
