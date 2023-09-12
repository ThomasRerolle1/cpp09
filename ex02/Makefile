NAME= PmergeMe 

SRCS=	main.cpp\
	PmergeMe.cpp
	

OBJ= $(SRCS:%.cpp=%.o)

CC= c++

CFLAGS=	-Wall -Werror -Wextra -std=c++98

GREEN = \033[0;32m

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ)
	@echo "$(GREEN)$(NAME) succesfully compiled$(RESET)"

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf *.o

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
