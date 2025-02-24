# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: TheTerror <jfaye@student.42lyon.fr>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/07 10:24:30 by TheTerror         #+#    #+#              #
#    Updated: 2024/02/27 21:27:52 by TheTerror        ###   ########lyon.fr    #
#                                                                              #
# **************************************************************************** #

NAME = btc

LIBFTPP	=	$(LIBFTPP_PATH)libftpp.a

LIBFTPP_PATH = ./libftpp/
OBJ_PATH = ./.obj/

INCLUDE = Include.h Date.hpp ExchangeRateBase.hpp CustomException.hpp BitcoinExchange.hpp

CC = 				c++
CPPFLAGS =			-std=c++98
CFLAGS=				$(CPPFLAGS) -Wall -Werror -Wextra -g3
RM =				rm -rf

SRC = main.cpp Date.cpp ExchangeRateBase.cpp CustomException.cpp BitcoinExchange.cpp

OBJ = $(SRC:%.cpp=$(OBJ_PATH)%.o)

all : make_libftpp $(NAME)

$(OBJ_PATH)%.o : %.cpp $(INCLUDE)
	@mkdir -p $(OBJ_PATH)
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME) : $(OBJ) $(INCLUDE) $(LIBFTPP)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFTPP) -o $@

make_libftpp :
	make -C $(LIBFTPP_PATH)

run : all
	./$(NAME)
valgrind : all
	valgrind --show-leak-kinds=all --leak-check=full --track-fds=yes ./$(NAME)

clean :
	@make clean -C $(LIBFTPP_PATH)
	@$(RM) $(OBJ)
	@$(RM) $(OBJ_PATH)
fclean : clean
	@make fclean -C $(LIBFTPP_PATH)
	@$(RM) $(NAME)
re : fclean all