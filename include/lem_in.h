/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelaina <oelaina@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 19:09:22 by oelaina           #+#    #+#             */
/*   Updated: 2019/12/30 20:27:15 by oelaina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEAM_IN_H
# define LEAM_IN_H

#include "libft.h"

typedef	struct 			s_neib
{
	int					index;
	struct	s_neib		*next;
}						t_neib;

typedef	struct			s_cell
{
	char				*name;
	struct	s_cell		*next;
	struct	s_cell		*prev;
	int					distance;
	int					is_visited;
	int					y;
	int					x;
	t_neib				*next_neib;
}						t_cell;

typedef	struct			s_map
{
	int					size_arr;
	int					count;
	int					count_cells;			
	int					check_cell;
	int					check_link;
	int					check_start;
	int					check_end;
	t_cell				*shortest_path;
	t_cell				**paths;
	t_cell				**arr_cell;
	int					start;
	int					end;

}						t_map;

/* cell operations*/
t_cell					*init_cell();
void					set_cell(t_cell *cell, char *line);
void					arr_cellcpy(t_cell **dest, t_cell **src, int size);
void					inc_arr_cell(t_cell ***arr_cell, int* size);
void					parse_start_end(t_map *map, char *line);
void					add_to_arr(t_map *map, char *line);
/* links operations */
void					parse_links(t_map *map, char *line);
t_neib					*init_neib(void);
t_neib					*neib_addlast(t_neib *alst, int index);
/*map operations */
t_map					*init_map();
void					parse_map(t_map *map);
void					parse_count(t_map *map, char *line);
/* tools */
void					clear_2D_arr(char **arr);
int						check_char(char* line, char c);
/* solver */
void					shortest_path(t_map *map);
t_cell					*tcell_dup(t_cell *cur);
#endif