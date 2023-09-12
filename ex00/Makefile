# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: trerolle <marvin@42lausanne.ch>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/07 09:13:06 by trerolle          #+#    #+#              #
#    Updated: 2023/07/14 12:43:10 by trerolle         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME= btc 

SRCS=	main.cpp\
		BitcoinExchange.cpp

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

