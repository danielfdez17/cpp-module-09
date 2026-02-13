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
MYCPPFLAGS = -Wall -Wextra -Werror -std=c++98 -g3 -fsanitize=address -D DEBUG=false

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
# 	./$(NAME) 
	./$(NAME) 9999999999999999999
# 	./$(NAME) 3 5 9 7 -4
# 	./$(NAME) 3 5 9 7 4 1 50 10
# 	./$(NAME) 3
# 	./$(NAME) 49 20 1 -1
# 	./$(NAME) 5 2 8 4 0 1
# 	./$(NAME) 3 1 4 1 5 9 2 6
# 	./$(NAME) 9 8 7 6 5 4 3 2 1
# 	./$(NAME) 30 49 60 1 31 29 42 46 13 8 5
# 	./$(NAME) 11 2 19 0 16 8 6 15 10 3 21 1 18 9 14 19 12 5 4 20 13 7
# 	./$(NAME) `shuf -i 1-10 -n 10 | tr "\n" " "`
# 	./$(NAME) `shuf -i 1-100000 -n 10 | tr "\n" " "`
# 	./$(NAME) `shuf -i 1-100000 -n 10 | tr "\n" " "`
# 	./$(NAME) `shuf -i 1-100000 -n 10 | tr "\n" " "`
# 	./$(NAME) `shuf -i 1-100000 -n 10 | tr "\n" " "`
# 	./$(NAME) `shuf -i 1-100000 -n 10 | tr "\n" " "`
# 	./$(NAME) `shuf -i 1-100000 -n 10 | tr "\n" " "`
# 	./$(NAME) `shuf -i 1-100000 -n 3000 | tr "\n" " "`
# 	./$(NAME) `shuf -i 1-100000 -n 10000 | tr "\n" " "`

debug:
	clear
	@$(MAKE) re --no-print-directory
	gdb ./$(NAME)

.PHONY: all obj clean fclean re run debug

.DEFAULT_GOAL: all
