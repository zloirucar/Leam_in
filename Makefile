# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: oelaina <oelaina@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/09/05 11:23:44 by skrabby           #+#    #+#              #
#    Updated: 2019/11/27 21:07:51 by oelaina          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = lem_in

LIB = -lftprintf -L./lib

SRCS_DIR = ./srcs/

SRCS = main \

HEADER = ./include

OBJ =	$(addprefix obj/, $(addsuffix .o, $(SRCS)))

all: $(NAME)

obj/%.o: srcs/%.c
	@gcc $(FLAGS) -c $< -I $(HEADER) -o $@

$(NAME): obj $(OBJ)
	@make -C lib
	@gcc -Wall -Wextra -Werror $(OBJ) -I $(HEADER) -o $(NAME) $(LIB)
	@tput setaf 6; tput bold; echo "DONE LEM_IN"

obj:
	@mkdir obj

clean:
	@make -C lib clean
	@rm -rf obj
	
fclean: clean
	@make -C lib fclean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
