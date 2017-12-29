BLUE = echo "\033[0;36m"
RED = echo "\033[0;31m"
GREEN = echo "\033[0;32m"
END = echo "\033[0m"

NAME = ft_retro

SRC = ClassGame.cpp \
		main.cpp \
		Attack.class.cpp \
		Enemies.class.cpp \
		Hero.class.cpp \
		Player.class.cpp

OBJ = $(SRC:.cpp=.o)

CC = clang++

FLGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJ)
		@$(CC) -o $(NAME) $(OBJ)  -lncurses
		@echo "$$($(GREEN))*******************$$($(END))"
		@echo "$$($(GREEN))FT_RETRO..is..READY$$($(END))"
		@echo "$$($(GREEN))*******************$$($(END))"

%.o: %.cpp
		@$(CC) $(FLGS) -c $<
		@echo "$$($(BLUE))******************$$($(END))"
		@echo "$$($(BLUE))......COMPILE.....$$($(END))"
		@echo "$$($(BLUE))******************$$($(END))"

clean:
		@rm -f *.o
		@rm -f *~
		@echo "$$($(RED))*********************$$($(END))"
		@echo "$$($(RED))OBJECT.FILE.IS.DELETE$$($(END))"
		@echo "$$($(RED))*********************$$($(END))"

fclean: clean
		@rm -f $(NAME)
		@echo "$$($(RED))**********************$$($(END))"
		@echo "$$($(RED))FT_RETRO...IS...DELETE$$($(END))"
		@echo "$$($(RED))**********************$$($(END))"

re: fclean all