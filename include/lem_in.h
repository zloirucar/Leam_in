/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skrabby <skrabby@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 19:09:22 by oelaina           #+#    #+#             */
/*   Updated: 2019/12/30 21:41:40 by skrabby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEAM_IN_H
# define LEAM_IN_H

#include "libft.h"
#include "stdio.h"

typedef	struct 			s_neib
{
	int					index;		// neighbors index in arr_cell
	int					weight;		// distance from cell to neighbor
	struct	s_neib		*next;
}						t_neib;

typedef	struct			s_cell
{
	char				*name;
	struct	s_cell		*next;
	struct	s_cell		*prev;
	int					index;		// index in arr_cell
	int					distance;
	int					is_visited;
	int					y;
	int					x;
	t_neib				*next_neib;
}						t_cell;

typedef struct			s_path
{
	t_cell				*cell;
	struct	s_path		*next;
}						t_path;

typedef struct			s_finpaths
{
	t_path				*path;	
	struct s_finpaths	*next;
}						t_finpaths;

typedef	struct			s_map
{
	int					size_arr;
	int					count;
	int					count_cells;			
	int					check_cell;
	int					check_link;
	int					check_start;
	int					check_end;
	t_finpaths			*paths;
	t_path				*shortest_path;
	t_path				*delete_path;
	t_cell				**arr_cell;		// all nodes
	int					start;			// start node index
	int					end;			// end node index
}						t_map;

/* cell operations*/
t_cell					*init_cell();
void					set_cell(t_cell *cell, char *line, int index);
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
int						shortest_path(t_map *map);
t_cell					*tcell_dup(t_cell *cur);
t_neib					*del_neib(t_map *map, t_neib *list,	char* name);
void					bhandari_algo(t_map *map);
void					revert_weights(t_map *map, t_neib *list, char *find_name);
int						get_weight(t_map *map, t_neib *list, char *find_name);

/* paths */
t_path					*init_path(void);
t_path					*path_addlast(t_path *alst, t_cell *cell);
void					print_shortest(t_path *list);
t_path					*revert_path(t_path *path);
void					save_paths(t_map *map);
t_finpaths				*paths_addlast(t_finpaths *list, t_path *new_path);
t_finpaths				*init_finpaths(void);

#endif

/*
2
##start
A 2 0
##end
H 2 6
B 0 8
C 4 2
D 0 2
E 0 4
F 0 6
G 4 4
A-B
A-E
B-C
C-D
E-D
H-D
F-D
E-F
F-G
G-H
*/