# ################ #
#*    COULEURS    *#
# ################ #

CLASSIC	= \e[0m
WHITE	= \e[38;2;238;232;213m
BOLD	= \e[1m
# BLACK	= \e[38;2;0;0;0m
BLACK	= \e[30m
RED   	= \e[31m
GREEN  	= \e[32m
BLUE 	= \e[38;2;0;36;148m
PURPLE 	= \e[38;2;211;54;130m
CYAN   	= \e[36m
YELLOW 	= \e[38;2;250;189;0m

# ############### #
#*   VARIABLES   *#
# ############### #

NAME = a.out

CXX = @c++ -std=c++20

SRCS =	./env/SIMDplatform.cpp					\
		./env/srcs/private/String.cpp			\
		./env/srcs/private/IOStream.cpp			\
		./env/srcs/private/Pool.cpp				\
		./env/srcs/private/Mutex.cpp			\
		./env/srcs/private/Thread.cpp			\
		./env/srcs/private/MultiThreading.cpp	\
		./env/srcs/private/Vector3.cpp			\
		\
		./main.cpp

LMAKE = @make --no-print-directory -C

OBJS_DIR = objs

OBJS = $(SRCS:%.cpp=$(OBJS_DIR)/%.obj)

DEPS = $(OBJS:%.obj=%.d)

INCLUDES = -I ./env/srcs -I .

CFLAGS = -Wall -Wextra -MMD -g3 -O3 -march=native -Wno-comment

LIB = -lpthread

# ############## #
#*    REGLES    *#
# ############## #

all: YAY $(NAME)

$(NAME): $(OBJS)
	$(CXX) $(CFLAGS) $(OBJS) $(LIB) -o $@
	@echo "$(BOLD)$(CYAN)Exécutable $(NAME) créé avec succès!$(CLASSIC)"

$(OBJS_DIR)/%.obj: %.cpp
	@mkdir -p $(@D)
	@echo "$(GREEN)🗸 Compilation $(BOLD)$(YELLOW)$<$(CLASSIC)"
	$(CXX) $(INCLUDES) $(CFLAGS) -c $< -o $@

clean:
	@echo "$(BOLD)$(RED)"
	rm $(LIBFT_P)/$(OBJS_DIR) -rf
	rm $(OBJS_DIR) -rf
	@echo "$(CLASSIC)"

fclean: clean
	@echo "$(BOLD)$(RED)"
	rm $(NAME) -f
	@echo "$(BOLD)$(GREEN)Tout a été supprimé... 🗑️\n$(CLASSIC)"

re: fclean all

.PHONY: all clean fclean re
-include $(DEPS)

# ############## #
#*    AUTRES    *#
# ############## #

YAY:
	@echo "$(PURPLE)$(BOLD)Compilation avec les flags suivants : "
	@echo $(CFLAGS)
	@echo "$(CLASSIC)"
