NAME = abstract_vm

C_DIR =	src
C_TEST_FILES = src/Expection.cpp src/OperandFactory.cpp src/Parser.cpp test/main.cpp src/execution.cpp
C_FILES = src/Expection.cpp src/OperandFactory.cpp src/Parser.cpp src/main.cpp src/execution.cpp

O_DIR =	.tmp/obj
O_FILES = $(C_FILES:$(C_DIR)%.cpp=$(O_DIR)%.o)

FLAGS = -Wall -Wextra -Werror -std=c++14
INCLUDES = -I./src

CC = clang++

all: $(NAME)

$(NAME): $(O_FILES)
	$(CC) $(FLAGS) $^ $(LIB) $(SRCI) -o $@ && echo "Done"

$(O_DIR)%.o: $(C_DIR)%.cpp
	@mkdir -p $(O_DIR)
	$(CC) $(FLAGS) $(INCLUDES) -o $@ -c $<

clean:
	@rm -Rf $(O_DIR)

fclean: clean
	@rm -f $(NAME) test_$(NAME)
	@rm -Rf .tmp/

re: fclean all

test: clean
	$(CC) -std=c++14 $(C_TEST_FILES) $(INCLUDES) -o test_$(NAME) && ./test_$(NAME) -s

debug: FLAGS+=-g
debug: re

.PHONY: clean all fclean re
