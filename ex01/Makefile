# * Colors
GREEN = \033[0;32m
RED = \033[0;31m
YELLOW = \033[0;33m
RESET = \033[0m
OK = $(GREEN)[OK]$(RESET)

# * Program name
NAME = RPN

# * Compilation
MYCPP = c++
MYCPPFLAGS = -Wall -Wextra -Werror -std=c++98 -g3 -fsanitize=address #-D DEBUG=true

# * Removal
RM = rm -rf

# * Includes
INCLUDES = -I ./inc/

# * Objects dir
OBJ_DIR = ./obj/

# * Sources files
BITCOIN_EXCHANGE_DIR = ./src/
BITCOIN_EXCHANGE_SRCS = 	main.cpp RPN.cpp

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
	./$(NAME) "8 9 * 9 - 9 - 9 - 4 - 1 +"
	./$(NAME) "7 7 * 7 -"
	./$(NAME) "1 2 * 2 / 2 * 2 4 - +"
	./$(NAME) "(1 + 1)"
	./$(NAME) "0 1 /"
	./$(NAME) "1 0 /"

debug:
	clear
	@$(MAKE) re --no-print-directory
	gdb ./$(NAME)

.PHONY: all obj clean fclean re run debug

.DEFAULT_GOAL: all
