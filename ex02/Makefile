# * Colors
GREEN = \033[0;32m
RED = \033[0;31m
YELLOW = \033[0;33m
RESET = \033[0m
OK = $(GREEN)[OK]$(RESET)

# * Program name
NAME = PmergeMe

# * Compilation
MYCPP = c++
MYCPPFLAGS = -Wall -Wextra -Werror -std=c++98 -g3 -fsanitize=address

# * Removal
RM = rm -rf

# * Includes
INCLUDES = -I ./inc/

# * Objects dir
OBJ_DIR = ./obj/

# * Sources files
BITCOIN_EXCHANGE_DIR = ./src/
BITCOIN_EXCHANGE_SRCS = 	main.cpp PMergeMe.cpp

SRCS = $(BITCOIN_EXCHANGE_SRCS)

# * Object files
OBJS = $(addprefix $(OBJ_DIR), $(SRCS:.cpp=.o))

# ! RULES
$(OBJ_DIR)%.o: $(BITCOIN_EXCHANGE_DIR)%.cpp
	@mkdir -p $(OBJ_DIR)
	@$(MYCPP) $(MYCPPFLAGS) $(INCLUDES) -c $< -o $@

$(NAME): $(OBJS)
	@$(MYCPP) $(MYCPPFLAGS) $(INCLUDES) $(OBJS) -o $(NAME)
	@echo "$(OK) $(GREEN)$(NAME)$(RESET)"

all: obj $(NAME)

obj:
	@mkdir -p $(OBJ_DIR)

clean:
	@$(RM) $(OBJS)
	@echo "$(OK) $(RED)Removed object files$(RESET)"

fclean: clean
	@echo "$(OK) $(RED)Removed $(NAME)$(RESET)"
	@$(RM) $(NAME)

re: fclean all
	@echo "$(OK) $(YELLOW)Rebuilt $(NAME)$(RESET)"

run:
	clear
	@$(MAKE) re --no-print-directory
	./$(NAME) 3 5 9 7 4
	@./$(NAME) `shuf -i 1-100000 -n 10 | tr "\n" " "`
# 	@./$(NAME) `shuf -i 1-100000 -n 3000 | tr "\n" " "`

debug:
	clear
	@$(MAKE) re --no-print-directory
	gdb ./$(NAME)

.PHONY: all obj clean fclean re run debug

.DEFAULT_GOAL: all
