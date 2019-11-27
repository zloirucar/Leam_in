# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: oelaina <oelaina@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/09/05 11:23:44 by skrabby           #+#    #+#              #
#    Updated: 2019/11/27 22:15:56 by oelaina          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = lem_in

LIB = -lftprintf -L./lib

SRCS_DIR = ./srcs/

FLAGS = -Wall -Wextra -Werror

SRCS = main \

HEADER = -I./include -I./lib/srcs/libft/

OBJ =	$(addprefix obj/, $(addsuffix .o, $(SRCS)))

all: $(NAME)

obj/%.o: srcs/%.c
	@gcc $(FLAGS) -c $< $(HEADER) -o $@

$(NAME): obj $(OBJ)
	@make -C lib
	@gcc $(FLAGS) $(OBJ) $(HEADER) -o $(NAME) $(LIB)
	@tput setaf 6; tput bold; echo "DONE LEM_IN"

obj:
	@mkdir obj

clean:
	@make -C lib clean
	@rm -rf obj
	@tput setaf 6; tput bold; echo "DONE Clean!"
	
fclean: clean
	@make -C lib fclean
	@rm -f $(NAME)
	@tput setaf 6; tput bold; echo "DONE Fclean!"

re: fclean all
.PHONY: all clean fclean re
