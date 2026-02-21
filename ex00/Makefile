# * Colors
GREEN = \033[0;32m
RED = \033[0;31m
YELLOW = \033[0;33m
RESET = \033[0m
OK = $(GREEN)[OK]$(RESET)

NO_PRINT = --no-print-directory

# * Program name
NAME = btc

# * Compilation
MYCPP = c++
MYCPPFLAGS = -Wall -Wextra -Werror -std=c++98 -g3 -fsanitize=address -D DEBUGGING=false

# * Removal
RM = rm -rf

# * Includes
INCLUDES = -I ./inc/ -I ./inc/logger/inc/

# * Objects dir
OBJ_DIR = ./obj/

# * Sources files
BITCOIN_EXCHANGE_DIR = ./src/
BITCOIN_EXCHANGE_SRCS = 	main.cpp BitcoinExchange.cpp Date.cpp

LOGGER_DIR = ./inc/logger
LOGGER_LIB = $(LOGGER_DIR)/logger.a

SRCS = $(BITCOIN_EXCHANGE_SRCS)

# * Object files
OBJS = $(addprefix $(OBJ_DIR), $(SRCS:.cpp=.o))

# ! RULES
$(OBJ_DIR)%.o: $(BITCOIN_EXCHANGE_DIR)%.cpp
	@mkdir -p $(OBJ_DIR)
	@$(MYCPP) $(MYCPPFLAGS) $(INCLUDES) -c $< -o $@

$(NAME): $(LOGGER_LIB) $(OBJS)
	@$(MYCPP) $(MYCPPFLAGS) $(INCLUDES) $(OBJS) -o $(NAME) $(LOGGER_LIB)
	@echo "$(OK) $(GREEN)$(NAME)$(RESET)"

$(LOGGER_LIB):
	@$(MAKE) -C $(LOGGER_DIR) $(NO_PRINT)

update:
	@git submodule update --init --recursive --remote --merge 2>/dev/null || true

all: obj logs update $(NAME)

obj:
	@mkdir -p $(OBJ_DIR)

logs:
	@mkdir -p logs

clean:
	@$(RM) $(OBJS)
	@echo "$(OK) $(RED)Removed object files$(RESET)"

fclean: clean
	@echo "$(OK) $(RED)Removed $(NAME)$(RESET)"
	@$(RM) $(NAME)

re: fclean all
	@$(MAKE) -C $(LOGGER_DIR) re $(NO_PRINT)
	@echo "$(OK) $(YELLOW)Rebuilt $(NAME)$(RESET)"

run:
	clear
	@$(MAKE) re --no-print-directory
	./$(NAME) input.txt

debug:
	clear
	@$(MAKE) re --no-print-directory
	gdb ./$(NAME)

.PHONY: all obj clean fclean re run debug

.DEFAULT_GOAL: all
