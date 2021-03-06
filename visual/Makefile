# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: oelaina <oelaina@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/01/10 21:48:52 by oelaina           #+#    #+#              #
#    Updated: 2020/02/15 14:08:34 by oelaina          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = visual

LIB = -lft -L../lib -L./srcs/minilibx/ -lmlx -framework OpenGL -framework AppKit

SRCS_DIR = ./srcs/

FLAGS = -Wall -Wextra -Werror

SRCS_VIS = main \
		   parser \
		   draw \
		   print_rooms \
		   tools \
		   draw_line \
		   ants_move \
		   ants_move_tools \
		   print_rooms_tools \
		   draw_text \
		   solmove_pair \
		   solution \
		   
SRCS = cell \
	   map	\
	   parse \
	   tools \
	   links \
	   solver \
	   neib_list \
	   ant \
	   nodes \
	   path \
	   finpath \
	   dijkstra \
	   hashtable \
	   clear \
	   clear_map \
	   optimal_path

HEADER = 	-I./include \
			-I../lib/libft/ \
			-I../include \
			-I./srcs/minilibx

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