# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: skrabby <skrabby@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/01/10 21:48:52 by oelaina           #+#    #+#              #
#    Updated: 2020/01/11 19:36:05 by skrabby          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = visual

LIB = -lft -L../lib -L./visualizer/minilibx/ -lmlx -framework OpenGL -framework AppKit

SRCS_DIR = ./srcs/

FLAGS = -Wall -Wextra -Werror

SRCS_VIS = main \
		   parser 

SRCS = cell \
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
			-I../lib/libft/ \
			-I../include \
			-I./visualizer/minilibx

OBJ =	$(addprefix ../obj/, $(addsuffix .o, $(SRCS)))
OBJ2 =	$(addprefix obj/, $(addsuffix .o, $(SRCS_VIS)))

all: $(NAME)

obj/%.o: srcs/%.c
	@gcc $(FLAGS) -c $< $(HEADER) -o $@
	
$(NAME): obj $(OBJ) $(OBJ2)
	@tput setaf 7; tput bold; echo "Compiling LIB"
	@make -C ../lib
	@tput setaf 7; tput bold; echo "Compiling VISUAL"
	@gcc $(FLAGS) $(OBJ2) $(OBJ) $(HEADER) -o $(NAME) $(LIB)
	@tput setaf 2; tput bold; echo "DONE VISUAL"

obj:
	@mkdir obj

clean:
	@rm -rf obj
	@tput setaf 6; tput bold; echo "DONE Clean!"
	
fclean: clean
	@rm -f $(NAME)
	@tput setaf 6; tput bold; echo "DONE Fclean!"

re: fclean all
.PHONY: all clean fclean re