/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skrabby <skrabby@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 19:09:22 by oelaina           #+#    #+#             */
/*   Updated: 2020/01/11 20:14:16 by skrabby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEAM_IN_H
# define LEAM_IN_H

#include "libft.h"

typedef	struct 			s_neib
{
	int					index;		// neighbors index in arr_cell
	int					weight;		// distance from cell to neighbor
	struct	s_neib		*next;
}						t_neib;

typedef	struct			s_cell
{
	char				*name;
	struct	s_cell		*next;		// this pointer is responsible for saving nodes in a check-priority hierarchy list (checklist) as we explore the map
	struct	s_cell		*prev;		// this pointer is crucial in implementing dijkstra algo, saving the shortest path
	int					index;		// index in arr_cell
	int					distance;
	int					is_visited;
	int					y;
	int					x;
	int					ant;		// the index of an ant wchich is located in the cell (if start/end cell then the count of ants)
	t_neib				*next_neib; // the list of nodes' neighbors, i. e. other nodes, which our node is connect to 
}						t_cell;

typedef struct			s_edge
{
	t_cell				*first_node;
	t_cell				*second_node;	
	int					used;
	struct s_edge		*next;
}						t_edge;

typedef struct			s_path
{
	t_cell				*cell;
	int					coord_x;
	int					coord_y;
	struct	s_path		*next;
	struct	s_path		*prev; // for ant_cross
}						t_path;

typedef struct			s_finpaths
{
	t_path				*path;	
	struct s_finpaths	*next;
}						t_finpaths;

typedef struct			s_solution
{
	char				*one_turn; 
	struct s_solution	*next;
}						t_solution;

typedef	struct			s_map
{
	int					size_arr;
	int					count;		// quantity of ants
	int					antsleft;	// quantity of ants left
	int					count_cells;			
	int					check_cell;
	int					check_link;
	int					check_start;
	int					newline;
	int					check_end;
	int					check_count;
	int					ant_index;
	t_finpaths			*rev_paths; // the storage of all paths that made it to finish and have been reverted, so we can later revert it back
	t_finpaths			*paths; // our final solution paths
	t_path				*delete_path; // the storage of nodes, the paths of which we are going to delete (by 2 nodes at once) 
	t_cell				**arr_cell;		// all nodes
	t_edge				*edges;			// store of all edges to determine unused ones
	t_solution			*solution;		// parse solutions for visualzier
	int					crossed;		// bool of whether all ants have crossed the road 
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
void					return_neib(t_map *map);
/*checklist*/
t_cell					*checklist_addlast(t_cell *checklist, t_cell *new);
/*map operations */
t_map					*init_map();
void					parse_map(t_map *map);
int						parse_count(t_map *map, char *line);
void					update_map(t_map *map);
/* tools */
void					clear_2d_arr(char **arr);
int						check_char(char* line, char c);
void					error_msg(void);
/* solver */
int						shortest_path(t_map *map);
t_cell					*tcell_dup(t_cell *cur);
t_neib					*del_neib(t_map *map, t_neib *list,	char* name);
void					bhandari_algo(t_map *map);
int						revert_weights(t_map *map, t_neib *list, char *find_name);
int						get_weight(t_map *map, t_neib *list, char *find_name);
/* paths */
t_path					*init_path(void);
t_path					*path_addlast(t_path *alst, t_cell *cell);
void					print_shortest(t_path *list);
t_path					*revert_path(t_path *path);
void					save_paths(t_map *map);
t_finpaths				*paths_addlast(t_finpaths *list, t_path *new_path);
t_finpaths				*init_finpaths(void);
void					delete_path(t_map *map);

/* edges */
t_edge					*edge_addlast(t_edge *list, t_cell *fnode, t_cell *snode);
t_edge					*init_edge(void);
t_edge					*remove_used_edge(t_map *map, char *fnode_name, char *snode_name);

/*nodes*/
int						visit_nodes_neighbours(t_map *map, t_cell *this_node);
int						get_weight(t_map *map, t_neib *list, char *find_name);
int						visit_node(t_map *map, t_cell *prev_node, t_cell *new_node);
/* ants */
void					move_ant(t_map *map, t_finpaths *path, int ant_index, int *newline);
void					ant_cross(t_map *map, int ants);
/*Bhandari */
void					bhandari_algo(t_map *map);
/*print */
void					printshort(t_map *map);
void					print_shortest(t_path *list);

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