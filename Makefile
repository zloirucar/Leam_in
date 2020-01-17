# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: oelaina <oelaina@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/09/05 11:23:44 by skrabby           #+#    #+#              #
#    Updated: 2020/01/17 16:37:58 by oelaina          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = lem_in

LIB = -lft -L./lib

SRCS_DIR = ./srcs/

FLAGS = -Wall -Wextra -Werror

SRCS = main \
	   cell \
	   map	\
	   parse \
	   tools \
	   links \
	   solver \
	   neib_list \
	   ant \
	   edge \
	   nodes \
	   path \
	   finpath \
	   bhandari \
	   dijkstra

HEADER = 	-I./include \
			-I./lib/libft/ \
			
OBJ =	$(addprefix obj/, $(addsuffix .o, $(SRCS)))

all: $(NAME)

obj/%.o: srcs/%.c
	@gcc $(FLAGS) -c $< $(HEADER) -o $@
	
$(NAME): obj $(OBJ)
	@tput setaf 7; tput bold; echo "Compiling LIB"
	@make -C lib
	@tput setaf 7; tput bold; echo "Compiling LEM_IN"
	@gcc $(FLAGS) $(OBJ) $(HEADER) -o $(NAME) $(LIB)
	@make -C visual
	@tput setaf 2; tput bold; echo "DONE LEM_IN"

obj:
	@mkdir obj

clean:
	@make -C lib clean
	@make -C visual clean
	@rm -rf obj
	@tput setaf 6; tput bold; echo "DONE Clean!"
	
fclean: clean
	@make -C lib fclean
	@rm -f $(NAME)
	@make -C visual fclean
	@tput setaf 6; tput bold; echo "DONE Fclean!"

re: fclean all
.PHONY: all clean fclean re
