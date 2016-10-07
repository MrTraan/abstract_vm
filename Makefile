NAME = abstract_vm

C_DIR =	src
C_DIRS = $(shell find $(C_DIR) -type d -follow -print | grep -v '/tests_')
C_FILES = $(shell find $(C_DIRS) -type f -follow -print | grep "\.cpp" | grep -v '/tests_')

O_DIR =	.tmp/obj
O_DIRS = $(C_DIRS:$(C_DIR)%=$(O_DIR)%)
O_FILES = $(C_FILES:$(C_DIR)%.cpp=$(O_DIR)%.o)

FLAGS = -Wall -Wextra -Werror
INCLUDES = -I./includes
# LIB = -Llibft -lft -ltermcap

all: $(NAME)

$(NAME): $(O_FILES)
	g++ $(FLAGS) $^ $(LIB) $(SRCI) -o $@ && echo "Done"

$(O_DIR)%.o: $(C_DIR)%.cpp
	@mkdir -p $(O_DIRS) $(O_DIR)
	g++ $(FLAGS) $(INCLUDES) -o $@ -c $<

clean:
	@rm -rf $(O_DIR)

fclean: clean
	@rm $(NAME) || true
	@rm -rf .tmp/

re: fclean all

.PHONY: clean all fclean re