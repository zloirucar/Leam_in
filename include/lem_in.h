/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelaina <oelaina@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 19:09:22 by oelaina           #+#    #+#             */
/*   Updated: 2019/12/29 16:42:11 by oelaina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEAM_IN_H
# define LEAM_IN_H

#include "libft.h"

typedef	struct			s_cell
{
	char				*name;
	int					y;
	int					x;
	int					size_neib;
	struct	s_cell		**neib;
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
/*map operations */
t_map					*init_map();
void					parse_map(t_map *map);
void					parse_count(t_map *map, char *line);
/* tools */
void					clear_2D_arr(char **arr);
int						check_char(char* line, char c);
#endif