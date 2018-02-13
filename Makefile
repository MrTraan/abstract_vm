NAME = abstract_vm

C_DIR =	src
C_DIRS = $(shell find $(C_DIR) -type d -follow -print | grep -v '/tests_')
C_FILES = $(shell find $(C_DIRS) -type f -follow -print | grep -e '\.cpp$$' | grep -v '/tests_')

O_DIR =	.tmp/obj
O_DIRS = $(C_DIRS:$(C_DIR)%=$(O_DIR)%)
O_FILES = $(C_FILES:$(C_DIR)%.cpp=$(O_DIR)%.o)

FLAGS = -Wall -Wextra -Werror -std=c++14
INCLUDES = -I./src

CC = clang++

all: $(NAME)

$(NAME): $(O_FILES)
	$(CC) $(FLAGS) $^ $(LIB) $(SRCI) -o $@ && echo "Done"

$(O_DIR)%.o: $(C_DIR)%.cpp
	@mkdir -p $(O_DIRS) $(O_DIR)
	$(CC) $(FLAGS) $(INCLUDES) -o $@ -c $<

clean:
	@rm -Rf $(O_DIR)

fclean: clean
	@rm -f $(NAME)
	@rm -Rf .tmp/

re: fclean all

debug: FLAGS+=-g
debug: re

.PHONY: clean all fclean re
