# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: trerolle <marvin@42lausanne.ch>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/19 19:18:44 by trerolle          #+#    #+#              #
#    Updated: 2023/07/19 20:15:00 by trerolle         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME= RPN 

SRCS=	main.cpp\
		RPN.cpp

OBJ= $(SRCS:%.cpp=%.o)

CC= c++

CFLAGS=	-Wall -Werror -Wextra -std=c++98

GREEN = \033[0;32m

all: ${NAME}

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

